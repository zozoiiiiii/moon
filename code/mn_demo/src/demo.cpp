#include "demo.h"
#include "public/ecs/mn_entity.h"

// color: a r g b
#define COLOR_RED 0xFFFF0000
#define COLOR_GREE 0xFF00FF00
#define COLOR_BLUE 0xFF0000FF
#define COLOR_EDITOR 0xFF535353
#define COLOR_TREEITEM_HIGHLIGHT 0xFF3A3A3A

void Demo::OnCreate()
{
	CreateTestUI();




	//BaseObject* pNewItem = BaseObject::parseFromFile(GetObjectMgr(),  "D:\\projects\\yakyak\\bin\\res\\ui_layout\\test.json");
	//Item* pItem = (Item*)GetObjectMgr()->create("Item");
	//Item* pItem1 = (Item*)GetObjectMgr()->create("Item");
	//pItem->AddChild(pItem1);
	//pItem->serializeToFile("D:\\projects\\yakyak\\bin\\res\\ui_layout\\test.json");
}

void Demo::CreateTestUI()
{
    MN::Entity* pMainEntity = (MN::Entity*)GetObjectMgr()->create("Entity");

	{
        MN::Entity* pItem = (MN::Entity*)GetObjectMgr()->create("Item");
        MN::Component* pRectangle = pItem->AddComponent("RectangleComponent");

        unsigned int color = COLOR_GREE;
		pRectangle->Invoke(NULL, "SetColor", &color);

        int width=100;
        int height=100;
        bool visible=true;
		pItem->SetFieldVal("width", &width);
		pItem->SetFieldVal("height", &height);
		pItem->SetFieldVal("visible", &visible);
		pMainEntity->AddChild(pItem);
	}
/*
	{
		Item* pItem = (Item*)GetObjectMgr()->create("Item");
		TextComponent* pText = (TextComponent*)pItem->AddComponent("TextComponent");
		pText->SetText("hello, world");
		pItem->SetLeft(100);
		pItem->SetWidth(100);
		pItem->SetHeight(100);
		pItem->SetVisible(true);
		pMainEntity->AddChild(pItem);
	}

	{
		Item* pItem = (Item*)GetObjectMgr()->create("Item");
		ImageComponent* pImage = (ImageComponent*)pItem->AddComponent("ImageComponent");
		pImage->SetImageSource("ui_image/grass.bmp");
		pItem->SetLeft(500);
		pItem->SetWidth(100);
		pItem->SetHeight(100);
		pItem->SetVisible(true);
		pMainEntity->AddChild(pItem);
	}*/

	pMainEntity->serializeToFile("ttt.xml");
}

void Demo::OnDestroy()
{
    //GetMgr()->RemoveExcute(this);
}

void Demo::OnExcute(float sec)
{
}