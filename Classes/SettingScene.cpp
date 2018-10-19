#include "SettingScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* SettingScene::createScene()
{
	return SettingScene::create();
}


static cocos2d::Size designResolutionSize = cocos2d::Size(1440, 900);
static cocos2d::Size smallResolutionSize = cocos2d::Size(480, 320);
static cocos2d::Size mediumResolutionSize = cocos2d::Size(1024, 768);
//static cocos2d::Size largeResolutionSize = cocos2d::Size(2048, 1536);
static cocos2d::Size largeResolutionSize = cocos2d::Size(1920, 1080);

bool SettingScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto backButton = Button::create("back.png", "back_selected.png", "back_disabled.png");
	//backButton->setPosition(Vec2(250, 250));
	backButton->addClickEventListener(CC_CALLBACK_1(SettingScene::btnBackCallback, this));
	this->addChild(backButton);

	auto fullScreenCheckbox = CheckBox::create("check_box_normal.png",
		"check_box_normal_press.png",
		"check_box_active.png",
		"check_box_normal_disable.png",
		"check_box_active_disable.png");
	fullScreenCheckbox->addEventListener([&](Ref* sender, CheckBox::EventType type) {
		Size frameSize;
		switch (type)
		{
			/*
			Why the output is :
			0.000000 0.000000
			0.000000 0.000000
			*/
		case cocos2d::ui::CheckBox::EventType::SELECTED:
			Director::getInstance()->getOpenGLView()->setDesignResolutionSize(largeResolutionSize.width, largeResolutionSize.height, ResolutionPolicy::EXACT_FIT);
			visibleSize = Director::getInstance()->getVisibleSize(); 
			Director::getInstance()->getOpenGLView()->setFullscreen();
			log("%f %f", visibleSize.width, visibleSize.height);
			break;
		case cocos2d::ui::CheckBox::EventType::UNSELECTED:
			Director::getInstance()->getOpenGLView()->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::EXACT_FIT);
			visibleSize = Director::getInstance()->getVisibleSize();
			Director::getInstance()->getOpenGLView()->setWindowed(designResolutionSize.width, designResolutionSize.height);
			log("%f %f", visibleSize.width, visibleSize.height);
			break;
		default:
			break;
		}
	});
	fullScreenCheckbox->setPosition(Vec2(visibleSize.width / 2 - 50, visibleSize.height / 2));
	this->addChild(fullScreenCheckbox);

	auto fullScreenText = Text::create("Full-Screen", "Arial", 24);


	fullScreenText->setPosition(Vec2(visibleSize.width / 2 + 50, visibleSize.height / 2));
	this->addChild(fullScreenText);

	return true;
}

void SettingScene::btnBackCallback(Ref* pSender)
{
	Director::getInstance()->popScene();
}
