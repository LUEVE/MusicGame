#include "SelectScene.h"
#include "SimpleAudioEngine.h"

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

	//��������
	tableView->setBounceable(true);                              //��������Ч��
	tableView->setDirection(cocos2d::extension::ScrollView::Direction::VERTICAL);  //����
	tableView->setDelegate(this);								  //ί�д���
	tableView->reloadData();									  //��������

	return true;
}

void SelectScene::btnBackCallback(Ref* pSender)
{
	Director::getInstance()->popScene();
}

TableViewCell* SelectScene::tableCellAtIndex(TableView* table, ssize_t idx) 
{
	char Icon[20];   //����idxѡ����ʾ��ͼƬ
	char number[10]; //��ʾlabel��ǩ������
	sprintf(Icon,"sp%d.png",idx%3+1);
	sprintf(number, "%02d", idx);

	TableViewCell* cell = table->dequeueCell();  //������

	//δ����βһֱȡ
	if (!cell) {
		cell = new TableViewCell();
		cell->autorelease();  //�Զ��ͷ���Դ

		//���һ������ͼƬ
		Sprite* sprite = Sprite::create(Icon);
		sprite->setAnchorPoint(Point::ZERO);  //�������Ϊ���½�
		sprite->setPosition(ccp(0, 0));
		sprite->setOpacity(100);
		cell->addChild(sprite,0,1);

		//���һ��label��ǩ
		LabelTTF* label = LabelTTF::create(number, "Arial", 20);
		label->setPosition(Point::ZERO);
		label->setAnchorPoint(Point::ZERO);
		cell->addChild(label, 0, 2);
	}
	else {
		//��������ͼƬ��ʹ������
		Texture2D* texture = TextureCache::sharedTextureCache()->addImage(Icon);
		Sprite* sprite = (Sprite*)cell->getChildByTag(1);
		sprite->setTexture(texture);

		//����ͼƬ���
		LabelTTF* label = (LabelTTF*)cell->getChildByTag(2);
		label->setString(number);
	}

	return cell;
}

//����idx������ÿ��cell�ĳߴ��С
Size SelectScene::tableCellSizeForIndex(TableView* table, ssize_t idx)
{
	//if (idx == 2) return CCSizeMake(100, 100);
	return CCSizeMake(100, 100);
}

//һ��������cell
ssize_t SelectScene::numberOfCellsInTableView(TableView* table)
{
	return 10;
}

//ĳ��cell�����ʱ�ص�����
void SelectScene::tableCellTouched(TableView* table, TableViewCell* cell)
{
	log("cell touched at index: %i", cell->getIdx()); //����̨���
}

void SelectScene::scrollViewDidScroll(cocos2d::extension::ScrollView* view) { } //����ʱ�ص�����
void SelectScene::scrollViewDidZoom(cocos2d::extension::ScrollView* view) { }   //����ʱ�ص�����