#include "StartScene.h"
#include "SettingScene.h"
#include "MainGameScene.h"
#include "AboutScene.h"
#include "SelectScene.h"
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

	auto visibleSize = Director::getInstance()->getVisibleSize();

	// Create background
	auto background = Sprite::create("background.png");
	background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(background, 1);

	// Create the main menu
	this->createMenu();

	auto audio = SimpleAudioEngine::getInstance();
	audio->playBackgroundMusic("bgm.mp3", true);
	audio->setBackgroundMusicVolume(0.75);

	return true;
}

void StartScene::createMenu()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto startItem = this->createSprite("START", CC_CALLBACK_1(StartScene::menuStartCallback, this));
	auto settingItem = this->createSprite("SETTING", CC_CALLBACK_1(StartScene::menuSettingCallback, this));
	auto aboutItem = this->createSprite("ABOUT", CC_CALLBACK_1(StartScene::menuAboutCallback, this));
	auto exitItem = this->createSprite("EXIT", CC_CALLBACK_1(StartScene::menuExitCallback, this));

	Vector<MenuItem*> menuItems;

	startItem->setPosition(Vec2(visibleSize.width / 2 - 110, visibleSize.height / 2 + 150));
	settingItem->setPosition(Vec2(visibleSize.width / 2 + 110, visibleSize.height / 2 + 50));
	aboutItem->setPosition(Vec2(visibleSize.width / 2 - 110, visibleSize.height / 2 - 50));
	exitItem->setPosition(Vec2(visibleSize.width / 2 + 110, visibleSize.height / 2 - 150));

	menuItems.pushBack(startItem);
	menuItems.pushBack(settingItem);
	menuItems.pushBack(aboutItem);
	menuItems.pushBack(exitItem);

	auto menu = Menu::createWithArray(menuItems);
	menu->setPosition(Vec2::ZERO);
	/*menu->alignItemsVertically();
	menu->alignItemsVerticallyWithPadding(30);*/
	this->addChild(menu);
}

/*
**	传入标签文本，回调函数，返回精灵菜单
*/
MenuItemSprite* StartScene::createSprite(string text, const ccMenuCallback& callback)
{
	auto Label = Label::createWithSystemFont(text, "CharlemagneStd-Bold", 32);
	auto Label2 = Label::createWithSystemFont(text, "CharlemagneStd-Bold", 30);
	auto Sprite_normal = Sprite::create("button_frame.png");
	Label->setPosition(Vec2(Sprite_normal->getContentSize().width / 2, Sprite_normal->getContentSize().height / 2));
	Sprite_normal->addChild(Label);
	auto Sprite_selected = Sprite::create("button_frame_selected.png");
	Label2->setPosition(Vec2(Sprite_selected->getContentSize().width / 2, Sprite_selected->getContentSize().height / 2));
	Sprite_selected->addChild(Label2);
	auto startItem = MenuItemSprite::create(Sprite_normal, Sprite_selected, Sprite_normal, callback);

	return startItem;
}

void StartScene::menuStartCallback(Ref* pSender)
{
	log("Start Button");
	auto selectScene = SelectScene::createScene();
	auto maingameScene = MainGameScene::createScene();
	Director::getInstance()->pushScene(TransitionFadeUp::create(0.5,selectScene));
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
