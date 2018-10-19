#ifndef __MAINGAME_SCENE_H__
#define __MAINGAME_SCENE_H__
#include <iostream>
#include "cocos2d.h"
#include <string>
#include "ui/CocosGUI.h"
using namespace std;
using namespace cocos2d::ui;
class MainGameScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	void btnBackCallback(Ref * pSender);

	CREATE_FUNC(MainGameScene);
};

#endif // __MAINGAME_SCENE_H__
