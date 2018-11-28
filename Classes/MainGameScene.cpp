#include "MainGameScene.h"
#include "SimpleAudioEngine.h"
// #include "Block/SG_BlockF91.h"
#include "Block/SG_Note.h"
#include "PauseScene.h"
USING_NS_CC;

Scene* MainGameScene::createScene()
{

	return MainGameScene::create();
}

Vector<Sprite*> AllSpirtInASong(6);

int flag = 0;

void MainGameScene::update(float dt)
{
	
	static mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
	static uniform_int_distribution<int> genProb(1, 100), genPos(0, SG_Game::WAYS - 1), genSpeed(10,20);
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

	for (int i = 0; i <= 3; ++i)
	{
		auto &vec = game.notes[i];
		for (auto it = vec.begin(); it != vec.end(); ) {
			if ((*it)->getPositionY() < 0)
			{
				(*it)->removeFromParent();
				it = vec.erase(it);
				this->comboNumber = 0;
				comboNumberLabel->removeFromParent();
				this->comboNumberLabel = Label::createWithSystemFont(to_string(this->comboNumber), "Arial", 30);
				this->comboNumberLabel->setPosition(Vec2(visibleSize.width / 6 * 4 + 100, visibleSize.height / 6 * 1));
				this->addChild(comboNumberLabel);
			}
			else it++;
		}
	}
	// 改变combo状态
	if(comboNumber < 3)
	{
		comboPlace->removeFromParent();
		comboPlace = SG_Note::create("combo1.PNG");
		comboPlace->setPosition(Vec2(visibleSize.width / 6 * 4, visibleSize.height / 6 * 1));
		this->addChild(comboPlace);
	}
	else if(comboNumber >= 3 && comboNumber <= 5)
	{
		comboPlace->removeFromParent();
		comboPlace = SG_Note::create("combo2.PNG");
		comboPlace->setPosition(Vec2(visibleSize.width / 6 * 4, visibleSize.height / 6 * 1));
		this->addChild(comboPlace);
	}
	else
	{
		comboPlace->removeFromParent();
		comboPlace = SG_Note::create("combo3.PNG");
		comboPlace->setPosition(Vec2(visibleSize.width / 6 * 4, visibleSize.height / 6 * 1));
		this->addChild(comboPlace);
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
	comboPlace = SG_Note::create("combo1.PNG");
	comboPlace->setPosition(Vec2(visibleSize.width / 6 * 4, visibleSize.height / 6 * 1));
	this->addChild(comboPlace);
	string s_comboNumber = to_string(comboNumber);
	this->comboNumberLabel = Label::createWithSystemFont(s_comboNumber, "Arial", 30);
	this->comboNumberLabel->setPosition(Vec2(visibleSize.width / 6 * 4 + 100, visibleSize.height / 6 * 1));
	this->addChild(this->comboNumberLabel);


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
			bool judgeFlag = false;
			for (auto it = vec.begin(); it != vec.end(); ) {
				 if (dist((*it)->getPosition(), judges[which]->getPosition()) <= 100 && dist((*it)->getPosition(), judges[which]->getPosition()) >=50)
				{
					
					auto animation = Animation::create();
					setJudgeAnimation(animation,3);
					auto action = Animate::create(animation);
					judges[which]->runAction(Sequence::create(action, nullptr));
					(*it)->removeFromParent();
					it = vec.erase(it);
					// lyw 计数combo
					this->comboNumber++;
				 	judgeFlag = true;
					break;

				}
				 else if(dist((*it)->getPosition(), judges[which]->getPosition()) < 50 && dist((*it)->getPosition(), judges[which]->getPosition()) >= 25)
				 {
					 auto animation = Animation::create();
					 setJudgeAnimation(animation,2);
					 auto action = Animate::create(animation);
					 judges[which]->runAction(Sequence::create(action, nullptr));
					 (*it)->removeFromParent();
					 it = vec.erase(it);
					 // lyw 计数combo
					 this->comboNumber++;
					 judgeFlag = true;
					 break;
				 }
				 else if ( dist((*it)->getPosition(), judges[which]->getPosition()) < 25)
				 {
					 auto animation = Animation::create();
					 setJudgeAnimation(animation,1);
					 auto action = Animate::create(animation);
					 
					 judges[which]->runAction(Sequence::create(action, nullptr));
					 (*it)->removeFromParent();
					 it = vec.erase(it);
					 // lyw 计数combo
					 this->comboNumber++;
					 judgeFlag = true;
					 break;
				 }
				 else
				 {
					
					 ++it;
					
				 }
					// lyw count combo


				
			}
			if (judgeFlag == false)
			{
				this->comboNumber = 0;
			}
			comboNumberLabel->removeFromParent();
			this->comboNumberLabel = Label::createWithSystemFont(to_string(this->comboNumber), "Arial", 30);
			this->comboNumberLabel->setPosition(Vec2(visibleSize.width / 6 * 4 + 100, visibleSize.height / 6 * 1));
			this->addChild(comboNumberLabel);
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
		case EventKeyboard::KeyCode::KEY_ESCAPE:
			/*auto visibleSize = Director::getInstance()->getVisibleSize();
			auto *renderTexture = RenderTexture::create(visibleSize.width, visibleSize.height);
			renderTexture->begin();
			Director::getInstance()->getRunningScene()->visit();
			renderTexture->end();
			auto pauseScene = PauseScene::createScene(renderTexture);
			Director::getInstance()->pushScene(pauseScene);*/
			Director::getInstance()->pushScene(PauseScene::createScene());
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

void MainGameScene::setJudgeAnimation(Animation* animation,int i)
{
	string judge;
	if (i == 3)
	{
		judge = "good";
	}
	else if(i == 2)
	{
		judge = "great";
	}
	else
	{
		judge = "perfect";
	}
	animation->addSpriteFrameWithFile(judge+"1.png");
	animation->addSpriteFrameWithFile(judge+"2.png");
	animation->addSpriteFrameWithFile(judge+"3.png");
	animation->setRestoreOriginalFrame(true);
	animation->setDelayPerUnit(0.1f);//设置动画的间隔时间
}
