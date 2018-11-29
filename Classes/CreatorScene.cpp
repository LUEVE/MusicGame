#include "CreatorScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* CreatorScene::createScene()
{
	return CreatorScene::create();
}

bool CreatorScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// backbutton
	auto sprite_back = Sprite::create("back.png");
	auto sprite_backselected = Sprite::create("back_selected.png");
	auto menuBackItem = MenuItemSprite::create(sprite_back, sprite_backselected, sprite_back, CC_CALLBACK_1(CreatorScene::menuBackCallBack, this));
	menuBackItem->setPosition(Vec2(30, visibleSize.height - 30));
	auto menu0 = Menu::create(menuBackItem, NULL);
	menu0->setPosition(Vec2::ZERO);
	this->addChild(menu0);

	return true;
}

void CreatorScene::menuBackCallBack(Ref* pSender)
{
	Director::getInstance()->popScene();
}
