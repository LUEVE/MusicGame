#ifndef __REUSLT_SCENE_H__
#define __REUSLT_SCENE_H__
#include <iostream>
#include "cocos2d.h"
#include <string>
#include "ui/CocosGUI.h"
#include "Block/SG_Game.h"

using namespace std;
using namespace cocos2d::ui;
class ResultScene : public cocos2d::Scene
{
public:
	SG_Game game;
	time_t start_time, now_time;
	cocos2d::Label judgeLabel[JUDGE_NUM];
	int finalRank;

	static ResultScene* createScene();
	virtual bool init();
	void setGame(SG_Game game) {
		this->game.gameScore = game.gameScore;
		for (int i = 0; i < JUDGE_NUM; ++i) {
			this->game.judgeCount[i] = game.judgeCount[i];
		}
		this->game.notes = game.notes;
	}
	void update(float dt);
	void btnBackCallback(Ref * pSender);
	ResultScene() {}

	CREATE_FUNC(ResultScene);
	
};

#endif // __REUSLT_SCENE_H__
