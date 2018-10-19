#ifndef __SETTING_SCENE_H__
#define __SETTING_SCENE_H__
#include <iostream>
#include "cocos2d.h"
#include <string>
#include "ui/CocosGUI.h"
using namespace std;
using namespace cocos2d::ui;
class SettingScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	void btnBackCallback(Ref * pSender);

	CREATE_FUNC(SettingScene);
};

#endif // __SETTING_SCENE_H__
