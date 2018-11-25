#include "MainGameScene.h"
#include "SimpleAudioEngine.h"
// #include "Block/SG_BlockF91.h"
#include "Block/SG_Note.h"
USING_NS_CC;

Scene* MainGameScene::createScene()
{
	return MainGameScene::create();
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
	
	auto visibleSize = Director::getInstance()->getVisibleSize();

	vector<Sprite*> judges = {SG_Note::create("red.png"), SG_Note::create("red.png"),
		SG_Note::create("red.png"), SG_Note::create("red.png")};
	for (int i = 0; i < judges.size(); ++i) // initialize judges
	{
		judges[i]->setPosition(Vec2(visibleSize.width / 4 * i + 100, 200));
		this->addChild(judges[i]);
	}

	game.notes.push_back(SG_Note::create("white.jpg"));
	game.notes.push_back(SG_Note::create("white.jpg"));
	game.notes.push_back(SG_Note::create("white.jpg"));
	game.notes.push_back(SG_Note::create("white.jpg"));
	for (int i = 0; i < game.notes.size(); ++i) // initialize notes
	{
		game.notes[i]->setPosition(Vec2(visibleSize.width / 4 * i + 100, 700));
		auto moveD = MoveBy::create(0.1, Vec2(0, -20));
		auto fall = RepeatForever::create(moveD);
		game.notes[i]->runAction(fall);
		this->addChild(game.notes[i]);
	}

	// auto mainsprite = Sprite::create("Fuck1.png");
	// mainsprite->setPosition(Vec2(500, 300));
	// this->addChild(mainsprite);
	// log("%lf",mainsprite->getPosition().x);


	// mainsprite->setVisible(false);

	auto listen1 = EventListenerKeyboard::create();

	listen1->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event * event) {
		// log("KeyPress:%d", keyCode);
		// log("%d", notefly);
		auto checkNote = [&](int which)
		{
			for (auto it = game.notes.begin(); it != game.notes.end(); )
			{
				auto &note = *it;
				if (dist(note->getPosition(), judges[which]->getPosition()) <= 20)
				{
					auto animation = Animation::create();
					animation->addSpriteFrameWithFile("Fuck1.png");
					animation->addSpriteFrameWithFile("Fuck2.png");
					animation->addSpriteFrameWithFile("Fuck3.png");
					animation->setRestoreOriginalFrame(true);
					animation->setDelayPerUnit(0.1f);//设置动画的间隔时间

					auto action = Animate::create(animation);
					judges[which]->runAction(Sequence::create(action, NULL));

					(*it)->removeFromParent();

					it = game.notes.erase(it);
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

	return true;
}

void MainGameScene::btnBackCallback(Ref* pSender)
{
	Director::getInstance()->popScene();
}

