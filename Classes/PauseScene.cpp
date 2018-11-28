#include "PauseScene.h"
#include "SettingScene.h"
#include "SimpleAudioEngine.h"
#include "MainGameScene.h"

USING_NS_CC;

//Scene* PauseScene::createScene(RenderTexture* sqr)
//{
//	Scene* scene = Scene::create();
//	PauseScene* layer = PauseScene::create();
//	scene->addChild(layer, 1);
//
//	auto visibleSize = Director::getInstance()->getVisibleSize();
//	auto background = Sprite::createWithTexture(sqr->getSprite()->getTexture());
//	background->setPosition(visibleSize.width / 2, visibleSize.height / 2);
//	background->setFlipY(true);
//	scene->addChild(background);
//
//	return scene;
//}

Scene* PauseScene::createScene()
{
	Scene* scene = Scene::create();
	PauseScene* layer = PauseScene::create();
	scene->addChild(layer, 1);

	return scene;
}

bool PauseScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto resumeLabel = Label::createWithSystemFont("Resume", "Arial", 24);
	auto resumeItem = MenuItemLabel::create(resumeLabel, CC_CALLBACK_1(PauseScene::menuResumeCallback, this));
	auto settingLabel = Label::createWithSystemFont("Setting", "Arial", 24);
	auto settingItem = MenuItemLabel::create(settingLabel, CC_CALLBACK_1(PauseScene::menuSettingCallback, this));
	auto exitLabel = Label::createWithSystemFont("Exit", "Arial", 24);
	auto exitItem = MenuItemLabel::create(exitLabel, CC_CALLBACK_1(PauseScene::menuExitCallback, this));
	auto restartLabel = Label::createWithSystemFont("Restart", "Arial", 24);
	auto restartItem = MenuItemLabel::create(restartLabel, CC_CALLBACK_1(PauseScene::menuRestartCallback, this));
	Vector<MenuItem*> menuItems;

	menuItems.pushBack(restartItem);
	menuItems.pushBack(resumeItem);
	menuItems.pushBack(settingItem);
	menuItems.pushBack(exitItem);
	
	auto menu = Menu::createWithArray(menuItems);
	//menu->setPosition(Vec2::ZERO);
	menu->alignItemsVertically();
	//menu->alignItemsVerticallyWithPadding(20);
	this->addChild(menu);
	
	// keyboard listen
	auto listen1 = EventListenerKeyboard::create();

	listen1->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event * event) {
		switch (keyCode)
		{
		case EventKeyboard::KeyCode::KEY_ESCAPE:
			Director::getInstance()->popScene();
			break;
		default:
			break;
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listen1, this);

	return true;
}

void PauseScene::menuResumeCallback(Ref* pSender)
{
	log("Resume Button");
	Director::getInstance()->popScene();
	//Director::sharedDirector()->replaceScene(MainGameScene::createScene());
}

void PauseScene::menuSettingCallback(Ref* pSender)
{
	log("Setting Button");
	auto settingScene = SettingScene::createScene();
	Director::getInstance()->pushScene(settingScene);
}

void PauseScene::menuExitCallback(Ref* pSender)
{
	log("Exit Button");
	Director::getInstance()->popToRootScene();
}

void PauseScene::menuRestartCallback(cocos2d::Ref* pSender)
{
	log("ReStart Button");
	Director::getInstance()->popScene();
	Director::sharedDirector()->replaceScene(MainGameScene::createScene());
}
