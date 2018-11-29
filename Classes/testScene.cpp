#include "testScene.h"
#include "SimpleAudioEngine.h"
#include "ui/UIButton.h"

testScene::testScene() : Scene(), scoreIfs("D:\\score.txt") {}

using namespace std::chrono;

bool testScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto sae = CocosDenshion::SimpleAudioEngine::getInstance();

	sae->stopBackgroundMusic();
	sae->playBackgroundMusic("Wiwi Kuan- Made in PixiTracker.mp3", true);

	// --
	int judgeTime, whichWay, speed, type;
	while (scoreIfs >> judgeTime >> whichWay >> speed >> type)
	{
		game.allNotes.push({judgeTime, whichWay, speed});
	}
	// --

	startPoint = steady_clock::now();

	judges.push_back(Sprite::create("NoteResources/red.png"));
	judges.push_back(Sprite::create("NoteResources/red.png"));
	judges.push_back(Sprite::create("NoteResources/red.png"));
	judges.push_back(Sprite::create("NoteResources/red.png"));
	for (int i = 0; i < SG_Game::WAYS; ++i)
	{
		judges[i]->setPosition(Vec2(visibleSize.width / 4 * i + 100, 200));
		this->addChild(judges[i]);
	}

	// backbutton
	auto sprite_back = Sprite::create("back.png");
	auto sprite_backselected = Sprite::create("back_selected.png");
	auto menuBackItem = MenuItemSprite::create(sprite_back, sprite_backselected, sprite_back, CC_CALLBACK_1(testScene::menuBackCallBack, this));
	menuBackItem->setPosition(Vec2(30, visibleSize.height - 30));
	auto menu0 = Menu::create(menuBackItem, NULL);
	menu0->setPosition(Vec2::ZERO);
	this->addChild(menu0);

	scheduleUpdate();
	return true;
}

double testScene::getDurationFromBegin(const std::chrono::steady_clock::time_point &nowPoint)
{
	steady_clock::duration timeSpan = nowPoint - startPoint;
	return double(timeSpan.count()) * steady_clock::period::num / steady_clock::period::den;
}

void testScene::update(float dt)
{
	oneFrameForward();

	auto getFrameNum = [](double duration) { return int(duration * 60); };

	int frameShouldBe = getFrameNum(getDurationFromBegin(steady_clock::now()));

	while (frameCnt < frameShouldBe)
	{
		log("%d %d", frameShouldBe, frameCnt);
		oneFrameForward();
	}
}

void testScene::appearNotes()
{
	if (game.allNotes.empty()) return;

	while (!game.allNotes.empty() && game.allNotes.front().appearTime < frameCnt) game.allNotes.pop();

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto &noteInfo = game.allNotes.front();
	
	while (noteInfo.appearTime == frameCnt)
	{
		auto newNote = SG_Note::create("NoteResources/white.jpg", noteInfo.speed, noteInfo.appearTime, noteInfo.judgeTime, noteInfo.whichWay);
		newNote->setPosition(Vec2(visibleSize.width / 4 * noteInfo.whichWay + 100, 700));
		
		auto moveD = MoveBy::create(1 / 60.0, Vec2(0, -noteInfo.speed));
		auto fall = RepeatForever::create(moveD);
		newNote->runAction(fall);
		this->addChild(newNote);
		
		game.notes[noteInfo.whichWay].push_back(newNote);
		game.allNotes.pop();

		if (game.allNotes.empty()) break;
		noteInfo = game.allNotes.front();
	}
}

void testScene::judgeNotes()
{
	for (int i = 0; i < SG_Game::WAYS; ++i)
	{
		for (auto it = game.notes[i].begin(); it != game.notes[i].end(); )
		{
			if ((*it)->get_judgeTime() == frameCnt)
			{
				auto animation = Animation::create();
				animation->addSpriteFrameWithFile("anime/Fuck3.png");
				animation->setRestoreOriginalFrame(true);
				animation->setDelayPerUnit(0.1f);
				auto action = Animate::create(animation);
				judges[i]->runAction(Sequence::create(action, nullptr));

				(*it)->removeFromParent();

				it = game.notes[i].erase(it);
			}
			else ++it;
		}
	}
}

void testScene::menuBackCallBack(Ref * pSender)
{
	Director::getInstance()->popScene();
}

void testScene::oneFrameForward()
{
	++frameCnt;
	appearNotes();
	judgeNotes();
}
