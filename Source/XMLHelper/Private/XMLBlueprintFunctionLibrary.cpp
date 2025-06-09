// Fill out your copyright notice in the Description page of Project Settings.


#include "XMLBlueprintFunctionLibrary.h"

#include "LogHelper.h"


bool UXMLBlueprintFunctionLibrary::IsXMLDocValid(const FXMLDocument& XMLDocument)
{
	return XMLDocument.doc != nullptr && XMLDocument.bIsValid;
}

bool UXMLBlueprintFunctionLibrary::IsXMLElementValid(const FXMLElement& XMLElement)
{
	return XMLElement.element != nullptr;
}

void UXMLBlueprintFunctionLibrary::BPL_LoadXMLFromFile(FString FilePath,FXMLDocument & XMLDocument)
{
	XMLDocument.doc = new tinyxml2::XMLDocument;
	if (!XMLDocument.doc)
	{
		LogError("Failed to create XML document");
		return;
	}
	tinyxml2::XMLError error = XMLDocument.doc->LoadFile(TCHAR_TO_UTF8(*FilePath));;
	if (error != tinyxml2::XMLError::XML_SUCCESS)
	{
		LogError("Failed to load XML from file {%s} : why {%s}",*FilePath,UTF8_TO_TCHAR(XMLDocument.doc->ErrorStr()));
		return;
	}
	LogDefault("Load XML Doc From File Success: %s",*FilePath)
	XMLDocument.bIsValid = true;
}

void UXMLBlueprintFunctionLibrary::BPL_LoadXMLFromXMLString(FString XMLString, FXMLDocument& XMLDocument)
{
	XMLDocument.doc = new tinyxml2::XMLDocument;
	if (!XMLDocument.doc)
	{
		LogError("Failed to create XML document");
		return;
	}
	tinyxml2::XMLError error = XMLDocument.doc->Parse(TCHAR_TO_UTF8(*XMLString));;
	if (error != tinyxml2::XMLError::XML_SUCCESS)
	{
		LogError("Failed to parse xml from string : why {%s}",UTF8_TO_TCHAR(XMLDocument.doc->ErrorStr()));
		return;
	}
	LogDefault("Load XML Doc From String Success")
	XMLDocument.bIsValid = true;
}

void UXMLBlueprintFunctionLibrary::BPL_UnloadXMLDocument(const FXMLDocument& XMLDocument)
{
	if (XMLDocument.doc)
	{
		delete XMLDocument.doc;
	}
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
	check(XMLElement.element)
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
	check(XMLElement.element)
	return UTF8_TO_TCHAR(XMLElement.element->GetText());
}

FString UXMLBlueprintFunctionLibrary::BPL_GetStringAttributeFromElement(const FXMLElement& XMLElement, FString Key)
{
	check(XMLElement.element)
	const char* result = nullptr;
	if (XMLElement.element->QueryStringAttribute(TCHAR_TO_UTF8(*Key),&result) == tinyxml2::XML_SUCCESS)
	{
		return UTF8_TO_TCHAR(result);
	}
	AssertLogVerify(false,"please check key or attribute is right")
	return TEXT("");
}

float UXMLBlueprintFunctionLibrary::BPL_GetFloatAttributeFromElement(const FXMLElement& XMLElement, FString Key)
{
	check(XMLElement.element)
	float v = 0.f;
	if (XMLElement.element->QueryFloatAttribute(TCHAR_TO_UTF8(*Key),&v) == tinyxml2::XML_SUCCESS)
	{
		return v;
	}
	AssertLogVerify(false,"please check key or attribute is right")
	return MAX_FLT;
}

bool UXMLBlueprintFunctionLibrary::BPL_GetBoolAttributeFromElement(const FXMLElement& XMLElement, FString Key)
{
	check(XMLElement.element)
	bool v = false;
	if (XMLElement.element->QueryBoolAttribute(TCHAR_TO_UTF8(*Key),&v) == tinyxml2::XML_SUCCESS)
	{
		return v;
	}
	AssertLogVerify(false,"please check key or attribute is right")
	return true;
}

double UXMLBlueprintFunctionLibrary::BPL_GetDoubleAttributeFromElement(const FXMLElement& XMLElement, FString Key)
{
	check(XMLElement.element)
	double v = 0;
	if (XMLElement.element->QueryDoubleAttribute(TCHAR_TO_UTF8(*Key),&v) == tinyxml2::XML_SUCCESS)
	{
		return v;
	}
	AssertLogVerify(false,"please check key or attribute is right")
	return 0;
}

int32 UXMLBlueprintFunctionLibrary::BPL_GetIntAttributeFromElement(const FXMLElement& XMLElement, FString Key)
{
	check(XMLElement.element)
	int32 v = 0;
	if (XMLElement.element->QueryIntAttribute(TCHAR_TO_UTF8(*Key),&v) == tinyxml2::XML_SUCCESS)
	{
		return v;
	}
	AssertLogVerify(false,"please check key or attribute is right")
	return 0;
}

int64 UXMLBlueprintFunctionLibrary::BPL_GetInt64AttributeFromElement(const FXMLElement& XMLElement, FString Key)
{
	check(XMLElement.element)
	int64 v = 0;
	if (XMLElement.element->QueryInt64Attribute(TCHAR_TO_UTF8(*Key),&v) == tinyxml2::XML_SUCCESS)
	{
		return v;
	}
	AssertLogVerify(false,"please check key or attribute is right")
	return 0;
}

