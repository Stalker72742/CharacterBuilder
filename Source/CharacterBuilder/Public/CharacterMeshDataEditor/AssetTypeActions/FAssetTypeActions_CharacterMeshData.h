#pragma once

#include "CoreMinimal.h"
#include "AssetTypeActions_Base.h"

class FAssetTypeActions_CharacterMeshData : public FAssetTypeActions_Base
{
public:
    virtual FText    GetName()           const override { return INVTEXT("Character Mesh Data"); }
    virtual FColor   GetTypeColor()      const override { return FColor(255, 140, 0); }
    virtual UClass*  GetSupportedClass() const override;
    virtual uint32   GetCategories()           override { return EAssetTypeCategories::Misc; }

    virtual void OpenAssetEditor(const TArray<UObject*>& InObjects,
                                 TSharedPtr<IToolkitHost> EditWithinLevelEditor) override;
};
