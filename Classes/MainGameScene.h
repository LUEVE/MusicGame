#ifndef __MAINGAME_SCENE_H__
#define __MAINGAME_SCENE_H__
#include <iostream>
#include "cocos2d.h"
#include <string>
#include "ui/CocosGUI.h"
#include "Block/SG_Game.h"
#include <ctime>


// 游戏开始MAX_RUNNING_TIME秒之后结束
#define MAX_RUNNING_TIME 15

using namespace std;
class MainGameScene : public cocos2d::Scene
{
public:
	SG_Note* comboPlace;
	SG_Game game;
	int comboNumber = 0;

	static cocos2d::Scene* createScene();
	bool CreatAllSpirtInSong();
	virtual bool init();
	void menuBackCallBack(Ref * pSender);
	void setJudgeAnimation(Animation* animation, int i);
	void update(float dt);
	cocos2d::Label*comboNumberLabel, *gameScoreLabel, *addedGameScoreLabel;
	CREATE_FUNC(MainGameScene);

	time_t start_time, now_time;
};

#endif // __MAINGAME_SCENE_H__
