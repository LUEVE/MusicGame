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

	//继承于CCTableViewDataSource
	virtual Size tableCellSizeForIndex(TableView* table, ssize_t idx);     //根据idx来设置每项cell的尺寸大小
	virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx);//获取编号为idx的cell
	virtual ssize_t numberOfCellsInTableView(TableView *table);                  //一共多少项cell
	
	//继承于CCTableViewDelegate
	virtual void tableCellTouched(TableView* table, TableViewCell* cell);          //某项cell被点击时回调函数
	virtual void scrollViewDidScroll(cocos2d::extension::ScrollView* view);        //滚动时回调函数
	virtual void scrollViewDidZoom(cocos2d::extension::ScrollView* view);          //放缩时回调函数
};

#endif // __SELECT_SCENE_H__