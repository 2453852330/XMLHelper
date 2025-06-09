#pragma once
#include "tinyxml2/tinyxml2.h"

#include "XMLType.generated.h"


USTRUCT(BlueprintType)
struct FXMLDocument
{
	GENERATED_BODY()
	tinyxml2::XMLDocument* doc = nullptr;
	bool bIsValid = false;
};

USTRUCT(BlueprintType)
struct FXMLElement
{
	GENERATED_BODY()
	tinyxml2::XMLElement* element = nullptr;
};

USTRUCT(BlueprintType)
struct FXMLAttribute
{
	GENERATED_BODY()
	const tinyxml2::XMLAttribute* attribute = nullptr;
};
