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

class SelectScene : public Layer, public TableViewDataSource, public TableViewDelegate{
public:

	virtual bool init();
	static cocos2d::Scene* createScene();
	CREATE_FUNC(SelectScene);
	
	struct songs {
		string name;
		string author;
	};

	int size;
	vector<string> files;
	vector<string> filenames;
	vector<songs> song;
	void getFileNames(string path, vector<string>& files);
	void getMessages();

	void btnBackCallback(Ref * pSender);
	void btnStartCallback(Ref * pSender);

	//�̳���CCTableViewDataSource
	virtual Size tableCellSizeForIndex(TableView* table, ssize_t idx);         //����idx������ÿ��cell�ĳߴ��С
	virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx);    //��ȡ���Ϊidx��cell
	virtual ssize_t numberOfCellsInTableView(TableView *table);                //һ��������cell
	virtual void tableCellHighlight(TableView* table, TableViewCell* cell);    //����ȥ��ʱ��,������ʾ
	virtual void tableCellUnhighlight(TableView* table, TableViewCell* cell);  //�ɿ�ʱȡ������
	
	//�̳���CCTableViewDelegate
	virtual void tableCellTouched(TableView* table, TableViewCell* cell);          //ĳ��cell�����ʱ�ص�����
	virtual void scrollViewDidScroll(cocos2d::extension::ScrollView* view);        //����ʱ�ص�����
	virtual void scrollViewDidZoom(cocos2d::extension::ScrollView* view);          //����ʱ�ص�����

};

#endif // __SELECT_SCENE_H__