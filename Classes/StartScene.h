#ifndef __START_SCENE_H__
#define __START_SCENE_H__
#include <iostream>
#include "cocos2d.h"
#include <string>
using namespace std;
class StartScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	void createMenu();


	void menuStartCallback(cocos2d::Ref* pSender);
	void menuSettingCallback(cocos2d::Ref* pSender);
	void menuAboutCallback(cocos2d::Ref* pSender);
	void menuExitCallback(cocos2d::Ref* pSender);

	CREATE_FUNC(StartScene);

private:
	cocos2d::MenuItemSprite* createSprite(string text, const cocos2d::ccMenuCallback& callback);
};

#endif // __START_SCENE_H__
