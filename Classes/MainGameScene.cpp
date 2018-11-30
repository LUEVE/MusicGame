#include "MainGameScene.h"
#include "SimpleAudioEngine.h"
// #include "Block/SG_BlockF91.h"
#include "Block/SG_Note.h"
#include "PauseScene.h"
#include "Block/SG_Action.h"
#include "ResultScene.h"
USING_NS_CC;
MainGameScene::MainGameScene(): Scene(), scoreIfs("D:\\score.txt"){}

//testScene::testScene() : Scene(), scoreIfs("D:\\score.txt") {}
Scene* MainGameScene::createScene()
{
	return MainGameScene::create();
}

Vector<Sprite*> AllSpirtInASong(6);

int flag = 0;
float nowtime = 0;
std::chrono::steady_clock::time_point MainGameScene::pauseStart;
chrono::steady_clock::duration MainGameScene::pauseDuration;
//std::chrono::steady_clock::time_point MainGameScene::pauseEnd;

void MainGameScene::update(float dt)
{
	oneFrameForward();

	auto getFrameNum = [](double duration) { return int(duration * 60); };
	double nowtime = getDuration(startPoint, chrono::steady_clock::now());
	int frameShouldBe = getFrameNum(nowtime);
	if (nowtime > 135)
	{
		Director::getInstance()->popScene();
		ResultScene* resultScene = ResultScene::createScene();
		resultScene->setGame(this->game);
		Director::getInstance()->pushScene(resultScene);
	}
	while (frameCnt < frameShouldBe)
	{
		log("%d %d", frameShouldBe, frameCnt);
		oneFrameForward();
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	// 判断出界

	for (int i = 0; i < SG_Game::WAYS; ++i)
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
				this->game.judgeCount[MISS]++;
			}
			else it++;
		}
	}
	// 改变combo状态
	if(comboNumber < game.COMBOSTATE_ONE_NUM)
	{
		comboPlace->removeFromParent();
		comboPlace = SG_Note::create("combo1.PNG");
		comboPlace->setPosition(Vec2(visibleSize.width / 6 * 4, visibleSize.height / 6 * 1));
		this->addChild(comboPlace);
	}
	else if(comboNumber >= game.COMBOSTATE_ONE_NUM && comboNumber <= game.COMBOSTATE_TWO_NUM)
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

static void restoreFrame(Sprite *s)
{
	s->setSpriteFrame(SpriteFrame::create("NoteResources/red.png", Rect(0, 0, 47, 46)));
}

void MainGameScene::preloadSoundResource(CocosDenshion::SimpleAudioEngine *sae)
{
	sae->preloadBackgroundMusic(bgmSongName.c_str());
	int tempNum = musicEffect.size();
	for (int i = 0; i < tempNum; ++i)
	{
		sae->preloadEffect(musicEffect[i].c_str());
	}
}

