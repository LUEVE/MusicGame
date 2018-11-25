#ifndef __MAINGAME_SCENE_H__
#define __MAINGAME_SCENE_H__
#include <iostream>
#include "cocos2d.h"
#include <string>
#include "ui/CocosGUI.h"
#include "Block/SG_Game.h"
using namespace std;
class MainGameScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	bool CreatAllSpirtInSong();
	virtual bool init();

	void btnBackCallback(Ref * pSender);
	

	void try_fuck2(float t, int data, std::string name);
	//void try_fuck2(float t, void* data, std::string name);
	void changeSpirt();

	CREATE_FUNC(MainGameScene);

	SG_Game game;
};

#endif // __MAINGAME_SCENE_H__
