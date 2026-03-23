#include "CharacterMeshDataEditor/AssetTypeActions/FAssetTypeActions_CharacterMeshData.h"
#include "CharacterMeshDataEditor/AssetEditor/FCharacterMeshDataEditor.h"
//#include "Data/DataAssets/CharacterMeshData.h"

UClass* FAssetTypeActions_CharacterMeshData::GetSupportedClass() const
{
    return nullptr;// UCharacterMeshData::StaticClass();
}

void FAssetTypeActions_CharacterMeshData::OpenAssetEditor(
    const TArray<UObject*>& InObjects, TSharedPtr<IToolkitHost> EditWithinLevelEditor)
{
    const EToolkitMode::Type Mode = EditWithinLevelEditor.IsValid()
        ? EToolkitMode::WorldCentric
        : EToolkitMode::Standalone;

    for (UObject* Obj : InObjects)
    {
        UCharacterMeshData* MeshData = nullptr;// = Cast<UCharacterMeshData>(Obj);
        if (!MeshData)
            continue;

        TSharedRef<FCharacterMeshDataEditor> Editor = MakeShared<FCharacterMeshDataEditor>();
        Editor->InitEditor(Mode, EditWithinLevelEditor, MeshData);
    }
}
