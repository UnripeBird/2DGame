#include "stdafx.h"
#include "woodboss.h"

HRESULT woodboss::init(string imageName, ENEMYDISCERN discernNum, int appearMapNum, POINT pos)
{
	enemy::init(imageName, discernNum, appearMapNum, pos);
	//이동속도 1.0
	_moveSpeed = 1.0f;

	_rezen = pos;
	_state = 0;
	
	_framey = 0;
	_framex = -1;
	_ani->init(200 * 3, 380 * 3, 120, 76 * 3);
	_ani->setPlayFrame(0, 1, false, true);
	_ani->setFPS(3);
	_ani->start();
	return S_OK;
}

void woodboss::update(image * pixelimage, POINT playerPoint, vector<fieldObject*> objectVec, vector<bullet*> bulletVec)
{
	_ani->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
	_hitWorldTimer = TIMEMANAGER->getWorldTime();

	face();
}

void woodboss::Hit()
{
}

void woodboss::face()
{

	_ani->setPlayFrame(0, 1, false, true);
	_ani->setFPS(3);
}

void woodboss::attackmoveleft()
{
}

void woodboss::attackmoveright()
{
}

void woodboss::hitmove()
{
}
