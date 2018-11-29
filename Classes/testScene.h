#pragma once

#include "cocos2d.h"
#include "Block/SG_Note.h"
#include "Block/SG_Game.h"
#include <fstream>

class testScene : public cocos2d::Scene
{
private:
	bool played = true;
	SG_Game game;
	vector<Sprite*> judges;
	ifstream scoreIfs;
	int frameCnt = 0;
	std::chrono::steady_clock::time_point startPoint;
public:
	virtual bool init();

	double getDurationFromBegin(const std::chrono::steady_clock::time_point & nowPoint);

	void update(float dt);
	void oneFrameForward();
	void appearNotes();
	void judgeNotes();

	CREATE_FUNC(testScene);


	testScene();
};
