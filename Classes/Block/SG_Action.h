#pragma once
#include "cocos2d.h"
USING_NS_CC;
class SG_Action
{


	static Size visibleSize;
public:
	static Sequence* addScoreAction();
	static RepeatForever * notesAction(int speed);
	static void setVisibleSize(Size v);


};