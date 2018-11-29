#pragma once

struct SG_NoteInfo
{
	int judgeTime;
	int appearTime;
	int whichWay;
	int speed;


	SG_NoteInfo(int judge_time, int which_way, int speed)
		: judgeTime(judge_time),
		  whichWay(which_way),
		  speed(speed)
	{
		appearTime = judgeTime - (700 - 200) / speed;
	}
};