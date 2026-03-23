
#include "CharacterMeshDataEditor/Factories/CharacterMeshDataFactory.h"
//#include "Data/DataAssets/CharacterMeshData.h"

UCharacterMeshDataFactory::UCharacterMeshDataFactory()
{
	//SupportedClass = UCharacterMeshData::StaticClass();
	bCreateNew     = true;
	bEditAfterNew  = true;
}

UObject* UCharacterMeshDataFactory::FactoryCreateNew(
	UClass* InClass, UObject* InParent, FName InName,
	EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	return nullptr;// NewObject<UCharacterMeshData>(InParent, InClass, InName, Flags);
}