bool MainGameScene::init()
{
	if (!Scene::init())
	{
		return false;
	} 
	// -- 初始化资源 -- begin

	// background

	auto mainGame_bg = Sprite::create("mainGame_bg.png");
	mainGame_bg->setAnchorPoint(Vec2(0, 0));
	mainGame_bg->setPosition(Vec2(0, 0));
	this->addChild(mainGame_bg);
	// preload sound resource

	auto sae = CocosDenshion::SimpleAudioEngine::getInstance();
	preloadSoundResource(sae);
	// Play music

	sae->stopBackgroundMusic();
	sae->playBackgroundMusic(bgmSongName.c_str(), false);
	// allnote in song push in scene

	int judgeTime, whichWay, speed, type;
	while (scoreIfs >> judgeTime >> whichWay >> speed >> type)
	{
		game.allNotes.push({ judgeTime, whichWay, speed });
	}
	// combo
	this->comboNumber = 0;
	comboPlace = SG_Note::create("combo1.PNG");
	comboPlace->setPosition(Vec2(visibleSize.width / 6 * 4, visibleSize.height / 6 * 1));
	this->addChild(comboPlace);
	string s_comboNumber = to_string(comboNumber);
	this->comboNumberLabel = Label::createWithSystemFont(s_comboNumber, "Arial", 30);
	this->comboNumberLabel->setPosition(Vec2(visibleSize.width / 6 * 4 + 100, visibleSize.height / 6 * 1));
	this->addChild(this->comboNumberLabel);

	// score
	this->game.gameScore = 0;
	string s_gameScore = to_string(game.gameScore);
	this->gameScoreLabel = Label::createWithSystemFont(s_gameScore, "Consolas", 30);
	this->gameScoreLabel->setPosition(Vec2(visibleSize.width / 5 * 4 + 100, visibleSize.height / 10 * 9));
	this->addChild(this->gameScoreLabel);

	this->addedGameScoreLabel = Label::createWithSystemFont("+", "Consolas", 30);
	this->addChild(this->addedGameScoreLabel);

	// judge place
	vector<Sprite*> judges = { SG_Note::create("NoteResources/red.png"), SG_Note::create("NoteResources/red.png"),
		SG_Note::create("NoteResources/red.png"), SG_Note::create("NoteResources/red.png") };

	for (int i = 0; i < judges.size(); ++i) // initialize judges
	{
		judges[i]->setPosition(Vec2(194 * i + 220, 200));
		this->addChild(judges[i]);
	}

	// -- 初始化资源 -- end

	
	// 记录时间
	startPoint = chrono::steady_clock::now();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	this->visibleSize = visibleSize;

	for(int i = 0; i < JUDGE_NUM; i++) {
		this->game.judgeCount[i] = 0;
	}

	// 键盘事件
	auto listen1 = EventListenerKeyboard::create();

	listen1->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event * event) {
		// log("KeyPress:%d", keyCode);
		// log("%d", notefly);
		auto checkNote = [&](int which)
		{
			long long addedScore = 0;
			auto &vec = game.notes[which];
			bool judgeFlag = true;
			for (auto it = vec.begin(); it != vec.end(); ) {
				auto restoreF = CallFunc::create([=]() { restoreFrame(judges[which]); });
				if (dist((*it)->getPosition(), judges[which]->getPosition()) <= SG_Game::MISSPLACE && dist((*it)->getPosition(), judges[which]->getPosition()) >= SG_Game::GOODPLACE) // miss
				{
					// music affect
					CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(musicEffect[3].c_str());
					auto animation = Animation::create();
					setJudgeAnimation(animation, 4);
					auto action = Animate::create(animation);
					judges[which]->runAction(Sequence::create(action, restoreF, nullptr));
					(*it)->removeFromParent();
					it = vec.erase(it);
					// lyw 计数combo
					this->comboNumber = 0;
					// lxs 计算游戏判定总数
					this->game.judgeCount[MISS]++;
					break;
				}
				else if (dist((*it)->getPosition(), judges[which]->getPosition()) <= SG_Game::GOODPLACE && dist((*it)->getPosition(), judges[which]->getPosition()) >=SG_Game::GREATPLACE) // good
				{
					// music affect
					CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(musicEffect[2].c_str());
					auto animation = Animation::create();
					setJudgeAnimation(animation,3);
					auto action = Animate::create(animation);
					judges[which]->runAction(Sequence::create(action, restoreF, nullptr));
					(*it)->removeFromParent();
					it = vec.erase(it);
					// lyw 计数combo
					this->comboNumber++;
					// lxs 增加分数
					if(comboNumber > 100) {
						addedScore = SG_Game::GOODSCORE_100;
					}
					else if(comboNumber > 50) {
						addedScore = SG_Game::GOODSCORE_50;
					}
					else {
						addedScore = SG_Game::GOODSCORE;
					}
					this->game.gameScore += addedScore;
				 	judgeFlag = true;
					// lxs 计算游戏判定总数
					this->game.judgeCount[GOOD]++;
					break;

				}
				else if(dist((*it)->getPosition(), judges[which]->getPosition()) <= SG_Game::GREATPLACE && dist((*it)->getPosition(), judges[which]->getPosition()) >= SG_Game::PERFECTPLACE) // perfect
				{
					 CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(musicEffect[1].c_str());
					 auto animation = Animation::create();
					 setJudgeAnimation(animation,2);
					 auto action = Animate::create(animation);
					 judges[which]->runAction(Sequence::create(action, restoreF, nullptr));
					 (*it)->removeFromParent();
					 it = vec.erase(it);
					 // lyw 计数combo
					 this->comboNumber++;
					 // lxs 增加分数
					 if (comboNumber > 100) {
						 addedScore = SG_Game::GREATSCORE_100;
					 }
					 else if (comboNumber > 50) {
						 addedScore = SG_Game::GREATSCORE_50;
					 }
					 else {
						 addedScore = SG_Game::GREATSCORE;
					 }
					 this->game.gameScore += addedScore;
					 judgeFlag = true;
					 // lxs 计算游戏判定总数
					 this->game.judgeCount[GREAT]++;
					 break;
				 }
				 else if ( dist((*it)->getPosition(), judges[which]->getPosition()) <= SG_Game::PERFECTPLACE)
				 {
					 CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(musicEffect[0].c_str());
					 auto animation = Animation::create();
					 setJudgeAnimation(animation,1);
					 auto action = Animate::create(animation);
					 
					 judges[which]->runAction(Sequence::create(action, restoreF, nullptr));
					 (*it)->removeFromParent();
					 it = vec.erase(it);
					 // lyw 计数combo
					 this->comboNumber++;
					 // lxs 增加分数
					 if (comboNumber > 100) {
						 addedScore = SG_Game::PERFECTSCORE_100;
					 }
					 else if (comboNumber > 50) {
						 addedScore = SG_Game::PERFECTSCORE_50;
					 }
					 else {
						 addedScore = SG_Game::PERFECTSCORE;
					 }
					 this->game.gameScore += addedScore;
					 judgeFlag = true;
					 // lxs 计算游戏判定总数
					 this->game.judgeCount[PERFECT]++;
					 break;
				 }
				 else
				 {
					
					 ++it;
					
				 }
			}
 
			// 刷新combo数
			reFreshComboLebal();
			// 刷新分数
			reFreshGameScoreLabel(addedScore);
			SG_Action::setVisibleSize(visibleSize);
			// 调用增加分数的actiona
			this->addedGameScoreLabel->runAction(SG_Action::addScoreAction());
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
			CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
			Director::getInstance()->pushScene(PauseScene::createScene());
			pauseStart = std::chrono::steady_clock::now();
			break;
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listen1, this);


	// lyw--

	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// backbutton
	auto sprite_back = Sprite::create("back.png");
	auto sprite_backselected = Sprite::create("back_selected.png");
	auto menuBackItem = MenuItemSprite::create(sprite_back, sprite_backselected, sprite_back, CC_CALLBACK_1(MainGameScene::menuBackCallBack, this));
	menuBackItem->setPosition(Vec2(30, visibleSize.height - 30));
	auto menu0 = Menu::create(menuBackItem, NULL);
	menu0->setPosition(Vec2::ZERO);
	this->addChild(menu0);

	scheduleUpdate();

	return true;
}


