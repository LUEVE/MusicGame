#ifndef __PAUSE_SCENE_H__
#define __PAUSE_SCENE_H__
#include <iostream>
#include "cocos2d.h"
#include <string>
using namespace std;
class PauseScene : public cocos2d::Layer
{
public:
	//static cocos2d::Scene* createScene(cocos2d::RenderTexture* sqr);
	static cocos2d::Scene* createScene();

	virtual bool init();

	void menuResumeCallback(cocos2d::Ref* pSender);
	void menuSettingCallback(cocos2d::Ref* pSender);
	void menuExitCallback(cocos2d::Ref* pSender);
	void menuRestartCallback(cocos2d::Ref* pSender);
	CREATE_FUNC(PauseScene);
};

#endif // __PAUSE_SCENE_H__
