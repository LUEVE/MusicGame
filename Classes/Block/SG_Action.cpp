#include "SG_Action.h"
Sequence* SG_Action::addScoreAction()
{
	auto moveUp = MoveBy::create(0.2, Vec2(0, visibleSize.height / 40));
	auto moveDown = MoveBy::create(0.2, Vec2(0, visibleSize.height / 40));
	auto fadeIn = FadeIn::create(0.2f);
	auto fadeOut = FadeOut::create(0.2f);
	auto showSpawn = Spawn::createWithTwoActions(moveUp, fadeIn);
	auto disappearSpawn = Spawn::createWithTwoActions(moveDown, fadeOut);
	auto addScoreAction = Sequence::create(showSpawn, disappearSpawn, nullptr);
	return addScoreAction;

}

RepeatForever* SG_Action::notesAction(int speed)
{
	auto moveD = MoveBy::create(1 / 60.0, Vec2(0, -speed));
	auto fall = RepeatForever::create(moveD);
	return fall;
}

Size SG_Action::visibleSize;
void SG_Action::setVisibleSize(Size v)
{
	visibleSize = v;
}


