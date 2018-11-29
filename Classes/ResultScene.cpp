#include "ResultScene.h"

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
	// TODO: allNotes是一个队列，装着这首歌的所有音符的消息
	// TODO : int allNoteNum = game.allNotes.size();
	int allNoteNum = 60;
	int scoreValue = calScoreValue(game.judgeCount[PERFECT], game.judgeCount[GREAT], game.judgeCount[GOOD], game.judgeCount[MISS], allNoteNum);
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

	scheduleOnce(schedule_selector(ResultScene::update), 0);

	return true;
}

void ResultScene::btnBackCallback(Ref* pSender) {
	Director::getInstance()->popScene();
}
