// Fill out your copyright notice in the Description page of Project Settings.


#include "XMLBlueprintFunctionLibrary.h"

#include "LogHelper.h"


bool UXMLBlueprintFunctionLibrary::BPL_LoadXMLFromFile(FString FilePath,FXMLDocument & XMLDocument)
{
	XMLDocument.doc = new tinyxml2::XMLDocument;
	if (!XMLDocument.doc)
	{
		LogError("Failed to create XML document");
		return false;
	}
	tinyxml2::XMLError error = XMLDocument.doc->LoadFile(TCHAR_TO_UTF8(*FilePath));;
	if (error != tinyxml2::XMLError::XML_SUCCESS)
	{
		LogError("Failed to load XML from file {%s} : why {%s}",*FilePath,UTF8_TO_TCHAR(XMLDocument.doc->ErrorStr()));
		return false;
	}
	return true;
}

bool UXMLBlueprintFunctionLibrary::BPL_LoadXMLFromXMLString(FString XMLString, FXMLDocument& XMLDocument)
{
	XMLDocument.doc = new tinyxml2::XMLDocument;
	if (!XMLDocument.doc)
	{
		LogError("Failed to create XML document");
		return false;
	}
	tinyxml2::XMLError error = XMLDocument.doc->Parse(TCHAR_TO_UTF8(*XMLString));;
	if (error != tinyxml2::XMLError::XML_SUCCESS)
	{
		LogError("Failed to parse xml from string : why {%s}",UTF8_TO_TCHAR(XMLDocument.doc->ErrorStr()));
		return false;
	}
	return true;
}


FXMLElement UXMLBlueprintFunctionLibrary::BPL_GetFirstChildElementFromDoc(const FXMLDocument& XMLDocument, FString Key)
{
	FXMLElement XmlElement;
	XmlElement.element = Key.IsEmpty() ? XMLDocument.doc->FirstChildElement() : XMLDocument.doc->FirstChildElement(TCHAR_TO_UTF8(*Key));
	return XmlElement;
}


FXMLElement UXMLBlueprintFunctionLibrary::BPL_GetFirstChildElementFromElement(const FXMLElement& XMLElement, FString Key)
{
	FXMLElement XmlElement;
	XmlElement.element = Key.IsEmpty() ? XMLElement.element->FirstChildElement() : XMLElement.element->FirstChildElement(TCHAR_TO_UTF8(*Key));
	return XmlElement;
}

FXMLElement UXMLBlueprintFunctionLibrary::BPL_GetRootElement(const FXMLDocument& XMLDocument)
{
	FXMLElement XmlElement;
	XmlElement.element = XMLDocument.doc->RootElement();
	return XmlElement;
}



int32 UXMLBlueprintFunctionLibrary::BPL_GetCountFromDocument(const FXMLDocument& XMLDocument, FString Key)
{
	return Key.IsEmpty() ? XMLDocument.doc->ChildElementCount() : XMLDocument.doc->ChildElementCount(TCHAR_TO_UTF8(*Key));
}


int32 UXMLBlueprintFunctionLibrary::BPL_GetCountFromElement(const FXMLElement& XMLElement, FString Key)
{
	return Key.IsEmpty() ? XMLElement.element->ChildElementCount() : XMLElement.element->ChildElementCount(TCHAR_TO_UTF8(*Key));
}

FXMLElement UXMLBlueprintFunctionLibrary::BPL_GetNextSiblingElement(const FXMLElement& XMLElement, FString Key)
{
	FXMLElement newXMLElement;
	newXMLElement.element = Key.IsEmpty() ? XMLElement.element->NextSiblingElement() : XMLElement.element->NextSiblingElement(TCHAR_TO_UTF8(*Key));
	return newXMLElement;
}

FXMLElement UXMLBlueprintFunctionLibrary::BPL_GetPreviousSiblingElement(const FXMLElement& XMLElement, FString Key)
{
	FXMLElement newXMLElement;
	newXMLElement.element = Key.IsEmpty() ? XMLElement.element->PreviousSiblingElement() : XMLElement.element->PreviousSiblingElement(TCHAR_TO_UTF8(*Key));
	return newXMLElement;
}

FString UXMLBlueprintFunctionLibrary::BPL_GetElementText(const FXMLElement& XMLElement)
{
	return UTF8_TO_TCHAR(XMLElement.element->GetText());
}

FString UXMLBlueprintFunctionLibrary::BPL_GetStringAttributeFromElement(const FXMLElement& XMLElement, FString Key)
{
	const char** result = nullptr;
	if (XMLElement.element->QueryStringAttribute(TCHAR_TO_UTF8(*Key),result) == tinyxml2::XML_SUCCESS)
	{
		return UTF8_TO_TCHAR(*result);
	}
	return TEXT("No Key");
}

float UXMLBlueprintFunctionLibrary::BPL_GetFloatAttributeFromElement(const FXMLElement& XMLElement, FString Key)
{
	float v = 0.f;
	if (XMLElement.element->QueryFloatAttribute(TCHAR_TO_UTF8(*Key),&v) == tinyxml2::XML_SUCCESS)
	{
		return v;
	}
	return MAX_FLT;
}

FXMLDocument UXMLBlueprintFunctionLibrary::BPL_CreateRootXML(FString RootName)
{
	FXMLDocument XMLDoc;
	XMLDoc.doc = new tinyxml2::XMLDocument;
	XMLDoc.doc->InsertEndChild(XMLDoc.doc->NewElement(TCHAR_TO_UTF8(*RootName)));
	return XMLDoc;
}

FXMLElement UXMLBlueprintFunctionLibrary::BPL_InsertElementToDocument(const FXMLDocument& XMLDocument, FString ElementName)
{
	FXMLElement XmlElement;
	tinyxml2::XMLNode* node = XMLDocument.doc->FirstChildElement()->InsertEndChild(XMLDocument.doc->NewElement(TCHAR_TO_UTF8(*ElementName)));
	XmlElement.element = node->ToElement();
	return XmlElement;
}

FXMLElement UXMLBlueprintFunctionLibrary::BPL_InsertElementToElement(const FXMLElement& XMLElement, FString ElementName)
{
	FXMLElement newXmlElement;
	newXmlElement.element = XMLElement.element->InsertNewChildElement(TCHAR_TO_UTF8(*ElementName));
	return newXmlElement;
}

void UXMLBlueprintFunctionLibrary::BPL_SetElementText(const FXMLElement& XMLElement, FString Text)
{
	XMLElement.element->SetText(TCHAR_TO_UTF8(*Text));
}

void UXMLBlueprintFunctionLibrary::BPL_SaveXMLToFile(const FXMLDocument& XMLDocument, FString FilePath)
{
	if (XMLDocument.doc->SaveFile(TCHAR_TO_UTF8(*FilePath))!= tinyxml2::XML_SUCCESS)
	{
		LogError("Failed to save XML file : %s ",UTF8_TO_TCHAR(XMLDocument.doc->ErrorStr()));
	}
}


