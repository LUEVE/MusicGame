#include "StartScene.h"
#include "SettingScene.h"
#include "MainGameScene.h"
#include "AboutScene.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

USING_NS_CC;

Scene* StartScene::createScene()
{
	return StartScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool StartScene::init()
{
	// initialize
	if (!Scene::init())
	{
		return false;
	}

	// Create the main menu
	this->createMenu();


	auto audio = SimpleAudioEngine::getInstance();

	audio->playBackgroundMusic("bgm.mp3", true);

	return true;
}

void StartScene::createMenu()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// load the Sprite Sheet
	auto spritecache = SpriteFrameCache::getInstance();
	spritecache->addSpriteFramesWithFile("buttons.plist");

	auto startSprite_normal = Sprite::createWithSpriteFrameName("start.png");
	auto startSprite_selected = Sprite::createWithSpriteFrameName("start_selected.png");
	auto startSprite_disabled = Sprite::createWithSpriteFrameName("start_disabled.png");
	auto startItem = MenuItemSprite::create(startSprite_normal, startSprite_selected, startSprite_disabled, CC_CALLBACK_1(StartScene::menuStartCallback, this));

	auto settingSprite_normal = Sprite::createWithSpriteFrameName("setting.png");
	auto settingSprite_selected = Sprite::createWithSpriteFrameName("setting_selected.png");
	auto settingSprite_disabled = Sprite::createWithSpriteFrameName("setting_disabled.png");
	auto settingItem = MenuItemSprite::create(settingSprite_normal, settingSprite_selected, settingSprite_disabled, CC_CALLBACK_1(StartScene::menuSettingCallback, this));

	auto aboutSprite_normal = Sprite::createWithSpriteFrameName("about.png");
	auto aboutSprite_selected = Sprite::createWithSpriteFrameName("about_selected.png");
	auto aboutSprite_disabled = Sprite::createWithSpriteFrameName("about_disabled.png");
	auto aboutItem = MenuItemSprite::create(aboutSprite_normal, aboutSprite_selected, aboutSprite_disabled, CC_CALLBACK_1(StartScene::menuAboutCallback, this));

	auto exitSprite_normal = Sprite::createWithSpriteFrameName("exit.png");
	auto exitSprite_selected = Sprite::createWithSpriteFrameName("exit_selected.png");
	auto exitSprite_disabled = Sprite::createWithSpriteFrameName("exit_disabled.png");
	auto exitItem = MenuItemSprite::create(exitSprite_normal, exitSprite_selected, exitSprite_disabled, CC_CALLBACK_1(StartScene::menuExitCallback, this));

	Vector<MenuItem*> menuItems;

	/*startItem->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 150));
	settingItem->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 50));
	aboutItem->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 50));
	exitItem->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 150));*/

	menuItems.pushBack(startItem);
	menuItems.pushBack(settingItem);
	menuItems.pushBack(aboutItem);
	menuItems.pushBack(exitItem);

	auto menu = Menu::createWithArray(menuItems);
	//menu->setPosition(Vec2::ZERO);
	menu->alignItemsVertically();
	//menu->alignItemsVerticallyWithPadding(20);
	this->addChild(menu, 1);
}

void StartScene::menuStartCallback(Ref* pSender)
{
	log("Start Button");
	auto maingameScene = MainGameScene::createScene();
	Director::getInstance()->pushScene(maingameScene);
}

void StartScene::menuSettingCallback(Ref* pSender)
{
	log("Setting Button");
	auto settingScene = SettingScene::createScene();
	Director::getInstance()->pushScene(settingScene);
}

void StartScene::menuAboutCallback(Ref* pSender)
{
	log("About Button");
	auto aboutScene = AboutScene::createScene();
	Director::getInstance()->pushScene(aboutScene);
}

void StartScene::menuExitCallback(Ref* pSender)
{
	Director::getInstance()->end();
}
