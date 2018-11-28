﻿#pragma once
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
	std::vector<std::vector<SG_Note*>> notes;
	SG_Game();
private:

};
