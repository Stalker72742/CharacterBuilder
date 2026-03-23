#include "CharacterMeshDataEditor/AssetEditor/FCharacterMeshDataEditor.h"

//#include "Data/DataAssets/CharacterMeshData.h"
//#include "Data/Structs/EquipmentMeshData.h"
#include "GameplayTagContainer.h"
#include "CharacterMeshDataEditor/AssetEditor/FCharacterMeshPreviewScene.h"
#include "CharacterMeshDataEditor/AssetEditor/SCharacterMeshViewport.h"

#include "PropertyEditorModule.h"
#include "IDetailsView.h"
#include "Widgets/Docking/SDockTab.h"
#include "Framework/Notifications/NotificationManager.h"
#include "Widgets/Notifications/SNotificationList.h"
#include "Styling/AppStyle.h"

#define LOCTEXT_NAMESPACE "FCharacterMeshDataEditor"

const FName FCharacterMeshDataEditor::TabID_Viewport = FName("CharacterMeshDataEditor_Viewport");
const FName FCharacterMeshDataEditor::TabID_Details  = FName("CharacterMeshDataEditor_Details");

void FCharacterMeshDataEditor::InitEditor(
    const EToolkitMode::Type Mode,
    const TSharedPtr<IToolkitHost>& InitToolkitHost,
    UCharacterMeshData* InMeshData)
{
    MeshData = InMeshData;

    // Viewport widget created BEFORE InitAssetEditor — exact same pattern as template
    ViewportWidget = SNew(SCharacterMeshViewport, SharedThis(this), CreatePreviewScene());

    if (PreviewScene.IsValid())
        PreviewScene->RebuildMeshes(MeshData);

    const TSharedRef<FTabManager::FLayout> Layout = FTabManager::NewLayout("CharacterMeshDataEditor_Layout_v1")
        ->AddArea
        (
            FTabManager::NewPrimaryArea()
            ->SetOrientation(Orient_Horizontal)
            ->Split
            (
                FTabManager::NewStack()
                ->SetSizeCoefficient(0.7f)
                ->AddTab(TabID_Viewport, ETabState::OpenedTab)
            )
            ->Split
            (
                FTabManager::NewStack()
                ->SetSizeCoefficient(0.3f)
                ->AddTab(TabID_Details, ETabState::OpenedTab)
            )
        );

    // FAssetEditorToolkit::InitAssetEditor(Mode, InitToolkitHost,
    //     FName("CharacterMeshDataEditorApp"), Layout, true, true, MeshData);

    ValidateSlotConflicts();
}

TSharedPtr<FCharacterMeshPreviewScene> FCharacterMeshDataEditor::CreatePreviewScene()
{
    if (!PreviewScene.IsValid())
    {
        PreviewScene = MakeShareable(new FCharacterMeshPreviewScene(
            FPreviewScene::ConstructionValues()
                .AllowAudioPlayback(false)
                .ShouldSimulatePhysics(false),
            StaticCastSharedRef<FCharacterMeshDataEditor>(AsShared())));
    }

    return PreviewScene;
}

void FCharacterMeshDataEditor::RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
    FAssetEditorToolkit::RegisterTabSpawners(InTabManager);

    WorkspaceMenuCategory = InTabManager->AddLocalWorkspaceMenuCategory(
        LOCTEXT("WorkspaceMenu", "Character Mesh Data Editor"));

    InTabManager->RegisterTabSpawner(TabID_Viewport,
        FOnSpawnTab::CreateSP(this, &FCharacterMeshDataEditor::SpawnTab_Viewport))
        .SetDisplayName(LOCTEXT("ViewportTab", "Preview Viewport"))
        .SetGroup(WorkspaceMenuCategory.ToSharedRef())
        .SetIcon(FSlateIcon(FAppStyle::GetAppStyleSetName(), "GraphEditor.EventGraph_16x"));

    FPropertyEditorModule& PropModule =
        FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");

    FDetailsViewArgs DetailsArgs;
    DetailsArgs.bHideSelectionTip = true;
    DetailsArgs.NameAreaSettings  = FDetailsViewArgs::HideNameArea;

    TSharedRef<IDetailsView> DetailsView = PropModule.CreateDetailView(DetailsArgs);
    //DetailsView->SetObjects(TArray<UObject*>{MeshData});

    DetailsView->OnFinishedChangingProperties().AddLambda(
    [this](const FPropertyChangedEvent&)
    {
        if (PreviewScene.IsValid())
            PreviewScene->RebuildMeshes(MeshData);
    });

    InTabManager->RegisterTabSpawner(TabID_Details,
        FOnSpawnTab::CreateLambda([DetailsView](const FSpawnTabArgs&)
        {
            return SNew(SDockTab).TabRole(ETabRole::PanelTab)
            [
                DetailsView
            ];
        }))
        .SetDisplayName(LOCTEXT("DetailsTab", "Details"))
        .SetGroup(WorkspaceMenuCategory.ToSharedRef());
}