FXMLAttribute UXMLBlueprintFunctionLibrary::BPL_FindAttribute(const FXMLElement& XMLElement, FString Key)
{
	FXMLAttribute XMLAttribute;
	if (XMLElement.element)
	{
		XMLAttribute.attribute = XMLElement.element->FindAttribute(TCHAR_TO_UTF8(*Key));
	}
	return XMLAttribute;
}

bool UXMLBlueprintFunctionLibrary::IsAttributeValid(const FXMLAttribute& XMLAttribute)
{
	return XMLAttribute.attribute != nullptr;
}

FXMLAttribute UXMLBlueprintFunctionLibrary::BPL_GetFirstAttribute(const FXMLElement& XMLElement)
{
	FXMLAttribute XMLAttribute;
	if (XMLElement.element)
	{
		XMLAttribute.attribute = XMLElement.element->FirstAttribute();
	}
	return XMLAttribute;
}

FXMLAttribute UXMLBlueprintFunctionLibrary::BPL_GetNextAttribute(const FXMLAttribute& XMLAttribute)
{
	FXMLAttribute Tmp;
	if (XMLAttribute.attribute)
	{
		Tmp.attribute = XMLAttribute.attribute->Next();
	}
	return Tmp;
}

bool UXMLBlueprintFunctionLibrary::AsBool(const FXMLAttribute& XMLAttribute)
{
	check(XMLAttribute.attribute != nullptr)
	return XMLAttribute.attribute->BoolValue();
}

double UXMLBlueprintFunctionLibrary::AsDouble(const FXMLAttribute& XMLAttribute)
{
	check(XMLAttribute.attribute != nullptr)
	return XMLAttribute.attribute->DoubleValue();
}

float UXMLBlueprintFunctionLibrary::AsFloat(const FXMLAttribute& XMLAttribute)
{
	check(XMLAttribute.attribute != nullptr)
	return XMLAttribute.attribute->FloatValue();
}

int64 UXMLBlueprintFunctionLibrary::AsInt64(const FXMLAttribute& XMLAttribute)
{
	check(XMLAttribute.attribute != nullptr)
	return XMLAttribute.attribute->Int64Value();
}

int32 UXMLBlueprintFunctionLibrary::AsInt(const FXMLAttribute& XMLAttribute)
{
	check(XMLAttribute.attribute != nullptr)
	return XMLAttribute.attribute->IntValue();
}

FString UXMLBlueprintFunctionLibrary::AsString(const FXMLAttribute& XMLAttribute)
{
	check(XMLAttribute.attribute != nullptr)
	return UTF8_TO_TCHAR(XMLAttribute.attribute->Value());
}

FXMLElement UXMLBlueprintFunctionLibrary::BPL_SetStringAttribute(const FXMLElement& XMLElement, FString Key , FString Value)
{
	check(XMLElement.element)
	XMLElement.element->SetAttribute(TCHAR_TO_UTF8(*Key),TCHAR_TO_UTF8(*Value));
	return XMLElement;
}

FXMLElement UXMLBlueprintFunctionLibrary::BPL_SetBoolAttribute(const FXMLElement& XMLElement, FString Key, bool Value)
{
	check(XMLElement.element)
	XMLElement.element->SetAttribute(TCHAR_TO_UTF8(*Key),Value);
	return XMLElement;
}

FXMLElement UXMLBlueprintFunctionLibrary::BPL_SetDoubleAttribute(const FXMLElement& XMLElement, FString Key, double Value)
{
	check(XMLElement.element)
	XMLElement.element->SetAttribute(TCHAR_TO_UTF8(*Key),Value);
	return XMLElement;
}

FXMLElement UXMLBlueprintFunctionLibrary::BPL_SetFloatAttribute(const FXMLElement& XMLElement, FString Key, float Value)
{
	check(XMLElement.element)
	XMLElement.element->SetAttribute(TCHAR_TO_UTF8(*Key),Value);
	return XMLElement;
}

FXMLElement UXMLBlueprintFunctionLibrary::BPL_DeleteAttribute(const FXMLElement& XMLElement, FString Key)
{
	// 不能使用空Key
	check(XMLElement.element && !Key.IsEmpty())
	XMLElement.element->DeleteAttribute(TCHAR_TO_UTF8(*Key));
	return XMLElement;
}

FXMLElement UXMLBlueprintFunctionLibrary::BPL_SetInt64Attribute(const FXMLElement& XMLElement, FString Key, int64 Value)
{
	check(XMLElement.element)
	XMLElement.element->SetAttribute(TCHAR_TO_UTF8(*Key),Value);
	return XMLElement;
}

FXMLElement UXMLBlueprintFunctionLibrary::BPL_SetIntAttribute(const FXMLElement& XMLElement, FString Key, int Value)
{
	check(XMLElement.element)
	XMLElement.element->SetAttribute(TCHAR_TO_UTF8(*Key),Value);
	return XMLElement;
}


FXMLDocument UXMLBlueprintFunctionLibrary::BPL_CreateRootXML(FString RootName)
{
	FXMLDocument XMLDoc;
	XMLDoc.doc = new tinyxml2::XMLDocument;
	XMLDoc.bIsValid = XMLDoc.doc ? true : false;
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
	check(XMLElement.element)
	XMLElement.element->SetText(TCHAR_TO_UTF8(*Text));
}

void UXMLBlueprintFunctionLibrary::BPL_SaveXMLToFile(const FXMLDocument& XMLDocument, FString FilePath)
{
	if (XMLDocument.doc->SaveFile(TCHAR_TO_UTF8(*FilePath))!= tinyxml2::XML_SUCCESS)
	{
		LogError("Failed to save XML file : %s ",UTF8_TO_TCHAR(XMLDocument.doc->ErrorStr()));
	}
}


