#include "CharacterMeshDataEditor/AssetEditor/SCharacterMeshViewport.h"
#include "CharacterMeshDataEditor/AssetEditor/FCharacterMeshPreviewScene.h"
#include "CharacterMeshDataEditor/AssetEditor/FCharacterMeshViewportClient.h"

void SCharacterMeshViewport::Construct(const FArguments& InArgs,
    TSharedPtr<FCharacterMeshDataEditor> InEditor,
    TSharedPtr<FCharacterMeshPreviewScene> InPreviewScene)
{
    EditorPtr    = InEditor;
    PreviewScene = InPreviewScene;

    SEditorViewport::Construct(SEditorViewport::FArguments());
}

SCharacterMeshViewport::~SCharacterMeshViewport()
{
    if (TypedViewportClient.IsValid())
        TypedViewportClient->Viewport = nullptr;
}

void SCharacterMeshViewport::OnFocusViewportToSelection()
{
    SEditorViewport::OnFocusViewportToSelection();

    if (TypedViewportClient.IsValid())
        TypedViewportClient->FocusViewportOnBounds(FBoxSphereBounds(), false);
}

TSharedRef<FEditorViewportClient> SCharacterMeshViewport::MakeEditorViewportClient()
{
    TypedViewportClient = MakeShareable(
        new FCharacterMeshViewportClient(SharedThis(this), PreviewScene.ToSharedRef()));

    return TypedViewportClient.ToSharedRef();
}
