#pragma once

#include "CoreMinimal.h"
#include "SEditorViewport.h"
#include "SCommonEditorViewportToolbarBase.h"

class FCharacterMeshDataEditor;
class FCharacterMeshPreviewScene;
class FCharacterMeshViewportClient;

class SCharacterMeshViewport : public SEditorViewport,
                               public FGCObject,
                               public ICommonEditorViewportToolbarInfoProvider
{
public:
    SLATE_BEGIN_ARGS(SCharacterMeshViewport) {}
    SLATE_END_ARGS()

    void Construct(const FArguments& InArgs,
                   TSharedPtr<FCharacterMeshDataEditor> InEditor,
                   TSharedPtr<FCharacterMeshPreviewScene> InPreviewScene);

    virtual ~SCharacterMeshViewport() override;

    // FGCObject
    virtual void    AddReferencedObjects(FReferenceCollector& Collector) override {}
    virtual FString GetReferencerName() const override { return TEXT("SCharacterMeshViewport"); }

    // ICommonEditorViewportToolbarInfoProvider
    virtual TSharedRef<SEditorViewport> GetViewportWidget()       override { return SharedThis(this); }
    virtual TSharedPtr<FExtender>       GetExtenders()      const override { return MakeShared<FExtender>(); }
    virtual void                        OnFloatingButtonClicked() override {}

    virtual void OnFocusViewportToSelection() override;

    TSharedPtr<FCharacterMeshViewportClient> GetViewportClient() const { return TypedViewportClient; }

protected:
    virtual TSharedRef<FEditorViewportClient> MakeEditorViewportClient() override;

private:
    TSharedPtr<FCharacterMeshPreviewScene>   PreviewScene;
    TSharedPtr<FCharacterMeshViewportClient> TypedViewportClient;
    TSharedPtr<FCharacterMeshDataEditor>     EditorPtr;
};
