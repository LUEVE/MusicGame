#include "GeneratorScene.h"
#include "ui/UIButton.h"
#include "SimpleAudioEngine.h"
#include "Block/SG_Note.h"
#include "testScene.h"

USING_NS_CC;
using namespace std;
using namespace std::chrono;

bool GeneratorScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	// auto director = Director::getInstance();
	// director->setAnimationInterval(1.0f / 30);

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto sae = CocosDenshion::SimpleAudioEngine::getInstance();

	sae->stopBackgroundMusic();
	sae->playBackgroundMusic("Wiwi Kuan- Made in PixiTracker.mp3", true);
	startPoint = steady_clock::now();

	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// backbutton
	auto sprite_back = Sprite::create("back.png");
	auto sprite_backselected = Sprite::create("back_selected.png");
	auto menuBackItem = MenuItemSprite::create(sprite_back, sprite_backselected, sprite_back, CC_CALLBACK_1(GeneratorScene::menuBackCallBack, this));
	menuBackItem->setPosition(Vec2(30, visibleSize.height - 30));
	auto menu0 = Menu::create(menuBackItem, NULL);
	menu0->setPosition(Vec2::ZERO);
	this->addChild(menu0);

	vector<Sprite*> judges = {SG_Note::create("NoteResources/red.png"), SG_Note::create("NoteResources/red.png"),
		SG_Note::create("NoteResources/red.png"), SG_Note::create("NoteResources/red.png")};

	auto speedLabel = Label::createWithTTF("current note speed: 5", "fonts/Marker Felt.ttf", 24);
	speedLabel->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 50));
	this->addChild(speedLabel);

	
	for (int i = 0; i < judges.size(); ++i) // initialize judges
	{
		judges[i]->setPosition(Vec2(visibleSize.width / 4 * i + 100, 200));
		this->addChild(judges[i]);
	}

	auto keyListener = EventListenerKeyboard::create();

	keyListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event * event)
	{
		const static string speedLabelPrefix = "current note speed: ";
		auto changeFrameToRed = [&](int which) { judges[which]->setSpriteFrame(SpriteFrame::create("NoteResources/white.jpg", Rect(0, 0, 40, 40))); };
		switch (keyCode)
		{
		case EventKeyboard::KeyCode::KEY_A:
			log("A");
			
			changeFrameToRed(0);
			writeNoteOut(0);
			break;
		case EventKeyboard::KeyCode::KEY_S:
			log("S");
			
			changeFrameToRed(1);
			writeNoteOut(1);
			break;
		case EventKeyboard::KeyCode::KEY_D:
			log("D");
			
			changeFrameToRed(2);
			writeNoteOut(2);
			break;
		case EventKeyboard::KeyCode::KEY_F:
			log("F");
			
			changeFrameToRed(3);
			writeNoteOut(3);
			break;
		case EventKeyboard::KeyCode::KEY_UP_ARROW:
			if (currentSpeed < 10) ++currentSpeed;
			speedLabel->setString(speedLabelPrefix + to_string(currentSpeed));
			break;
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
			if (currentSpeed > 2) --currentSpeed;
			speedLabel->setString(speedLabelPrefix + to_string(currentSpeed));
			break;
		default:
			log("default pressed");
			break;
		}
	};

	keyListener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event * event)
	{
		auto changeFrameToWhite = [&](int which) { judges[which]->setSpriteFrame(SpriteFrame::create("NoteResources/red.png", Rect(0, 0, 47, 46))); };
		switch (keyCode)
		{
		case EventKeyboard::KeyCode::KEY_A:
			log("A");
			
			changeFrameToWhite(0);
			break;
		case EventKeyboard::KeyCode::KEY_S:
			log("S");

			changeFrameToWhite(1);
			break;
		case EventKeyboard::KeyCode::KEY_D:
			log("D");

			changeFrameToWhite(2);
			break;
		case EventKeyboard::KeyCode::KEY_F:
			log("F");

			changeFrameToWhite(3);
			break;
		default:
			log("default released");
			break;
		}
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);
	scheduleUpdate();
	return true;
}

void GeneratorScene::oneFrameForward()
{
	++frameCnt;
}

double GeneratorScene::getDurationFromBegin(const std::chrono::steady_clock::time_point &nowPoint)
{
	steady_clock::duration timeSpan = nowPoint - startPoint;
	return double(timeSpan.count()) * steady_clock::period::num / steady_clock::period::den;
}

void GeneratorScene::update(float dt)
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

void GeneratorScene::menuBackCallBack(Ref * pSender)
{
	Director::getInstance()->popScene();
}

void GeneratorScene::writeNoteOut(int which)
{
	scoreOfs << frameCnt << ' ' << which << ' ' << currentSpeed << ' ' << 0 << '\n';
}

GeneratorScene::GeneratorScene() : scoreOfs("D:\\score.txt") {}

