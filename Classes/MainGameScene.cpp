#include "MainGameScene.h"
#include "SimpleAudioEngine.h"
//#include "Block/SG_BlockF91.h"
#include "Block/SG_Note.h"
USING_NS_CC;

Scene* MainGameScene::createScene()
{
	return MainGameScene::create();
}

bool MainGameScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	// lyw 2018年10月20日01:00:52


	auto notefly = SG_Note::create("white.jpg");
	notefly->setPosition(Vec2(300, 300));
	this->addChild(notefly);

	auto judgePlace = SG_Note::create("red.png");
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

void MainGameScene::try_fuck()
{
	log("1");
}