void FCharacterMeshDataEditor::UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
    FAssetEditorToolkit::UnregisterTabSpawners(InTabManager);
    InTabManager->UnregisterTabSpawner(TabID_Viewport);
    InTabManager->UnregisterTabSpawner(TabID_Details);
}

TSharedRef<SDockTab> FCharacterMeshDataEditor::SpawnTab_Viewport(const FSpawnTabArgs& Args) const
{
    TSharedRef<SDockTab> SpawnedTab =
        SNew(SDockTab).Label(LOCTEXT("ViewportTabLabel", "Preview Viewport"));

    if (ViewportWidget.IsValid())
        SpawnedTab->SetContent(ViewportWidget.ToSharedRef());

    return SpawnedTab;
}

void FCharacterMeshDataEditor::OnClose()
{
    MeshData = nullptr;

    if (PreviewScene.IsValid())
        PreviewScene.Reset();

    if (ViewportWidget.IsValid())
        ViewportWidget.Reset();
}

void FCharacterMeshDataEditor::ValidateSlotConflicts() const
{
    if (!MeshData)
        return;

    TArray<FString> ConflictMessages;

    // auto CheckConflicts = [&](const TArray<FEquipmentMeshData>& Entries, const FString& Section)
    // {
    //     TMap<FGameplayTag, FString> SlotOwners;
    //
    //     for (const FEquipmentMeshData& Entry : Entries)
    //     {
    //         if (!Entry.SlotTag.IsValid())
    //             continue;
    //
    //         const FString ItemName = Entry.SlotTag.ToString();
    //
    //         if (FString* Owner = SlotOwners.Find(Entry.SlotTag))
    //         {
    //             ConflictMessages.Add(FString::Printf(
    //                 TEXT("[%s] Slot '%s' claimed by '%s' and '%s'"),
    //                 *Section, *Entry.SlotTag.ToString(), **Owner, *ItemName));
    //         }
    //         else
    //         {
    //             SlotOwners.Add(Entry.SlotTag, ItemName);
    //         }
    //
    //         for (const FGameplayTag& LockedSlot : Entry.AdditionalLockedSlots)
    //         {
    //             if (!LockedSlot.IsValid())
    //                 continue;
    //
    //             if (FString* Owner = SlotOwners.Find(LockedSlot))
    //             {
    //                 ConflictMessages.Add(FString::Printf(
    //                     TEXT("[%s] '%s' locks slot '%s' already owned by '%s'"),
    //                     *Section, *ItemName, *LockedSlot.ToString(), **Owner));
    //             }
    //         }
    //     }
    // };

    // if (MeshData->bHasTPSMeshes)
    //     CheckConflicts(MeshData->GetTPSEquipmentMeshData(), TEXT("TPS"));
    //
    // if (MeshData->bHasFPSMeshes)
    //     CheckConflicts(MeshData->GetTPSEquipmentMeshData(), TEXT("FPS"));

    for (const FString& Msg : ConflictMessages)
    {
        FNotificationInfo Info(FText::FromString(Msg));
        Info.bFireAndForget       = false;
        Info.bUseSuccessFailIcons = true;
        Info.ExpireDuration       = 0.f;
        Info.FadeOutDuration      = 0.f;
        Info.Image                = FAppStyle::GetBrush("Icons.Warning");

        TSharedPtr<SNotificationItem> Notif =
            FSlateNotificationManager::Get().AddNotification(Info);

        if (Notif.IsValid())
            Notif->SetCompletionState(SNotificationItem::CS_Fail);

        UE_LOG(LogTemp, Warning, TEXT("CharacterMeshDataEditor: %s"), *Msg);
    }
}

#undef LOCTEXT_NAMESPACE
