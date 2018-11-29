#ifndef __ABOUT_SCENE_H__
#define __ABOUT_SCENE_H__
#include <iostream>
#include "cocos2d.h"
#include <string>
#include "ui/CocosGUI.h"
using namespace std;
using namespace cocos2d::ui;
class AboutScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	void menuBackCallBack(Ref * pSender);

	CREATE_FUNC(AboutScene);
};

#endif // __ABOUT_SCENE_H__
