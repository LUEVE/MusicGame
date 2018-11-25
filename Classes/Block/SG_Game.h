#pragma once
#include "cocos2d.h"
#include <vector>
#include "SG_Note.h"

USING_NS_CC;

class SG_Game
{
public:
	const static int WAYS = 4;
	std::vector<std::vector<SG_Note*>> notes;
	SG_Game();
private:

};
