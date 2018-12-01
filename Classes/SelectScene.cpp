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

	getMessages();

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto song_bg = Sprite::create("./song_bg/song1.jpg");
	song_bg->setAnchorPoint(Vec2(0, 0));
	song_bg->setPosition(Vec2(0, 0));
	song_bg->setTag(123);
	this->addChild(song_bg);

	auto button_back = Button::create("back.png", "back_selected.png", "back_disabled.png");
	button_back->setPosition(Vec2(100, 50));
	button_back->addClickEventListener(CC_CALLBACK_1(SelectScene::btnBackCallback, this));
	this->addChild(button_back);

	/*auto button_start = Button::create("start.png", "start_selected.png", "start_disabled.png");
	button_start->setPosition(Vec2(150, 50));
	button_start->addClickEventListener(CC_CALLBACK_1(SelectScene::btnStartCallback, this));
	this->addChild(button_start);*/

	auto label1 = Label::createWithTTF("Select Songs", "fonts/Marker Felt.ttf", 24);
	label1->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - label1->getContentSize().height));
	this->addChild(label1);

	TableView* tableView = TableView::create(this, CCSizeMake(visibleSize.width / 2, visibleSize.height-150));
	tableView->setPosition(ccp(visibleSize.width / 2, origin.y + 100));
	this->addChild(tableView); 

	//��������
	tableView->setBounceable(true);                              //��������Ч��
	tableView->setDirection(cocos2d::extension::ScrollView::Direction::VERTICAL);  //����
	tableView->setDelegate(this);								  //ί�д���
	tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);  //��idС�Ŀ�ʼ����
	tableView->reloadData();									  //��������

	return true;
}

void SelectScene::btnBackCallback(Ref* pSender)
{
	Director::getInstance()->popScene();
}

void SelectScene::btnStartCallback(Ref* pSender) {
	
}

TableViewCell* SelectScene::tableCellAtIndex(TableView* table, ssize_t idx) 
{
	string message = song[idx].name;
	
	TableViewCell* cell = table->dequeueCell();  //������

	//δ����βһֱȡ
	if (!cell) {
		cell = new TableViewCell();
		cell->autorelease();  //�Զ��ͷ���Դ

		//���һ������ͼƬ
		Sprite* cellSprite = Sprite::create("song_unselected.png");
		cellSprite->setAnchorPoint(Point::ZERO);  //�������Ϊ���½�
		cellSprite->setPosition(ccp(0, 0));
		cellSprite->setOpacity(150);
		cellSprite->setTag(1);  //���ñ�ǩ
		cell->addChild(cellSprite,0,1);

		//���һ��label��ǩ
		LabelTTF* label = LabelTTF::create(message, "Georgia-BoldItalic", 40);
		label->setPosition(cellSprite->getContentSize().width / 2, cellSprite->getContentSize().height / 2);
		label->setTag(2);
		cellSprite->addChild(label, 0, 2);
	}
	else {
		//��������ͼƬ��ʹ������
		Texture2D* texture = TextureCache::sharedTextureCache()->addImage("song_unselected.png");
		Sprite* pSprite = (Sprite*)cell->getChildByTag(1);
		pSprite->setTexture(texture);

		//����ͼƬ���
		LabelTTF* pLabel = (LabelTTF*)pSprite->getChildByTag(2);
		pLabel->setString(message);
	}

	return cell;
}

//����idx������ÿ��cell�ĳߴ��С
Size SelectScene::tableCellSizeForIndex(TableView* table, ssize_t idx)
{
	return CCSizeMake(512, 65);
}

//һ��������cell
ssize_t SelectScene::numberOfCellsInTableView(TableView* table)
{
	return 10;
}

//ĳ��cell�����ʱ�ص�����
void SelectScene::tableCellTouched(TableView* table, TableViewCell* cell)
{
	ssize_t id = cell->getIdx();
	char bg[20];
	sprintf(bg, "./song_bg/song%d.jpg", id % 3 + 1);
	log("cell touched at index: %i", id); //����̨���
	Blink *blink_ = Blink::create(0.5f, 1);  //ͼƬ��˸
	cell->runAction(blink_);

	//������ͼƬ
	Sprite* replace = (Sprite*)this->getChildByTag(123);
	Texture2D* rTexture = TextureCache::sharedTextureCache()->addImage(bg);
	replace->setTexture(rTexture);
}

void SelectScene::tableCellHighlight(TableView* table, TableViewCell* cell) {

	Texture2D *aTexture = TextureCache::sharedTextureCache()->addImage("song_selected.png");
	Sprite *pSprite = (Sprite *)cell->getChildByTag(1);
	pSprite->setTexture(aTexture);
}

void SelectScene::tableCellUnhighlight(TableView* table, TableViewCell* cell) {

	Texture2D *aTexture = TextureCache::sharedTextureCache()->addImage("song_unselected.png");
	Sprite *pSprite = (Sprite *)cell->getChildByTag(1);
	pSprite->setTexture(aTexture);
}

//����ʱ�ص�����
void SelectScene::scrollViewDidScroll(cocos2d::extension::ScrollView* view) { } 
//����ʱ�ص�����
void SelectScene::scrollViewDidZoom(cocos2d::extension::ScrollView* view) { }   

void SelectScene::getFileNames(string path, vector<string>& files)
{
	//�ļ����  
	long hFile = 0;
	//�ļ���Ϣ  
	struct _finddata_t fileinfo;
	string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			//�����Ŀ¼,����֮  
			//�������,�����б�  
			if ((fileinfo.attrib &  _A_SUBDIR))
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
					getFileNames(p.assign(path).append("\\").append(fileinfo.name), files);
			}
			else
			{
				files.push_back(p.assign(path).append("\\").append(fileinfo.name));
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
}

void SelectScene::getMessages() {
	char * filePath = "F:\\MusicGame\\Resources\\song_message";
	//��ȡ��·���µ������ļ�  
	getFileNames(filePath, files);
	size = files.size();
	vector<string> temp_filenames(size);
	for (int i = 0; i < size; i++)
	{
		temp_filenames[i] = files[i].c_str();
	}
	filenames = temp_filenames;

	vector<songs> temp_song(size);
	for (int i = 0; i < size; i++) {
		ifstream in(filenames[i]);
		string line;
		getline(in, line);
		temp_song[i].name = line;
		getline(in, line);
		temp_song[i].author = line;
	}
	song = temp_song;
}