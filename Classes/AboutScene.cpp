﻿#include "AboutScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* AboutScene::createScene()
{
	return AboutScene::create();
}

bool AboutScene::init()
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
	auto menuBackItem = MenuItemSprite::create(sprite_back, sprite_backselected, sprite_back, CC_CALLBACK_1(AboutScene::menuBackCallBack, this));
	menuBackItem->setPosition(Vec2(30, visibleSize.height - 30));
	auto menu0 = Menu::create(menuBackItem, NULL);
	menu0->setPosition(Vec2::ZERO);
	this->addChild(menu0);

	return true;
}

void AboutScene::menuBackCallBack(Ref* pSender)
{
	Director::getInstance()->popScene();
}
