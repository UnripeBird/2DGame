#include "stdafx.h"	
#include "burning.h"

HRESULT burning::init(string imageName, ENEMYDISCERN discernNum, int appearMapNum, POINT pos)
{

	enemy::init(imageName, discernNum, appearMapNum, pos);
	//이동속도 1.0
	_moveSpeed = 1.0f;

	_rezen = pos;
	_state = 0;
	_dr = drright;
	_framey = 0;
	_framex = -1;
	_ani->init(933 * 3, 600 * 3, 200, 100 * 3);
	_ani->setPlayFrame(0, 3, false, true);
	_ani->setFPS(3);
	_ani->start();
	return S_OK;
}

void burning::update(image * pixelimage, POINT playerPoint, vector<fieldObject*> objectVec, vector<bullet*> bulletVec)
{

	_ani->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
	_hitWorldTimer = TIMEMANAGER->getWorldTime();

	//움직이는 방향

	//움직임

	
}

void burning::Hit()
{
	_hitCount = true;

	_hitTimer = TIMEMANAGER->getWorldTime();
}

void burning::move()
{
	_ani->setPlayFrame(0, 3, false, true);
	_ani->setFPS(3);
	if (_ani->isPlay() == false)
	{
		_ani->start();
	}
}


void burning::attackmoveleft()
{

	_ani->setPlayFrame(14, 27, false, true);
	_ani->setFPS(3);
	
}

void burning::attackmoveright()
{
	_ani->setPlayFrame(28, 41, false, true);
	_ani->setFPS(3);
	
}

void burning::hitmove()
{

	_ani->setPlayFrame(42, 42, false, true);
	_ani->setFPS(3);
	_ani->start();
}
