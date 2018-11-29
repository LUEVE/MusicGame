#include "Block/SG_Note.h"

SG_Note::SG_Note(int speed, int judgeTime, int appearTime, int whichWay)
	: Sprite(), speed(speed), judgeTime(judgeTime), appearTime(appearTime), whichWay(whichWay)
{
}

SG_Note* SG_Note::create(const string& filename, int speed, int appearTime, int judgeTime, int whichWay)
{
	SG_Note *sprite = new (std::nothrow) SG_Note(speed, judgeTime, appearTime, whichWay);
	if (sprite && sprite->initWithFile(filename))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}


SG_Note* SG_Note::create(const string& filename, const Rect& rect)
{
	SG_Note *sprite = new (std::nothrow) SG_Note();
	if (sprite && sprite->initWithFile(filename,rect))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}
SG_Note* SG_Note::create(const string& filename)
{
	SG_Note *sprite = new (std::nothrow) SG_Note();
	if (sprite && sprite->initWithFile(filename))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

string SG_Note::get_color()
{
	return color;
}

int SG_Note::get_shape()
{
	return shape;
}

double SG_Note::get_offset()
{
	return offset;
}

char SG_Note::get_keyType()
{
	return keyType;
}

void SG_Note::set_shape(int shape)
{
	this->shape = shape;
}

void SG_Note::set_offset(double offset)
{
	this->offset = offset;
}

void SG_Note::set_keyType(char keyType)
{
	this->keyType = keyType;
}

void SG_Note::set_color(string color)
{
	this->color = color;
}

void SG_Note::update(float delta)
{
	//log("fuck");
}
bool SG_Note::initWithFile(const std::string& filename, const Rect& rect)
{
	if (!Sprite::initWithFile(filename, rect)) return false;
	scheduleUpdate();
	return true;
}
bool SG_Note::initWithFile(const std::string& filename)
{
	if (!Sprite::initWithFile(filename)) return false;
	scheduleUpdate();
	return true;
}


