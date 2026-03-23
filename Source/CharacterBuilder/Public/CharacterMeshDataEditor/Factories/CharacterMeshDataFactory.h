#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "CharacterMeshDataFactory.generated.h"

UCLASS()
class UCharacterMeshDataFactory : public UFactory
{
	GENERATED_BODY()

public:
	UCharacterMeshDataFactory();

	virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent,
									  FName InName, EObjectFlags Flags,
									  UObject* Context, FFeedbackContext* Warn) override;

	virtual bool ShouldShowInNewMenu() const override { return true; }
};