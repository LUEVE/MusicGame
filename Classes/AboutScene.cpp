#include "AboutScene.h"
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

	auto button = Button::create("back.png", "back_selected.png", "back_disabled.png");

	button->setPosition(Vec2(100, 50));
	button->addClickEventListener(CC_CALLBACK_1(AboutScene::btnBackCallback, this));

	this->addChild(button);

	return true;
}

void AboutScene::btnBackCallback(Ref* pSender)
{
	Director::getInstance()->popScene();
}
