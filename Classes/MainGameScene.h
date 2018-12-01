#ifndef __MAINGAME_SCENE_H__
#define __MAINGAME_SCENE_H__
#include <iostream>
#include "cocos2d.h"
#include <string>
#include "ui/CocosGUI.h"
#include "Block/SG_Game.h"
#include <ctime>
#include <fstream>
#include "SimpleAudioEngine.h"


// 游戏开始MAX_RUNNING_TIME秒之后结束
#define MAX_RUNNING_TIME 15
using std::string;
using namespace std;
class MainGameScene : public cocos2d::Scene
{
public:
	static std::chrono::steady_clock::time_point pauseStart;
	static std::chrono::steady_clock::time_point  pauseEnd;
	static chrono::steady_clock::duration pauseDuration;

	SG_Note* comboPlace;
	SG_Game game;
	int comboNumber = 0;
	ifstream scoreIfs;
	std::chrono::steady_clock::time_point startPoint;
	cocos2d::Label*comboNumberLabel, *gameScoreLabel, *addedGameScoreLabel;
	Size visibleSize;

	MainGameScene();
	MainGameScene(string songName);
	CREATE_FUNC(MainGameScene);
	static MainGameScene* create(string songName);

	static string bgmSongName;
	static string pureSongName;  // 歌曲名字不包含 .txt .mp3 之列后缀
	vector<string> musicEffect = {"MusicEffect\\Effect_cai.mp3","MusicEffect\\Effect_ruo.mp3","MusicEffect\\Effect_xing.mp3","MusicEffect\\Effect_qiang.mp3"};
	void preloadSoundResource(CocosDenshion::SimpleAudioEngine* sae);
	virtual bool init();
	static cocos2d::Scene* createScene();
	bool CreatAllSpirtInSong();
	double getDuration(const std::chrono::steady_clock::time_point &start, const std::chrono::steady_clock::time_point &end);
	void menuBackCallBack(Ref * pSender);
	void setJudgeAnimation(Animation* animation, int i);
	void oneFrameForward();
	void appearNotes();
	void update(float dt);
	void reFreshComboLebal();
	void reFreshGameScoreLabel(long long addedScore);

private:
	int frameCnt = 0;
};

#endif // __MAINGAME_SCENE_H__
