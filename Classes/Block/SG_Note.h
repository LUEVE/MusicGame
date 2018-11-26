#pragma once
#include "cocos2d.h"
#include "2d/CCSprite.h"
#include <string>
using namespace std;
using namespace cocos2d;

class SG_Note : public Sprite
{
public:
	static SG_Note* create(const string &filename,const Rect& rect);
	static SG_Note* create(const string &filename);
	static SG_Note* create(const string &filename,Scene*father);
	//
	string get_color();
	int get_shape();
	double get_offset();
	char get_keyType();

	void set_color(string color);
	void set_shape(int shape);
	void set_offset(double offset);
	void set_keyType(char keyType);
	//


private:
	string color;
	int shape;
	char keyType;
	double offset;
	bool initWithFile(const std::string& filename,const Rect& rect) override;
	bool initWithFile(const std::string& filename) override;
	void update(float delta) override;



};