void MainGameScene::menuBackCallBack(Ref* pSender)
{
	Director::getInstance()->pushScene(PauseScene::createScene());
	CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
	pauseStart = std::chrono::steady_clock::now();
}

void MainGameScene::setJudgeAnimation(Animation* animation,int i)
{
	string judge;
	if (i==MISS)
	{
		judge = "Judge\\miss";
	}
	else if (i == GOOD)
	{
		judge = "Judge\\good";
	}
	else if(i == GREAT)
	{
		judge = "Judge\\great";
	}
	else
	{
		judge = "Judge\\perfect";
	}

	animation->addSpriteFrameWithFile(judge+"1.png");
	animation->addSpriteFrameWithFile(judge+"2.png");
	animation->addSpriteFrameWithFile(judge+"3.png");
	animation->setRestoreOriginalFrame(true);
	animation->setDelayPerUnit(0.1f);//设置动画的间隔时间
	
}
void MainGameScene::appearNotes()
{
	if (game.allNotes.empty()) return;

	while (!game.allNotes.empty() && game.allNotes.front().appearTime < frameCnt) game.allNotes.pop();

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto &noteInfo = game.allNotes.front();

	while (noteInfo.appearTime == frameCnt)
	{
		auto newNote = SG_Note::create("greenhat.png", noteInfo.speed, noteInfo.appearTime, noteInfo.judgeTime, noteInfo.whichWay);
		newNote->setPosition(Vec2(194 * noteInfo.whichWay + 220, 700));

		// 调用 note下落的action
		newNote->runAction(SG_Action::notesAction(noteInfo.speed));
		this->addChild(newNote);

		game.notes[noteInfo.whichWay].push_back(newNote);
		game.allNotes.pop();

		if (game.allNotes.empty()) break;
		noteInfo = game.allNotes.front();
	}
}

// 辅助函数 -----

void MainGameScene::oneFrameForward()
{
	++frameCnt;
	appearNotes();
}



double MainGameScene::getDuration(const std::chrono::steady_clock::time_point &start, const std::chrono::steady_clock::time_point &end)
{
	chrono::steady_clock::duration timeSpan = end - start;
	timeSpan -= pauseDuration;
	return double(timeSpan.count()) * chrono::steady_clock::period::num / chrono::steady_clock::period::den;
}

 void MainGameScene::reFreshComboLebal()
{
	 comboNumberLabel->removeFromParent();
	 this->comboNumberLabel = Label::createWithSystemFont(to_string(this->comboNumber), "Arial", 30);
	 this->comboNumberLabel->setPosition(Vec2(this->visibleSize.width / 6 * 4 + 100, this->visibleSize.height / 6 * 1));
	 this->addChild(comboNumberLabel);
}

 void MainGameScene::reFreshGameScoreLabel(long long addedScore)
{
	 gameScoreLabel->removeFromParent();
	 this->gameScoreLabel = Label::createWithSystemFont(to_string(this->game.gameScore), "Consolas", 30);
	 this->gameScoreLabel->setPosition(Vec2(visibleSize.width / 5 * 4 + 100, visibleSize.height / 10 * 9));
	 this->addChild(this->gameScoreLabel);

	 addedGameScoreLabel->removeFromParent();
	 this->addedGameScoreLabel = Label::createWithSystemFont("+" + to_string(addedScore), "Consolas", 30);
	 if (addedScore) {
		 this->addedGameScoreLabel->setPosition(Vec2(visibleSize.width / 5 * 4 + 100, visibleSize.height / 20 * 17));
	 }
	 else {
		 this->addedGameScoreLabel->setPosition(Vec2(-100, -100));
	 }
	 this->addChild(this->addedGameScoreLabel);
}

 // 辅助函数   --