#pragma once

#include "CoreMinimal.h"
#include "AdvancedPreviewScene.h"

class FCharacterMeshDataEditor;
class UCharacterMeshData;

class FCharacterMeshPreviewScene : public FAdvancedPreviewScene
{
public:
    FCharacterMeshPreviewScene(ConstructionValues CVS,
                               const TSharedRef<FCharacterMeshDataEditor>& InEditor);
    virtual ~FCharacterMeshPreviewScene() override;

    virtual void Tick(float InDeltaTime) override;

    void RebuildMeshes(UCharacterMeshData* InMeshData);

private:
    TWeakPtr<FCharacterMeshDataEditor> EditorPtr;
    TArray<USceneComponent*>           PreviewComponents;
};
