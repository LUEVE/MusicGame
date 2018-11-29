#include "SettingScene.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

USING_NS_CC;

Scene* SettingScene::createScene()
{
	return SettingScene::create();
}


bool SettingScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto userdata = UserDefault::sharedUserDefault();

	/* Set background music volume */
	// label
	auto volumeLabel = Label::createWithSystemFont("Music Volume", "Arial", 24);
	volumeLabel->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 60));
	this->addChild(volumeLabel);
	// slider
	auto slider_bgm = Slider::create();
	slider_bgm->loadBarTexture("Slider_Back.png");
	slider_bgm->loadSlidBallTextures("SliderNode_Normal.png", "SliderNode_Press.png", "SliderNode_Disable.png");
	slider_bgm->loadProgressBarTexture("Slider_PressBar.png");
	slider_bgm->setPosition(Vec2(visibleSize.width / 2 + 10, visibleSize.height / 2 + 30));
	slider_bgm->setPercent(SimpleAudioEngine::getInstance()->getBackgroundMusicVolume() * 100.0f);
	slider_bgm->addEventListener(CC_CALLBACK_2(SettingScene::SliderBGMCallBack, this));
	this->addChild(slider_bgm);
	// On/Off button
	auto musicOnItem = MenuItemImage::create("volume_on.png", "volume_on.png");
	musicOnItem->setUserData((void *)"ON");
	auto musicOffItem = MenuItemImage::create("volume_off.png", "volume_off.png");
	musicOffItem->setUserData((void *)"OFF");
	auto menuToggle = MenuItemToggle::createWithCallback([=](Ref* obj) {
		MenuItemFont *item = (MenuItemFont*)((MenuItemToggle *)obj)->getSelectedItem();
		char* musicState = (char*)item->getUserData();
		if (musicState == "ON")
		{
			SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(userdata->getFloatForKey("backgroundmusic"));
			slider_bgm->setPercent(userdata->getFloatForKey("backgroundmusic") * 100.0f);
			slider_bgm->setColor(Color3B(255, 255, 255));
			slider_bgm->setEnabled(true);
			userdata->setBoolForKey("backgroundmusic_on", true);
		}
		else if(musicState == "OFF"){
			SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.0f);
			slider_bgm->setPercent(0);
			slider_bgm->setColor(cocos2d::Color3B::GRAY);
			slider_bgm->setEnabled(false);
			userdata->setBoolForKey("backgroundmusic_on", false);
		}
	}, musicOnItem, musicOffItem, NULL);
	if (userdata->getBoolForKey("backgroundmusic_on") == false) {
		menuToggle->setSelectedIndex(1);
		slider_bgm->setEnabled(false);
	}
	else
	{
		menuToggle->setSelectedIndex(0);
		slider_bgm->setEnabled(true);
	}
	menuToggle->setPosition(visibleSize.width / 2 - 80, visibleSize.height / 2 + 30);
	auto menu = Menu::create(menuToggle, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu, 5);


	/* Set sound effect volume */
	// label
	auto volumeLabel2 = Label::createWithSystemFont("Sound Effect Volume", "Arial", 24);
	volumeLabel2->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 30));
	this->addChild(volumeLabel2);
	// slider
	auto slider_eff = Slider::create();
	slider_eff->loadBarTexture("Slider_Back.png");
	slider_eff->loadSlidBallTextures("SliderNode_Normal.png", "SliderNode_Press.png", "SliderNode_Disable.png");
	slider_eff->loadProgressBarTexture("Slider_PressBar.png");
	slider_eff->setPosition(Vec2(visibleSize.width / 2 + 10, visibleSize.height / 2 - 60));
	slider_eff->setPercent(SimpleAudioEngine::getInstance()->getEffectsVolume() * 100.0f);
	slider_eff->addEventListener(CC_CALLBACK_2(SettingScene::SliderEffectCallBack, this));
	this->addChild(slider_eff);
	// On/Off button
	auto musicOnItem2 = MenuItemImage::create("volume_on.png", "volume_on.png");
	musicOnItem2->setUserData((void *)"ON");
	auto musicOffItem2 = MenuItemImage::create("volume_off.png", "volume_off.png");
	musicOffItem2->setUserData((void *)"OFF");
	auto menuToggle2 = MenuItemToggle::createWithCallback([=](Ref* obj) {
		MenuItemFont *item = (MenuItemFont*)((MenuItemToggle *)obj)->getSelectedItem();
		char* musicState = (char*)item->getUserData();
		if (musicState == "ON")
		{
			SimpleAudioEngine::getInstance()->setEffectsVolume(userdata->getFloatForKey("soundeffect"));
			slider_eff->setPercent(userdata->getFloatForKey("soundeffect") * 100.0f);
			slider_eff->setColor(Color3B(255, 255, 255));
			slider_eff->setEnabled(true);
			userdata->setBoolForKey("soundeffect_on", true);
		}
		else if (musicState == "OFF") {
			SimpleAudioEngine::getInstance()->setEffectsVolume(0.0f);
			slider_eff->setPercent(0);
			slider_eff->setColor(cocos2d::Color3B::GRAY);
			slider_eff->setEnabled(false);
			userdata->setBoolForKey("soundeffect_on", false);
		}
	}, musicOnItem2, musicOffItem2, NULL);
	if (userdata->getBoolForKey("soundeffect_on") == false) {
		menuToggle2->setSelectedIndex(1);
		slider_eff->setEnabled(false);
	}
	else
	{
		menuToggle2->setSelectedIndex(0);
		slider_eff->setEnabled(true);
	}
	menuToggle2->setPosition(visibleSize.width / 2 - 80, visibleSize.height / 2 - 60);
	auto menu2 = Menu::create(menuToggle2, NULL);
	menu2->setPosition(Point::ZERO);
	this->addChild(menu2, 5);


	// Keyboard listen ESC
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

void SettingScene::SliderBGMCallBack(Ref *pSender, Slider::EventType type) {
	auto item = (Slider*)(pSender);
	log("%i", item->getPercent());
	if (item->getPercent() == 100) {
		//item->setEnabled(false);
	}
	else {
		SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(item->getPercent() / 100.0f);
		UserDefault::sharedUserDefault()->setFloatForKey("backgroundmusic", item->getPercent() / 100.0f);
	}
}

void SettingScene::SliderEffectCallBack(Ref *pSender, Slider::EventType type) {
	auto item = (Slider*)(pSender);
	log("%i", item->getPercent());
	if (item->getPercent() == 100) {
		//item->setEnabled(false);
	}
	else {
		SimpleAudioEngine::getInstance()->setEffectsVolume(item->getPercent() / 100.0f);
		UserDefault::sharedUserDefault()->setFloatForKey("soundeffect", item->getPercent() / 100.0f);
	}
}
