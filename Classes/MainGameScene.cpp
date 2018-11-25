#include "MainGameScene.h"
#include "SimpleAudioEngine.h"
//#include "Block/SG_BlockF91.h"
#include "Block/SG_Note.h"
USING_NS_CC;

Scene* MainGameScene::createScene()
{

	return MainGameScene::create();
}

Vector<Sprite*> AllSpirtInASong(6);

int timeFlag = 0;

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


bool MainGameScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	// lyw 2018年10月20日01:00:52
	
	//自定义帧执行器 

	auto tryT = CallFuncN::create([=](Ref* sender) {
		log("fuck");
	});
	
	auto scheduler = Director::getInstance()->getScheduler();
	//int i = 10;
//	scheduler->schedule(CC_CALLBACK_0(MainGameScene::try_fuck,this,&i)),0.2f,kRepeatForever,0);
	//auto scheduler = Director::getInstance()->getScheduler();
	int i = 10;
	string name = "sssss";
	scheduler->schedule(CC_CALLBACK_1(MainGameScene::try_fuck2, this, i, name), this, 0.1f, -1, 0, false,"fuck1");


	//schedule(schedule_selector(MainGameScene::try_fuck), 0.2f, kRepeatForever, 0);

	CreatAllSpirtInSong();

	auto tryV =  AllSpirtInASong.at(2);
	//tryV->setPosition(Vec2(500, 500));
	//this->addChild(tryV);

	auto notefly = SG_Note::create("NoteResources/white.jpg");
	notefly->setPosition(Vec2(300, 300));
	this->addChild(notefly);

	auto judgePlace = SG_Note::create("NoteResources/red.png");
	judgePlace->setPosition(Vec2(500, 300));
	this->addChild(judgePlace);

	
	// 移动
	auto move1 = MoveBy::create(0.1, Vec2(20, 0));
	auto move1F = RepeatForever::create(move1);
	notefly->runAction(move1F);

	//
	
	auto mainsprite = Sprite::create("Fuck1.png");
	mainsprite->setPosition(Vec2(500, 300));
	this->addChild(mainsprite);
	log("%lf",mainsprite->getPosition().x);



	mainsprite->setVisible(false);
	// 监听
	auto listen1 = EventListenerKeyboard::create();
	float judgeX = judgePlace->getPosition().x;
	float judgeY = judgePlace->getPosition().y;

	// 键盘
	listen1->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event * event) {
		//log("KeyPress:%d", keyCode);
		log("%d", notefly);
		if (&*notefly == nullptr)
		{
			return;
		}
		auto animation = CCAnimation::create();
		animation->addSpriteFrameWithFile("Fuck1.png");
		animation->addSpriteFrameWithFile("Fuck2.png");
		animation->addSpriteFrameWithFile("Fuck3.png");
		animation->setRestoreOriginalFrame(false);
		animation->setDelayPerUnit(0.1f);//设置动画的间隔时间



		auto animate1 = CCAnimate::create(animation);
		log("%f", notefly->getPosition().x);
		log("%f", notefly->getPosition().y);
		float nowx = notefly->getPosition().x;
		float nowy = notefly->getPosition().y;
		if (abs(nowx - judgeX) < 10)
		{
			log("ok\n");
		}
		else { log("false\n"); }

		mainsprite->setVisible(true);

		auto actionMoveDone = CallFuncN::create([=](Ref* sender) {
			mainsprite->stopAllActions();
			mainsprite->setVisible(false);
		});
		mainsprite->runAction(CCRepeatForever::create(CCSequence::create(animate1, actionMoveDone,NULL)));
		//mainsprite->setVisible(false);
		
		notefly->cleanup();
		this->removeChild(notefly);
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listen1, this);
	

	// lyw--

	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto button = Button::create("back.png", "back_selected.png", "back_disabled.png");
	
	button->setPosition(Vec2(100, 50));
	button->addClickEventListener(CC_CALLBACK_1(MainGameScene::btnBackCallback, this));

	this->addChild(button);

	return true;
}

void MainGameScene::btnBackCallback(Ref* pSender)
{
	Director::getInstance()->popScene();
}

void MainGameScene::try_fuck(float dt)
{
	//timeFlag++;
	//log("%d",timeFlag);
	
}
// lyw
int SFlag = 0;


//--lyw
void MainGameScene::try_fuck2(float t, int data, string name)
{
	timeFlag++;
	int i = data;
	log("%s", name.c_str());
	log("%d", i);
	if (timeFlag % 10 == 0)
	{
		//SFlag++;
		//auto newSpirt = AllSpirtInASong.at(SFlag % 2);
		//newSpirt->setPosition(10 * timeFlag / 10, 300);
		//addChild(newSpirt, 10);
		//log("s", this);
		changeSpirt();
	};
}


void MainGameScene::changeSpirt()
{
	if (timeFlag % 10 == 0)
	{
		if (SFlag > 4)
		{
			return;
		}
		
		auto newSpirt = AllSpirtInASong.at(SFlag);
		newSpirt->setPosition(10 * timeFlag/10,300);
		addChild(newSpirt,10);
		SFlag++;
	}
	
}
