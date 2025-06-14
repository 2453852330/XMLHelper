// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TestXML.generated.h"

/*
 * this file is the test class of HOW TO USE TinyXML2 Lib
 * 这是个测试类,正式使用时可以删除掉这个类
 * TextXML.h + TestXML.cpp
 */

UCLASS()
class XMLHELPER_API ATestXML : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATestXML();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere,Category="TEST")
	bool bEnableTest = false;
};
