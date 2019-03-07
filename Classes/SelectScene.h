#ifndef __SELECT_SCENE_H__
#define __SELECT_SCENE_H__

#include "cocos2d.h"
using namespace cocos2d;

#include "cocos-ext.h"
using namespace cocos2d::extension;

#include "ui/CocosGUI.h"
using namespace cocos2d::ui;

#include <io.h>
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

class SelectScene : public Layer, public TableViewDataSource, public TableViewDelegate {
public:

	virtual bool init();
	CREATE_FUNC(SelectScene);
	static cocos2d::Scene* createScene();
	static cocos2d::Scene* createScene(string _filePath);
	SelectScene();
	SelectScene(string filePath);
	static SelectScene* SelectScene::create(string _filePath);

	struct Songs {
		string name;
		string author;
	};

	int size;
	string filePath = ".\\SongInformation";
	vector<string> files;
	vector<string> filenames;
	vector<Songs> song;
	void getFileNames(string path, vector<string>& files);
	void getMessages();

	void btnBackCallback(Ref * pSender);
	void btnStartCallback(Ref * pSender);

	//继承于CCTableViewDataSource
	virtual Size tableCellSizeForIndex(TableView* table, ssize_t idx);         //根据idx来设置每项cell的尺寸大小
	virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx);    //获取编号为idx的cell
	virtual ssize_t numberOfCellsInTableView(TableView *table);                //一共多少项cell
	virtual void tableCellHighlight(TableView* table, TableViewCell* cell);    //按下去的时候,高亮显示
	virtual void tableCellUnhighlight(TableView* table, TableViewCell* cell);  //松开时取消高亮
	
	//继承于CCTableViewDelegate
	virtual void tableCellTouched(TableView* table, TableViewCell* cell);          //某项cell被点击时回调函数
	virtual void scrollViewDidScroll(cocos2d::extension::ScrollView* view);        //滚动时回调函数
	virtual void scrollViewDidZoom(cocos2d::extension::ScrollView* view);          //放缩时回调函数

};

#endif // __SELECT_SCENE_H__