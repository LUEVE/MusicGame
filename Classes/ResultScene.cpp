﻿#include "ResultScene.h"

USING_NS_CC;

ResultScene* ResultScene::createScene() {
	return ResultScene::create();
}

void ResultScene::update(float dt) {
	auto visibleSize = Director::getInstance()->getVisibleSize();
	for (int i = 1; i < JUDGE_NUM; ++i) {
		this->judgeLabel[i] = Label::createWithSystemFont("x " + to_string(this->game.judgeCount[i]), "Consolas", 30);
		this->judgeLabel[i]->setPosition(Vec2(visibleSize.width / 10 * 4, visibleSize.height / 10 * (JUDGE_NUM - i) * 1.5 + 115));
		this->addChild(judgeLabel[i]);
	}

	scoreLabel = Label::createWithSystemFont("total score : " + to_string(this->game.gameScore), "Consolas", 40);
	scoreLabel->setPosition(Vec2(visibleSize.width / 10 * 4, visibleSize.height / 10 * 9));
	this->addChild(scoreLabel);

	int rank;
	// allNotes是一个队列，装着这首歌的所有音符的消息
	// BUG : 不知道为什么这里的size()会返回0
	// int allNoteNum = game.allNotes.size();

	int allNoteNum = 0;
	for(int i = 1; i < JUDGE_NUM; ++i) {
		allNoteNum += game.judgeCount[i];
	}

	double scoreValue = calScoreValue(game.judgeCount[PERFECT], game.judgeCount[GREAT], game.judgeCount[GOOD], game.judgeCount[MISS], allNoteNum);
	if(game.judgeCount[MISS] == 0 && game.judgeCount[GOOD] == 0) {
		rank = SS_RANK;
	}
	else if(game.judgeCount[MISS] == 0) {
		rank = S_RANK;
	}
	else if(scoreValue > 0.7) {
		rank = A_RANK;
	}
	else if(scoreValue > 0.5) {
		rank = B_RANK;
	}
	else if(scoreValue > 0.3) {
		rank = C_RANK;
	}
	else {
		rank = D_RANK;
	}
	SG_Note *rankPic;
	switch (rank) {
	case SS_RANK:
		rankPic = SG_Note::create("ss.png");
		break;
	case S_RANK:
		rankPic = SG_Note::create("s.png");
		break;
	case A_RANK:
		rankPic = SG_Note::create("a.png");
		break;
	case B_RANK:
		rankPic = SG_Note::create("b.png");
		break;
	case C_RANK:
		rankPic = SG_Note::create("c.png");
		break;
	case D_RANK:
		rankPic = SG_Note::create("d.png");
		break;
	}
	rankPic->setPosition(Vec2(visibleSize.width / 10 * 8, visibleSize.height / 10 * 5.5));
	this->addChild(rankPic);

}



bool ResultScene::init() {
	if (!Scene::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	
	// backbutton
	auto sprite_back = Sprite::create("back.png");
	auto sprite_backselected = Sprite::create("back_selected.png");
	auto menuBackItem = MenuItemSprite::create(sprite_back, sprite_backselected, sprite_back, CC_CALLBACK_1(ResultScene::menuBackCallBack, this));
	menuBackItem->setPosition(Vec2(30, visibleSize.height - 30));
	auto menu0 = Menu::create(menuBackItem, NULL);
	menu0->setPosition(Vec2::ZERO);
	this->addChild(menu0);

	auto perfectSprite = SG_Note::create("Judge/perfect_result.png");
	perfectSprite->setPosition(Vec2(visibleSize.width / 10 * 2, visibleSize.height / 10 * 7.5));
	this->addChild(perfectSprite);

	auto greatSprite = SG_Note::create("Judge/great_result.png");
	greatSprite->setPosition(Vec2(visibleSize.width / 10 * 2, visibleSize.height / 10 * 6));
	this->addChild(greatSprite);

	auto goodSprite = SG_Note::create("Judge/good_result.png");
	goodSprite->setPosition(Vec2(visibleSize.width / 10 * 2, visibleSize.height / 10 * 4.5));
	this->addChild(goodSprite);
	
	auto missSprite = SG_Note::create("Judge/miss_result.png");
	missSprite->setPosition(Vec2(visibleSize.width / 10 * 2, visibleSize.height / 10 * 3));
	this->addChild(missSprite);

	log("ResultScene created");

	scheduleOnce(schedule_selector(ResultScene::update), 0);

	return true;
}

void ResultScene::menuBackCallBack(Ref* pSender) {
	Director::getInstance()->popScene();
}
