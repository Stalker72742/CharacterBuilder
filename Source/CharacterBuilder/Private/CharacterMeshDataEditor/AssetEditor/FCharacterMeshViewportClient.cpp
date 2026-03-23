#include "CharacterMeshDataEditor/AssetEditor/FCharacterMeshViewportClient.h"
#include "CharacterMeshDataEditor/AssetEditor/FCharacterMeshPreviewScene.h"
#include "SEditorViewport.h"

FCharacterMeshViewportClient::FCharacterMeshViewportClient(
    const TSharedRef<SEditorViewport>& InViewport,
    const TSharedRef<FCharacterMeshPreviewScene>& InPreviewScene)
    : FEditorViewportClient(nullptr, &InPreviewScene.Get(), InViewport)
{
    AdvancedPreviewScene = static_cast<FCharacterMeshPreviewScene*>(PreviewScene);

    SetRealtime(true);

    DrawHelper.bDrawGrid  = false;
    DrawHelper.bDrawPivot = false;

    SetViewLocation(FVector(200.f, 0.f, 100.f));
    SetViewRotation(FVector(-200.f, 0.f, -100.f).Rotation());
    SetViewportType(LVT_Perspective);
    SetViewModes(VMI_Lit, VMI_Lit);
}

void FCharacterMeshViewportClient::FocusViewportOnBounds(const FBoxSphereBounds& Bounds, bool bInstant)
{
    const FVector Position = Bounds.Origin;
    float Radius = Bounds.SphereRadius;

    float AspectToUse = AspectRatio;
    const FIntPoint ViewportSize = Viewport->GetSizeXY();
    if (!bUseControllingActorViewInfo && ViewportSize.X > 0 && ViewportSize.Y > 0)
        AspectToUse = Viewport->GetDesiredAspectRatio();

    if (AspectToUse > 1.0f)
        Radius *= AspectToUse;

    const float HalfFOVRadians     = FMath::DegreesToRadians(ViewFOV / 2.0f);
    const float DistanceFromSphere  = Radius / FMath::Sin(HalfFOVRadians);
    FViewportCameraTransform& VT    = GetViewTransform();
    const FVector CameraOffset      = VT.GetRotation().Vector() * -DistanceFromSphere;

    TWeakPtr<SWidget> WidgetWeak = StaticCastSharedPtr<SWidget>(EditorViewportWidget.Pin());
    
    VT.SetLookAt(Position);
    VT.TransitionToLocation(Position + CameraOffset, WidgetWeak, bInstant);
    Invalidate();
}
