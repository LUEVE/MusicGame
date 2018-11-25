#include "Block/SG_Note.h"

Sprite* SG_Note::create(const string& filename, const Rect& rect)
{
	Sprite *sprite = new (std::nothrow) SG_Note;
	if (sprite && sprite->initWithFile(filename,rect))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}
Sprite* SG_Note::create(const string& filename)
{
	Sprite *sprite = new (std::nothrow) SG_Note;
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


