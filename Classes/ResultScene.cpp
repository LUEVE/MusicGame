#include "ResultScene.h"

USING_NS_CC;

ResultScene* ResultScene::createScene() {
	return ResultScene::create();
}

void ResultScene::update(float dt) {

}



bool ResultScene::init() {
	if (!Scene::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto backButton = Button::create("back.png", "back_selected.png", "back_disabled.png");
	backButton->setPosition(Vec2(100, 50));
	backButton->addClickEventListener(CC_CALLBACK_1(ResultScene::btnBackCallback, this));
	this->addChild(backButton);

	auto perfectSprite = SG_Note::create("perfect_result.png");
	perfectSprite->setPosition(Vec2(visibleSize.width / 10 * 2, visibleSize.height / 10 * 7.5));
	this->addChild(perfectSprite);

	auto greatSprite = SG_Note::create("great_result.png");
	greatSprite->setPosition(Vec2(visibleSize.width / 10 * 2, visibleSize.height / 10 * 6));
	this->addChild(greatSprite);

	auto goodSprite = SG_Note::create("good_result.png");
	goodSprite->setPosition(Vec2(visibleSize.width / 10 * 2, visibleSize.height / 10 * 4.5));
	this->addChild(goodSprite);
	
	auto missSprite = SG_Note::create("miss_result.png");
	missSprite->setPosition(Vec2(visibleSize.width / 10 * 2, visibleSize.height / 10 * 3));
	this->addChild(missSprite);


	log("ResultScene created");

	return true;
}

void ResultScene::btnBackCallback(Ref* pSender) {
	Director::getInstance()->popScene();
}
