// Fill out your copyright notice in the Description page of Project Settings.


#include "TestXML.h"

#include "LogHelper.h"

#include "tinyxml2/tinyxml2.h"

// Sets default values
ATestXML::ATestXML()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATestXML::BeginPlay()
{
	Super::BeginPlay();

	if (!bEnableTest)
	{
		LogWarning("not enable to run test")
		return;
	}
	
	tinyxml2::XMLDocument doc;
	tinyxml2::XMLError error = doc.LoadFile(TCHAR_TO_UTF8(TEXT("D:\\Projects\\B1\\Plugins\\XMLHelper\\test_example\\example_01.xml")));
	if (error != tinyxml2::XMLError::XML_SUCCESS)
	{
		LogError("Failed to load XML file: %s",UTF8_TO_TCHAR(doc.ErrorStr()))
		return;
	}

	LogWarning("load xml file success")

	LogWarning("ChildElementCount: %d",doc.ChildElementCount())
	LogWarning("ChildElementCount(\"Root\"): %d",doc.ChildElementCount("Root"))

	tinyxml2::XMLElement* titleElement = doc.FirstChildElement()->FirstChildElement();
	LogWarning("root.title:%s",UTF8_TO_TCHAR(titleElement->GetText()))

	tinyxml2::XMLElement* idElement = doc.FirstChildElement()->FirstChildElement()->NextSiblingElement();
	LogWarning("root.id:%s",UTF8_TO_TCHAR(idElement->GetText()))

	tinyxml2::XMLElement* nameElement = doc.FirstChildElement()->FirstChildElement("Person")->FirstChildElement("Name");
	LogWarning("root.person.name:%s",UTF8_TO_TCHAR(nameElement->GetText()))
	tinyxml2::XMLElement* ageElement = doc.FirstChildElement()->FirstChildElement("Person")->FirstChildElement("Age");
	LogWarning("root.person.age:%s",UTF8_TO_TCHAR(ageElement->GetText()))


	tinyxml2::XMLElement* posListElement = doc.FirstChildElement()->FirstChildElement("PosList");
	int32 loopCount = posListElement->ChildElementCount("xpos");
	LogWarning("get %d (xpos,ypos)",loopCount)

	tinyxml2::XMLElement* xposElement = posListElement->FirstChildElement("xpos");
	tinyxml2::XMLElement* yposElement = posListElement->FirstChildElement("ypos");
	LogWarning("(%s,%s)",UTF8_TO_TCHAR(xposElement->GetText()),UTF8_TO_TCHAR(yposElement->GetText()))
	
	for (int32 i = 1; i < loopCount; ++i)
	{
		xposElement = xposElement->NextSiblingElement("xpos");
		yposElement = yposElement->NextSiblingElement("ypos");
		LogWarning("(%s,%s)",UTF8_TO_TCHAR(xposElement->GetText()),UTF8_TO_TCHAR(yposElement->GetText()))
	}

	// node是XMLElement的基类
	tinyxml2::XMLNode* rootNode = doc.FirstChildElement();
	LogError("rootNode's child element count %d",rootNode->ChildElementCount())
	tinyxml2::XMLNode* titleNode = rootNode->FirstChild();
	if (titleNode)
	{
		LogWarning("titleNode's value:%s",UTF8_TO_TCHAR(titleNode->Value()))
	}

	// this will cant get the value
	tinyxml2::XMLNode* rootNode2 = doc.FirstChild();
	LogError("rootNode2's child element count %d",rootNode2->ChildElementCount())
	tinyxml2::XMLNode* titleNode2 = rootNode->FirstChild();
	if (titleNode2)
	{
		LogWarning("titleNode2's value:%s",UTF8_TO_TCHAR(titleNode2->Value()))
	}
	
	
	// write data
	tinyxml2::XMLDocument doc2;
	tinyxml2::XMLElement* doc2RootElement = doc2.RootElement();
	if (!doc2RootElement)
	{
		LogWarning("Doc2 root element is nullptr , will set it ")
	}
	else
	{
		LogWarning("doc2 has root element")
	}
	
	tinyxml2::XMLNode* rootNode3 = doc2.InsertEndChild(doc2.NewElement("Root"));
	tinyxml2::XMLNode* newTitleElement = rootNode3->InsertEndChild(doc2.NewElement("title"));
	newTitleElement->ToElement()->SetText("Hello World");;

	tinyxml2::XMLElement* rootElement3 = rootNode3->ToElement();
	tinyxml2::XMLElement* newPersonElement = rootElement3->InsertNewChildElement("person");
	newPersonElement->InsertNewChildElement("name")->SetText("LiSi");
	newPersonElement->InsertNewChildElement("age")->SetText("24");

	// try two root
	// 写入两个根节点
	// 虽然可以正常写出(写出文件里面数据是对的),但是无法预览
	// XML只支持一个根节点
	tinyxml2::XMLNode* playNode = doc2.InsertEndChild(doc2.NewElement("PLAY"));
	tinyxml2::XMLNode* playNameNode = playNode->InsertEndChild(doc2.NewElement("name"));
	playNameNode->ToElement()->SetText("ARK");
	
	
	tinyxml2::XMLError writeError = doc2.SaveFile("D:\\Projects\\B1\\Plugins\\XMLHelper\\test_example\\example_out.xml");
	if (writeError != tinyxml2::XMLError::XML_SUCCESS)
	{
		LogError("failed to save XML file : %s", UTF8_TO_TCHAR(doc2.ErrorStr()));
		return;
	}
	LogWarning("write xml file success")

	// try copy
	tinyxml2::XMLDocument targetDoc;
	doc.DeepCopy(&targetDoc);
	LogError("after deep copy")
	LogWarning("source doc's title:%s",UTF8_TO_TCHAR(doc.FirstChildElement()->FirstChildElement()->GetText()))
	LogWarning("target doc's title:%s",UTF8_TO_TCHAR(targetDoc.FirstChildElement()->FirstChildElement()->GetText()))

	tinyxml2::XMLElement* targetPerson = targetDoc.FirstChildElement()->FirstChildElement("Person");
	LogWarning("get target doc's child node person result: %s ",targetPerson?TEXT("TRUE"):TEXT("FALSE"))
	if (targetPerson)
	{
		LogWarning("target person's name:%s",UTF8_TO_TCHAR(targetPerson->FirstChildElement("Name")->GetText()))
	}
	
	LogWarning("insert data to source")
	doc.FirstChildElement()->InsertNewChildElement("Insert")->SetText("this is insert data");
	
	// find failed
	tinyxml2::XMLElement* findElement = targetDoc.FirstChildElement()->FirstChildElement("Insert");
	LogWarning("try find data from target doc :%s",findElement?TEXT("TRUE"):TEXT("FALSE"))

	// DeepClone可以递归复制当前节点下的全部节点 DeepClone中的参数为目标文档的Document对象
	// doc.DeepClone();

	// ShallowClone仅复制当前节点
	// doc.ShallowClone();
}
