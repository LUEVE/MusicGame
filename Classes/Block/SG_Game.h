#pragma once
#include "cocos2d.h"
#include <vector>
#include "SG_Note.h"
#include <queue>
#include "SG_NoteInfo.h"

USING_NS_CC;

class SG_Game
{
public:
	const static int WAYS = 4;
	std::vector<std::vector<SG_Note*>> notes; // now notes
	std::queue<SG_NoteInfo> allNotes; // all notes in one game
	SG_Game();
private:

};
