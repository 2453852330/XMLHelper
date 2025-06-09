// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XMLType.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "XMLBlueprintFunctionLibrary.generated.h"



UCLASS()
class XMLHELPER_API UXMLBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	// 检测一个XMLDocument结构是否有效?
	UFUNCTION(BlueprintPure,Category="XMLHelper")
	static bool IsXMLDocValid(const FXMLDocument & XMLDocument);

	// 检测一个XMLElement结构是否有效?
	UFUNCTION(BlueprintPure,Category="XMLHelper")
	static bool IsXMLElementValid(const FXMLElement & XMLElement);
	
	
	// 从文件加载XML结构
	UFUNCTION(BlueprintPure,Category="XMLHelper")
	static void BPL_LoadXMLFromFile(FString FilePath,FXMLDocument & XMLDocument);

	// 从字符串中构建XML结构
	UFUNCTION(BlueprintPure,Category="XMLHelper")
	static void BPL_LoadXMLFromXMLString(FString XMLString,FXMLDocument & XMLDocument);

	// 释放一个XMLDocument内存 , LoadXML 中使用 new 创建了对象,所以需要手动 delete
	UFUNCTION(BlueprintCallable,Category="XMLHelper")
	static void BPL_UnloadXMLDocument(const FXMLDocument & XMLDocument);
	
	// 获取第一个子节点元素从XML结构,Key是可空的;
	UFUNCTION(BlueprintPure,Category="XMLHelper")
	static FXMLElement BPL_GetFirstChildElementFromDoc(const FXMLDocument& XMLDocument, FString Key);

	// 获取某个子元素的子元素,key是可空的
	UFUNCTION(BlueprintPure,Category="XMLHelper")
	static FXMLElement BPL_GetFirstChildElementFromElement(const FXMLElement& XMLElement, FString Key);

	// 获取根元素
	UFUNCTION(BlueprintPure,Category="XMLHelper")
	static FXMLElement BPL_GetRootElement(const FXMLDocument& XMLDocument);

	// 从XML结构中获取子元素的数量
	UFUNCTION(BlueprintPure,Category="XMLHelper")
	static int32 BPL_GetCountFromDocument(const FXMLDocument& XMLDocument,FString Key);

	// 从XMLElement中获取子元素的数量
	UFUNCTION(BlueprintPure,Category="XMLHelper")
	static int32 BPL_GetCountFromElement(const FXMLElement& XMLElement,FString Key);	

	// 获取一个元素的下一个同级元素,Key可空;若Key为空,获取下一个结构同级元素;若有Key,获取下一个同级同名元素;
	UFUNCTION(BlueprintPure,Category="XMLHelper")
	static FXMLElement BPL_GetNextSiblingElement(const FXMLElement& XMLElement,FString Key);

	// 获取一个元素的上一个同级元素,Key可空;若Key为空,获取上一个结构同级元素;若有Key,获取上一个同级同名元素;
	UFUNCTION(BlueprintPure,Category="XMLHelper")
	static FXMLElement BPL_GetPreviousSiblingElement(const FXMLElement& XMLElement,FString Key);
	
	// 获取一个元素的文本值,使用IsXMLElementValid()确保该元素可用;
	UFUNCTION(BlueprintPure,Category="XMLHelper")
	static FString BPL_GetElementText(const FXMLElement& XMLElement);

	// Attribute --------------------------------------------------------------------------------------------------

	// 获取一个元素的string属性值,Key是属性名称,不可为空
	UFUNCTION(BlueprintPure,Category="XMLHelper")
	static FString BPL_GetStringAttributeFromElement(const FXMLElement& XMLElement, FString Key);
	
	// 获取一个元素的float属性值,Key是属性名称,不可为空
	UFUNCTION(BlueprintPure,Category="XMLHelper")
	static float BPL_GetFloatAttributeFromElement(const FXMLElement& XMLElement, FString Key);

	// 获取一个元素的bool属性值,Key是属性名称,不可为空
	UFUNCTION(BlueprintPure,Category="XMLHelper")
	static bool BPL_GetBoolAttributeFromElement(const FXMLElement& XMLElement, FString Key);

	// 获取一个元素的double属性值,Key是属性名称,不可为空
	UFUNCTION(BlueprintPure,Category="XMLHelper")
	static double BPL_GetDoubleAttributeFromElement(const FXMLElement& XMLElement, FString Key);

	// 获取一个元素的Int属性值,Key是属性名称,不可为空
	UFUNCTION(BlueprintPure,Category="XMLHelper")
	static int32 BPL_GetIntAttributeFromElement(const FXMLElement& XMLElement, FString Key);

	// 获取一个元素的Int64属性值,Key是属性名称,不可为空
	UFUNCTION(BlueprintPure,Category="XMLHelper")
	static int64 BPL_GetInt64AttributeFromElement(const FXMLElement& XMLElement, FString Key);

	// 寻找一个属性
	UFUNCTION(BlueprintPure,Category="XMLHelper")
	static FXMLAttribute BPL_FindAttribute(const FXMLElement& XMLElement, FString Key);

	// 检测一个属性是否有效
	UFUNCTION(BlueprintPure,Category="XMLHelper")
	static bool IsAttributeValid(const FXMLAttribute& XMLAttribute);
	
	// 获取某个元素的第一个属性
	UFUNCTION(BlueprintPure,Category="XMLHelper")
	static FXMLAttribute BPL_GetFirstAttribute(const FXMLElement& XMLElement);

	// 获取当前属性的下一个属性
	UFUNCTION(BlueprintPure,Category="XMLHelper")
	static FXMLAttribute BPL_GetNextAttribute(const FXMLAttribute& XMLAttribute);

	// 获取某个属性的bool值
	UFUNCTION(BlueprintPure,Category="XMLHelper")
	static bool AsBool(const FXMLAttribute& XMLAttribute);

	// 获取某个属性的double值
	UFUNCTION(BlueprintPure,Category="XMLHelper")
	static double AsDouble(const FXMLAttribute& XMLAttribute);
	
	// 获取某个属性的float值
	UFUNCTION(BlueprintPure,Category="XMLHelper")
	static float AsFloat(const FXMLAttribute& XMLAttribute);

	// 获取某个属性的int64值
	UFUNCTION(BlueprintPure,Category="XMLHelper")
	static int64 AsInt64(const FXMLAttribute& XMLAttribute);

	// 获取某个属性的int值
	UFUNCTION(BlueprintPure,Category="XMLHelper")
	static int32 AsInt(const FXMLAttribute& XMLAttribute);
	
	// 获取某个属性的string值
	UFUNCTION(BlueprintPure,Category="XMLHelper")
	static FString AsString(const FXMLAttribute& XMLAttribute);
	
	
	// 蓝图不支持 uint32,uint64,不提供 QueryUnsignedAttribute() + QueryUnsigned64Attribute()
	// 获取一个元素的Unsigned属性值,Key是属性名称,不可为空
	// 获取一个元素的Unsigned64属性值,Key是属性名称,不可为空

	// 设置一个string属性
	UFUNCTION(BlueprintCallable,Category="XMLHelper")
	static FXMLElement BPL_SetStringAttribute(const FXMLElement& XMLElement, FString Key , FString Value);

	// 设置一个bool属性
	UFUNCTION(BlueprintCallable,Category="XMLHelper")
	static FXMLElement BPL_SetBoolAttribute(const FXMLElement& XMLElement, FString Key , bool Value);

	// 设置一个double属性
	UFUNCTION(BlueprintCallable,Category="XMLHelper")
	static FXMLElement BPL_SetDoubleAttribute(const FXMLElement& XMLElement, FString Key , double Value);

	// 设置一个float属性
	UFUNCTION(BlueprintCallable,Category="XMLHelper")
	static FXMLElement BPL_SetFloatAttribute(const FXMLElement& XMLElement, FString Key , float Value);

	// 设置一个int64属性
	UFUNCTION(BlueprintCallable,Category="XMLHelper")
	static FXMLElement BPL_SetInt64Attribute(const FXMLElement& XMLElement, FString Key , int64 Value);

	// 设置一个int属性
	UFUNCTION(BlueprintCallable,Category="XMLHelper")
	static FXMLElement BPL_SetIntAttribute(const FXMLElement& XMLElement, FString Key , int Value);

	// 移除某个元素的key属性,Key不能为空
	UFUNCTION(BlueprintCallable,Category="XMLHelper")
	static FXMLElement BPL_DeleteAttribute(const FXMLElement& XMLElement, FString Key);
	
	// 创建一个XMLDocument,传入根节点的name
	UFUNCTION(BlueprintPure,Category="XMLHelper")
	static FXMLDocument BPL_CreateRootXML(FString RootName);

	// 插入一个Element到Document中
	UFUNCTION(BlueprintPure,Category="XMLHelper")
	static FXMLElement BPL_InsertElementToDocument(const FXMLDocument & XMLDocument,FString ElementName);

	// 插入一个Element到Element中
	UFUNCTION(BlueprintPure,Category="XMLHelper")
	static FXMLElement BPL_InsertElementToElement(const FXMLElement & XMLElement,FString ElementName);

	// 设置一个Element的text文本
	UFUNCTION(BlueprintCallable,Category="XMLHelper")
	static void BPL_SetElementText(const FXMLElement & XMLElement, FString Text);

	// 保存一个XMLDocument到文件
	UFUNCTION(BlueprintCallable,Category="XMLHelper")
	static void BPL_SaveXMLToFile(const FXMLDocument& XMLDocument,FString FilePath);
};



