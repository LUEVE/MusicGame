#ifndef __SELECT_SCENE_H__
#define __SELECT_SCENE_H__

#include "cocos2d.h"
using namespace cocos2d;

#include "cocos-ext.h"
using namespace cocos2d::extension;

#include "ui/CocosGUI.h"
using namespace cocos2d::ui;

class SelectScene : public Layer, public TableViewDataSource, public TableViewDelegate
{
public:
	virtual bool init();
	static cocos2d::Scene* createScene();
	CREATE_FUNC(SelectScene);
	
	void menuBackCallBack(Ref * pSender);

	//�̳���CCTableViewDataSource
	virtual Size tableCellSizeForIndex(TableView* table, ssize_t idx);     //����idx������ÿ��cell�ĳߴ��С
	virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx);//��ȡ���Ϊidx��cell
	virtual ssize_t numberOfCellsInTableView(TableView *table);                  //һ��������cell
	
	//�̳���CCTableViewDelegate
	virtual void tableCellTouched(TableView* table, TableViewCell* cell);          //ĳ��cell�����ʱ�ص�����
	virtual void scrollViewDidScroll(cocos2d::extension::ScrollView* view);        //����ʱ�ص�����
	virtual void scrollViewDidZoom(cocos2d::extension::ScrollView* view);          //����ʱ�ص�����
};

#endif // __SELECT_SCENE_H__