#pragma once
#include "cocos2d.h"
#include <vector>
#include "SG_Note.h"
#include <queue>
#include "SG_NoteInfo.h"

#define MISS 4
#define GOOD 3
#define GREAT 2
#define PERFECT 1
#define JUDGE_NUM (4+1)

USING_NS_CC;

class SG_Game
{
public:
	const static int WAYS = 4;
	const static int MISSPLACE = 150;
	const static int GOODPLACE = 100;
	const static int GREATPLACE = 50;
	const static int PERFECTPLACE = 25;


	const static int COMBOSTATE_ONE_NUM = 5;
	const static int COMBOSTATE_TWO_NUM = 10;
	const static int COMBOSTATE_THREE_NUM = 20;
	const static int GOODSCORE = 150;
	const static int GREATSCORE = 200;
	const static int PERFECTSCORE = 250;

	const static int GOODSCORE_50 = 200;
	const static int GREATSCORE_50 = 250;
	const static int PERFECTSCORE_50 = 300;

	const static int GOODSCORE_100 = 300;
	const static int GREATSCORE_100 = 350;
	const static int PERFECTSCORE_100 = 400;
	
	long long gameScore = 0;
	int judgeCount[JUDGE_NUM];
	std::vector<std::vector<SG_Note*>> notes; // now notes
	std::queue<SG_NoteInfo> allNotes; // all notes in one game
	SG_Game();
private:

};
