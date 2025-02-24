// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "tinyxml2/tinyxml2.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "XMLBlueprintFunctionLibrary.generated.h"

USTRUCT(BlueprintType)
struct FXMLDocument
{
	GENERATED_BODY()
	tinyxml2::XMLDocument* doc = nullptr;
};

USTRUCT(BlueprintType)
struct FXMLElement
{
	GENERATED_BODY()
	tinyxml2::XMLElement* element = nullptr;
};



UCLASS()
class XMLHELPER_API UXMLBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	// load xml 
	UFUNCTION(BlueprintPure,Category="XMLHelper")
	static bool BPL_LoadXMLFromFile(FString FilePath,FXMLDocument & XMLDocument);
	UFUNCTION(BlueprintPure,Category="XMLHelper")
	static bool BPL_LoadXMLFromXMLString(FString XMLString,FXMLDocument & XMLDocument);
	
	// first child from xml document
	UFUNCTION(BlueprintPure,Category="XMLHelper")
	static FXMLElement BPL_GetFirstChildElementFromDoc(const FXMLDocument& XMLDocument, FString Key);

	// first child from xml element
	UFUNCTION(BlueprintPure,Category="XMLHelper")
	static FXMLElement BPL_GetFirstChildElementFromElement(const FXMLElement& XMLElement, FString Key);

	// get root
	UFUNCTION(BlueprintPure,Category="XMLHelper")
	static FXMLElement BPL_GetRootElement(const FXMLDocument& XMLDocument);

	// get count
	UFUNCTION(BlueprintPure,Category="XMLHelper")
	static int32 BPL_GetCountFromDocument(const FXMLDocument& XMLDocument,FString Key);	
	UFUNCTION(BlueprintPure,Category="XMLHelper")
	static int32 BPL_GetCountFromElement(const FXMLElement& XMLElement,FString Key);	

	// get element
	UFUNCTION(BlueprintPure,Category="XMLHelper")
	static FXMLElement BPL_GetNextSiblingElement(const FXMLElement& XMLElement,FString Key);
	UFUNCTION(BlueprintPure,Category="XMLHelper")
	static FXMLElement BPL_GetPreviousSiblingElement(const FXMLElement& XMLElement,FString Key);
	
	// get text
	UFUNCTION(BlueprintPure,Category="XMLHelper")
	static FString BPL_GetElementText(const FXMLElement& XMLElement);

	// attributes
	UFUNCTION(BlueprintPure,Category="XMLHelper")
	static FString BPL_GetStringAttributeFromElement(const FXMLElement& XMLElement, FString Key);
	UFUNCTION(BlueprintPure,Category="XMLHelper")
	static float BPL_GetFloatAttributeFromElement(const FXMLElement& XMLElement, FString Key);


	// create
	UFUNCTION(BlueprintPure,Category="XMLHelper")
	static FXMLDocument BPL_CreateRootXML(FString RootName);
	UFUNCTION(BlueprintPure,Category="XMLHelper")
	static FXMLElement BPL_InsertElementToDocument(const FXMLDocument & XMLDocument,FString ElementName);
	UFUNCTION(BlueprintPure,Category="XMLHelper")
	static FXMLElement BPL_InsertElementToElement(const FXMLElement & XMLElement,FString ElementName);

	// set
	UFUNCTION(BlueprintCallable,Category="XMLHelper")
	static void BPL_SetElementText(const FXMLElement & XMLElement, FString Text);

	// save
	UFUNCTION(BlueprintCallable,Category="XMLHelper")
	static void BPL_SaveXMLToFile(const FXMLDocument& XMLDocument,FString FilePath);
};


