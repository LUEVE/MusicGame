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

	auto backButton = Button::create("back.png", "back_selected.png", "back_disabled.png");
	backButton->setPosition(Vec2(100, 50));
	backButton->addClickEventListener(CC_CALLBACK_1(SettingScene::btnBackCallback, this));
	this->addChild(backButton);

	auto volumeLabel = Label::createWithSystemFont("Volume", "Arial", 24);
	volumeLabel->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 30));
	this->addChild(volumeLabel);

	auto slider = Slider::create();
	slider->loadBarTexture("Slider_Back.png");
	slider->loadSlidBallTextures("SliderNode_Normal.png", "SliderNode_Press.png", "SliderNode_Disable.png");
	slider->loadProgressBarTexture("Slider_PressBar.png");
	slider->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	slider->setPercent(75);

	slider->addEventListener(CC_CALLBACK_2(SettingScene::SliderCallBack, this));

	this->addChild(slider);

	return true;
}

void SettingScene::SliderCallBack(Ref *pSender, Slider::EventType type) {
	auto item = (Slider*)(pSender);
	log("%i", item->getPercent());
	if (item->getPercent() == 100) {
		//item->setEnabled(false);
	}
	else {
		SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(item->getPercent() / 100.0f);
	}
}

void SettingScene::btnBackCallback(Ref* pSender)
{
	Director::getInstance()->popScene();
}

