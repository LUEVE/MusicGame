#pragma once

#include "cocos2d.h"
#include <chrono>
#include <fstream>

class GeneratorScene : public cocos2d::Scene
{
private:
	int frameCnt = 0;
	bool played = true;
	std::chrono::steady_clock::time_point startPoint;
	void oneFrameForward();
	double getDurationFromBegin(const std::chrono::steady_clock::time_point &nowPoint); // in second
	std::ofstream scoreOfs;
	int currentSpeed = 5;
public:
	bool init() override;
	void writeNoteOut(int which);
	void update(float dt) override;

	void menuBackCallBack(Ref *pSender);

	CREATE_FUNC(GeneratorScene);

	GeneratorScene();
};