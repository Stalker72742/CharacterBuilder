#include "CharacterMeshDataEditor/AssetEditor/FCharacterMeshPreviewScene.h"

//#include "Data/DataAssets/CharacterMeshData.h"
//#include "Data/Structs/EquipmentMeshData.h"
#include "GameplayTagContainer.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/WorldSettings.h"

FCharacterMeshPreviewScene::FCharacterMeshPreviewScene(
    ConstructionValues CVS, const TSharedRef<FCharacterMeshDataEditor>& InEditor)
    : FAdvancedPreviewScene(CVS)
    , EditorPtr(InEditor)
{
    GetWorld()->GetWorldSettings(true)->bEnableWorldBoundsChecks = false;
    SetFloorVisibility(true, false);
}

FCharacterMeshPreviewScene::~FCharacterMeshPreviewScene() {}

void FCharacterMeshPreviewScene::Tick(float InDeltaTime)
{
    FAdvancedPreviewScene::Tick(InDeltaTime);
}

void FCharacterMeshPreviewScene::RebuildMeshes(UCharacterMeshData* InMeshData)
{
    for (USceneComponent* Comp : PreviewComponents)
        if (IsValid(Comp))
            RemoveComponent(Comp);

    PreviewComponents.Empty();

    //if (!InMeshData || !InMeshData->bHasTPSMeshes || InMeshData->RootTPSMesh.IsNull())
      //  return;

    USkeletalMesh* rootMesh = nullptr;// = InMeshData->RootTPSMesh.LoadSynchronous();
    
    USkeletalMeshComponent* LeaderComp = NewObject<USkeletalMeshComponent>(GetTransientPackage());
    LeaderComp->SetSkeletalMeshAsset(rootMesh);
    AddComponent(LeaderComp, FTransform::Identity);
    PreviewComponents.Add(LeaderComp);

    TArray<FGameplayTag> UsedSlots;

    // for (const FEquipmentMeshData& EquipData : InMeshData->GetTPSEquipmentMeshData())
    // {
    //     if (!EquipData.SlotTag.IsValid() || UsedSlots.Contains(EquipData.SlotTag))
    //         continue;
    //
    //     bool bCanEquip = true;
    //     for (const FGameplayTag& LockedSlot : EquipData.AdditionalLockedSlots)
    //     {
    //         if (LockedSlot.IsValid() && UsedSlots.Contains(LockedSlot))
    //         {
    //             bCanEquip = false;
    //             break;
    //         }
    //     }
    //
    //     if (!bCanEquip)
    //         break;
    //
    //     UsedSlots.Add(EquipData.SlotTag);
    //     UsedSlots.Append(EquipData.AdditionalLockedSlots);
    //
    //     if (const auto skMeshData = EquipData.GetSkeletalEquipmentMesh())
    //     {
    //         if (skMeshData->SkeletalMesh.IsNull())
    //             break;
    //
    //         USkeletalMeshComponent* Comp = NewObject<USkeletalMeshComponent>(GetTransientPackage());
    //         Comp->SetSkeletalMesh(skMeshData->SkeletalMesh.LoadSynchronous());
    //         Comp->SetLeaderPoseComponent(LeaderComp);
    //         AddComponent(Comp, FTransform::Identity);
    //         PreviewComponents.Add(Comp);
    //     }
    // }
}
