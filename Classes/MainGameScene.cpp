#include "MainGameScene.h"
#include "SimpleAudioEngine.h"
// #include "Block/SG_BlockF91.h"
#include "Block/SG_Note.h"
USING_NS_CC;

Scene* MainGameScene::createScene()
{

	return MainGameScene::create();
}

Vector<Sprite*> AllSpirtInASong(6);


void MainGameScene::update(float dt)
{
	static mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
	static uniform_int_distribution<int> genProb(1, 100), genPos(0, SG_Game::WAYS - 1), genSpeed(10, 50);
	auto visibleSize = Director::getInstance()->getVisibleSize();
	if (genProb(rng) <= 2)
	{
		SG_Note* newNote = SG_Note::create("white.jpg");
		int pos = genPos(rng);
		newNote->setPosition(Vec2(visibleSize.width / 4 * pos + 100, 700));

		auto moveD = MoveBy::create(0.1, Vec2(0, -genSpeed(rng)));
		auto fall = RepeatForever::create(moveD);
		newNote->runAction(fall);

		this->addChild(newNote);

		game.notes[pos].push_back(newNote);
	}
}

bool MainGameScene::CreatAllSpirtInSong()
{
	for (int i = 1; i <= 5; ++i)
	{
		char a = (char)i % 2 + '1';
		string PictureName = "Note";
		PictureName = PictureName+ a + ".png";
		auto tempNote = SG_Note::create(PictureName);
		//this->addChild(tempNote);
		AllSpirtInASong.pushBack(tempNote);
	}
	return true;
}


static float sqr(float x)
{
	return x * x;
}

static float dist(const Vec2 &a, const Vec2 &b)
{
	return sqrt(sqr(a.x - b.x) + sqr(a.y - b.y));
}


bool MainGameScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	this->comboNumber = 0;
	auto visibleSize = Director::getInstance()->getVisibleSize();
	// combo区
	auto comboPlace = SG_Note::create("comebo.PNG");
	comboPlace->setPosition(Vec2(visibleSize.width / 6 * 4, visibleSize.height / 6 * 1));
	this->addChild(comboPlace);
	auto myLabel = Label::createWithSystemFont("999", "Arial", 30);
	myLabel->setPosition(Vec2(visibleSize.width / 6 * 4 + 100, visibleSize.height / 6 * 1));
	this->addChild(myLabel);


	// 判断区
	vector<Sprite*> judges = {SG_Note::create("red.png"), SG_Note::create("red.png"),
		SG_Note::create("red.png"), SG_Note::create("red.png")};
	
	for (int i = 0; i < judges.size(); ++i) // initialize judges
	{
		judges[i]->setPosition(Vec2(visibleSize.width / 4 * i + 100, 200));
		this->addChild(judges[i]);
	}

	// 掉落块

	game.notes[0].push_back(SG_Note::create("white.jpg"));
	game.notes[1].push_back(SG_Note::create("white.jpg"));
	game.notes[2].push_back(SG_Note::create("white.jpg"));
	game.notes[3].push_back(SG_Note::create("white.jpg"));
	for (int i = 0; i < SG_Game::WAYS; ++i) // initialize notes
	{
		game.notes[i].front()->setPosition(Vec2(visibleSize.width / 4 * i + 100, 700));
		auto moveD = MoveBy::create(0.1, Vec2(0, -20));
		auto fall = RepeatForever::create(moveD);
		game.notes[i].front()->runAction(fall);
		this->addChild(game.notes[i].front());
	}

	// 键盘事件
	auto listen1 = EventListenerKeyboard::create();

	listen1->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event * event) {
		// log("KeyPress:%d", keyCode);
		// log("%d", notefly);
		auto checkNote = [&](int which)
		{
			auto &vec = game.notes[which];
			for (auto it = vec.begin(); it != vec.end(); ) {
				if ((*it)->getPositionY() < 0)
				{
					(*it)->removeFromParent();
					it = vec.erase(it);
				}
				else if (dist((*it)->getPosition(), judges[which]->getPosition()) <= 20)
				{
					auto animation = Animation::create();
					animation->addSpriteFrameWithFile("Fuck1.png");
					animation->addSpriteFrameWithFile("Fuck2.png");
					animation->addSpriteFrameWithFile("Fuck3.png");
					animation->setRestoreOriginalFrame(true);
					animation->setDelayPerUnit(0.1f);//设置动画的间隔时间

													 // judges[which]->setSpriteFrame(SpriteFrame::create("red.png", Rect(0, 0, 47, 46)));

													 // auto original = Animation::create();
													 // original->addSpriteFrameWithFile("red.png");
													 // original->setRestoreOriginalFrame(false);
													 // original->setDelayPerUnit(0);
													 // judges[which]->runAction(Sequence::create(Animate::create(original), nullptr));

					auto action = Animate::create(animation);
					// action->initWithAnimation(original);
					// judges[which]->stopAllActions();
					judges[which]->runAction(Sequence::create(action, nullptr));

					(*it)->removeFromParent();

					it = vec.erase(it);
				}
				else ++it;
			}
		};

		switch (keyCode)
		{
		case EventKeyboard::KeyCode::KEY_A:
			log("A");
			checkNote(0);
			break;
		case EventKeyboard::KeyCode::KEY_S:
			log("S");
			checkNote(1);
			break;
		case EventKeyboard::KeyCode::KEY_D:
			log("D");
			checkNote(2);
			break;
		case EventKeyboard::KeyCode::KEY_F:
			log("F");
			checkNote(3);
			break;
		default:
			log("default pressed");
			break;
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listen1, this);


	// lyw--

	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto button = ui::Button::create("back.png", "back_selected.png", "back_disabled.png");

	button->setPosition(Vec2(origin.x + 100, origin.y + 50));
	button->addClickEventListener(CC_CALLBACK_1(MainGameScene::btnBackCallback, this));

	this->addChild(button);

	scheduleUpdate();

	return true;
}

void MainGameScene::btnBackCallback(Ref* pSender)
{
	Director::getInstance()->popScene();
}

