#include "SelectScene.h"
#include "SimpleAudioEngine.h"
#include "MainGameScene.h"
USING_NS_CC;

Scene* SelectScene::createScene()
{
	Scene *scene = Scene::create();
	SelectScene *layer = SelectScene::create();
	scene->addChild(layer);
	return scene;
}

bool SelectScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	//Size mysize = Director::sharedDirector()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto song1_bg = Sprite::create("song1.jpg");
	song1_bg->setAnchorPoint(Vec2(0, 0));
	song1_bg->setPosition(Vec2(0, 0));
	this->addChild(song1_bg);

	auto button = Button::create("back.png", "back_selected.png", "back_disabled.png");
	button->setPosition(Vec2(100, 50));
	button->addClickEventListener(CC_CALLBACK_1(SelectScene::btnBackCallback, this));
	this->addChild(button);

	auto label1 = Label::createWithTTF("Select Songs", "fonts/Marker Felt.ttf", 24);
	label1->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - label1->getContentSize().height));
	this->addChild(label1);

	TableView* tableView = TableView::create(this, CCSizeMake(visibleSize.width / 2, visibleSize.height));
	tableView->setPosition(ccp(visibleSize.width / 2, origin.y - 2*label1->getContentSize().height));
	this->addChild(tableView);

	//属性设置
	tableView->setBounceable(true);                              //开启弹性效果
	tableView->setDirection(cocos2d::extension::ScrollView::Direction::VERTICAL);  //纵向
	tableView->setDelegate(this);								  //委托代理
	tableView->reloadData();									  //加载数据

	return true;
}

void SelectScene::btnBackCallback(Ref* pSender)
{
	Director::getInstance()->popScene();
}

TableViewCell* SelectScene::tableCellAtIndex(TableView* table, ssize_t idx) 
{
	char Icon[20];   //根据idx选中显示的图片
	char number[10]; //显示label标签的数字
	sprintf(Icon,"sp%d.png",idx%3+1);
	sprintf(number, "%02d", idx);

	TableViewCell* cell = table->dequeueCell();  //出队列

	//未到结尾一直取
	if (!cell) {
		cell = new TableViewCell();
		cell->autorelease();  //自动释放资源

		//添加一个精灵图片
		Sprite* sprite = Sprite::create(Icon);
		sprite->setAnchorPoint(Point::ZERO);  //设置描点为左下角
		sprite->setPosition(ccp(0, 0));
		sprite->setOpacity(100);
		cell->addChild(sprite,0,1);

		//添加一个label标签
		LabelTTF* label = LabelTTF::create(number, "Arial", 20);
		label->setPosition(Point::ZERO);
		label->setAnchorPoint(Point::ZERO);
		cell->addChild(label, 0, 2);
	}
	else {
		//更换精灵图片，使用纹理
		Texture2D* texture = TextureCache::sharedTextureCache()->addImage(Icon);
		Sprite* sprite = (Sprite*)cell->getChildByTag(1);
		sprite->setTexture(texture);

		//更改图片编号
		LabelTTF* label = (LabelTTF*)cell->getChildByTag(2);
		label->setString(number);
	}

	return cell;
}

//根据idx来设置每项cell的尺寸大小
Size SelectScene::tableCellSizeForIndex(TableView* table, ssize_t idx)
{
	//if (idx == 2) return CCSizeMake(100, 100);
	return CCSizeMake(100, 100);
}

//一共多少项cell
ssize_t SelectScene::numberOfCellsInTableView(TableView* table)
{
	return 10;
}

//某项cell被点击时回调函数
void SelectScene::tableCellTouched(TableView* table, TableViewCell* cell)
{
	log("cell touched at index: %i", cell->getIdx()); //控制台输出
	auto maingameScene = MainGameScene::createScene();
	Director::getInstance()->pushScene(TransitionFadeUp::create(0.5, maingameScene));
}

void SelectScene::scrollViewDidScroll(cocos2d::extension::ScrollView* view) { } //滚动时回调函数
void SelectScene::scrollViewDidZoom(cocos2d::extension::ScrollView* view) { }   //放缩时回调函数