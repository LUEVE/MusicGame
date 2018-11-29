#ifndef __REUSLT_SCENE_H__
#define __REUSLT_SCENE_H__
#include <iostream>
#include "cocos2d.h"
#include <string>
#include "ui/CocosGUI.h"
#include "Block/SG_Game.h"

#define SS_RANK 9527
#define S_RANK 666
#define A_RANK 233
#define B_RANK 114514
#define C_RANK 555
#define D_RANK 886

using namespace std;
using namespace cocos2d::ui;
class ResultScene : public cocos2d::Scene
{
public:
	SG_Game game;
	time_t start_time, now_time;
	cocos2d::Label *judgeLabel[JUDGE_NUM], *scoreLabel;
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
	int calScoreValue(int perfect, int great, int good, int miss, int allNotesNum) {
		double value;
		value = perfect * 1.0 + great * 0.7 + good * 0.5;
		value /= allNotesNum;
		return static_cast<int>(value);
	}
	ResultScene() {}

	CREATE_FUNC(ResultScene);
	
};

#endif // __REUSLT_SCENE_H__
