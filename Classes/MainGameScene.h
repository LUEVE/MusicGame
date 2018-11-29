#ifndef __MAINGAME_SCENE_H__
#define __MAINGAME_SCENE_H__
#include <iostream>
#include "cocos2d.h"
#include <string>
#include "ui/CocosGUI.h"
#include "Block/SG_Game.h"
using namespace std;
class MainGameScene : public cocos2d::Scene
{
public:
	cocos2d::Label*comboNumberLabel;
	SG_Note* comboPlace;
	SG_Game game;
	int comboNumber = 0;

	static cocos2d::Scene* createScene();
	bool CreatAllSpirtInSong();
	virtual bool init();
	void btnBackCallback(Ref * pSender);
	void setJudgeAnimation(Animation* animation, int i);
	void update(float dt);
	CREATE_FUNC(MainGameScene);


};

#endif // __MAINGAME_SCENE_H__
