#pragma once
#include "cocos2d.h"
#include <vector>
#include "SG_Note.h"

USING_NS_CC;

class SG_Game
{
public:
	const static int WAYS = 4;
	const static int MISSPLACE = 150;
	const static int GOODPLACE = 100;
	const static int GREATPLACE = 50;
	const static int PERFECTPLACE = 25;

	const static int GOODSCORE = 150;
	const static int GREATSCORE = 200;
	const static int PERFECTSCORE = 250;

	const static int GOODSCORE_50 = 200;
	const static int GREATSCORE_50 = 250;
	const static int PERFECTSCORE_50 = 300;

	const static int GOODSCORE_100 = 300;
	const static int GREATSCORE_100 = 350;
	const static int PERFECTSCORE_100 = 400;

	std::vector<std::vector<SG_Note*>> notes;
	SG_Game();
private:

};
