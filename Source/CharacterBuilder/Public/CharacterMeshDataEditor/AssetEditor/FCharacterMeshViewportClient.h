#pragma once

#include "CoreMinimal.h"
#include "EditorViewportClient.h"

class FCharacterMeshPreviewScene;

class FCharacterMeshViewportClient : public FEditorViewportClient
{
public:
    FCharacterMeshViewportClient(const TSharedRef<SEditorViewport>& InViewport,
                                 const TSharedRef<FCharacterMeshPreviewScene>& InPreviewScene);

    void FocusViewportOnBounds(const FBoxSphereBounds& Bounds, bool bInstant = false);

    FCharacterMeshPreviewScene* AdvancedPreviewScene {nullptr};
};
