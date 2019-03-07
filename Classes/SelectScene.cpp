#include "SelectScene.h"
#include "SimpleAudioEngine.h"
#include <direct.h>
#include "MainGameScene.h"

USING_NS_CC;

Scene* SelectScene::createScene()
{
	Scene *scene = Scene::create();
	SelectScene *layer = SelectScene::create();
	scene->addChild(layer);
	return scene;
}
Scene* SelectScene::createScene(string _filePath)
{
	Scene *scene = Scene::create();
	SelectScene *layer = SelectScene::create(_filePath);
	scene->addChild(layer);
	return scene;
}
SelectScene::SelectScene()
{
	
}
SelectScene::SelectScene(string _filePath): filePath(_filePath)
{
};
//
SelectScene* SelectScene::create(string _filePath)
{

	SelectScene *pRet = new(std::nothrow)SelectScene(_filePath);
	if (pRet && pRet->init())
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = nullptr;
		return nullptr;
	}
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

	//属性设置
	tableView->setBounceable(true);                              //开启弹性效果
	tableView->setDirection(cocos2d::extension::ScrollView::Direction::VERTICAL);  //纵向
	tableView->setDelegate(this);								  //委托代理
	tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);  //从id小的开始排列
	tableView->reloadData();									  //加载数据

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
	
	TableViewCell* cell = table->dequeueCell();  //出队列

	//未到结尾一直取
	if (!cell) {
		cell = new TableViewCell();
		cell->autorelease();  //自动释放资源

		//添加一个精灵图片
		Sprite* cellSprite = Sprite::create("song_unselected.png");
		cellSprite->setAnchorPoint(Point::ZERO);  //设置描点为左下角
		cellSprite->setPosition(ccp(0, 0));
		cellSprite->setOpacity(150);
		cellSprite->setTag(1);  //设置标签
		cell->addChild(cellSprite,0,1);

		//添加一个label标签
		LabelTTF* label = LabelTTF::create(message, "Georgia-BoldItalic", 40);
		label->setPosition(cellSprite->getContentSize().width / 2, cellSprite->getContentSize().height / 2);
		label->setTag(2);
		cellSprite->addChild(label, 0, 2);
	}
	else {
		//更换精灵图片，使用纹理
		Texture2D* texture = TextureCache::sharedTextureCache()->addImage("song_unselected.png");
		Sprite* pSprite = (Sprite*)cell->getChildByTag(1);
		pSprite->setTexture(texture);

		//更改图片编号
		LabelTTF* pLabel = (LabelTTF*)pSprite->getChildByTag(2);
		
		pLabel->setString(message);
	}

	return cell;
}

//根据idx来设置每项cell的尺寸大小
Size SelectScene::tableCellSizeForIndex(TableView* table, ssize_t idx)
{
	return CCSizeMake(512, 65);
}

//一共多少项cell
ssize_t SelectScene::numberOfCellsInTableView(TableView* table)
{
	return this->files.size();
}

//某项cell被点击时回调函数
void SelectScene::tableCellTouched(TableView* table, TableViewCell* cell)
{
	ssize_t id = cell->getIdx();
	char bg[20];
	sprintf(bg, "./song_bg/song%d.jpg", id % 3 + 1);
	log("cell touched at index: %i", id); //控制台输出
	Blink *blink_ = Blink::create(0.5f, 1);  //图片闪烁
	cell->runAction(blink_);
	log("%s", song[id].name);
	//换背景图片
	Sprite* replace = (Sprite*)this->getChildByTag(123);
	Texture2D* rTexture = TextureCache::sharedTextureCache()->addImage(bg);
	replace->setTexture(rTexture);
	auto mainGameScene = MainGameScene::create(song[id].name);
	Director::getInstance()->pushScene(mainGameScene);
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

//滚动时回调函数
void SelectScene::scrollViewDidScroll(cocos2d::extension::ScrollView* view) { } 
//放缩时回调函数
void SelectScene::scrollViewDidZoom(cocos2d::extension::ScrollView* view) { }   

void SelectScene::getFileNames(string path, vector<string>& files)
{
	//文件句柄  
	long hFile = 0;
	//文件信息  
	struct _finddata_t fileinfo;
	string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			//如果是目录,迭代之  
			//如果不是,加入列表  
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
	//char   buffer[MAX_PATH];
	//getcwd(buffer, MAX_PATH);

	const char * filePath = (this->filePath).data();
	//获取该路径下的所有文件  
	getFileNames(filePath, files);
	size = files.size();
	vector<string> temp_filenames(size);
	for (int i = 0; i < size; i++)
	{
		temp_filenames[i] = files[i].c_str();
	}
	filenames = temp_filenames;

	vector<Songs> temp_song(size);
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