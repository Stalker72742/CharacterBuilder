#pragma once

#include "CoreMinimal.h"
#include "Toolkits/AssetEditorToolkit.h"

class UCharacterMeshData;
class FCharacterMeshPreviewScene;
class SCharacterMeshViewport;

class FCharacterMeshDataEditor : public FAssetEditorToolkit, public FNotifyHook
{
public:
    FCharacterMeshDataEditor()  = default;
    ~FCharacterMeshDataEditor() = default;

    void InitEditor(const EToolkitMode::Type Mode,
                    const TSharedPtr<IToolkitHost>& InitToolkitHost,
                    UCharacterMeshData* InMeshData);

    virtual FName        GetToolkitFName()              const override { return FName("CharacterMeshDataEditor"); }
    virtual FText        GetBaseToolkitName()           const override { return INVTEXT("Character Mesh Data Editor"); }
    virtual FString      GetWorldCentricTabPrefix()     const override { return TEXT("CharacterMeshData "); }
    virtual FLinearColor GetWorldCentricTabColorScale() const override { return FLinearColor(0.5f, 0.25f, 0.f); }

    virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)   override;
    virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;
    virtual void OnClose() override;

    TSharedPtr<FCharacterMeshPreviewScene> CreatePreviewScene();

private:
    TSharedRef<SDockTab> SpawnTab_Viewport(const FSpawnTabArgs& Args) const;
    void                 ValidateSlotConflicts() const;

private:
    UCharacterMeshData*                    MeshData      {nullptr};
    TSharedPtr<FCharacterMeshPreviewScene> PreviewScene;
    TSharedPtr<SCharacterMeshViewport>     ViewportWidget;

    static const FName TabID_Viewport;
    static const FName TabID_Details;

public:

    TSharedPtr<FCharacterMeshPreviewScene> GetPreviewScene() const { return PreviewScene; }
};
