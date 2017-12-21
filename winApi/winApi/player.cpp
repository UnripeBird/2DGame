#include "stdafx.h"
#include "player.h"

enum POSE
{
	IDLE,
	SLIDING,
	WALK,
	RUN,
	SWALLOW,
	JUMP
};

HRESULT player::init(void)
{
	_x = 100;
	_y = 100;

	_x = 100;
	_y = 100;

	IMAGEMANAGER->addFrameImage("kirby", "image/kirby.bmp", 1728, 3648, 18, 38, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("kirby_burning", "image/kirby_burning.bmp", 5520, 4752, 23, 22, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("kirby_freeze", "image/kirby_freeze.bmp", 1872, 6048, 18, 24, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("kirby_spark", "image/kirby_spark.bmp", 3840, 5412, 20, 22, true, RGB(255, 0, 255));

	_fileName[0] = "kirby";
	_fileName[1] = "kirby_burning";
	_fileName[2] = "kirby_freeze";
	_fileName[3] = "kirby_spark";
	_fileNum = 0;
	_pose = 0;
	_starFrame = 0;
	_endFrame = 1;
	_curRight = true;
	_keyDownNum = 0;
	_playAni = false;
	_alreadyMove = false;

	_image = IMAGEMANAGER->findImage(_fileName[_fileNum]);

	_ani = new animation;
	_ani->init(1728, 3648, 96, 96);
	_ani->setPlayFrame(0, 1, false, true);
	_ani->setFPS(5);
	_ani->start();

	DublleKeyWorldTimer = 0;
	DubbleKeyTimer = 0;

	return S_OK;
}

void player::release(void)
{
}

void player::update(vector<fieldObject*> objectPos, vector<enemy*> enemyPos)
{
	move(objectPos);
	objectCollision(objectPos);
	enemyCollision(enemyPos);
	_ani->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
}

void player::move(vector<fieldObject*> objectPos)
{
	DublleKeyWorldTimer = TIMEMANAGER->getWorldTime();
	int direction = 0;

	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		if (_pose != SWALLOW && _alreadyMove == false)
		{
			if (_keyDownNum < 1)
			{
				_keyDownNum += 1;
				_pose = WALK;
			}
			else
			{
				_keyDownNum += 1;
				_pose = RUN;
			}
			_alreadyMove = true;
		}
		_curRight = true;
		_playAni = true;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && _pose != SWALLOW)
	{
		if (_pose == WALK)
		{
			_x += PLAYERSPEED;
		}
		else if(_pose == RUN)
		{
			_x += PLAYERSPEED * 1.5;
			_keyDownNum = 0;
		}
		direction = 1;
		moveCollision(objectPos, direction);
	}

	if (KEYMANAGER->isOnceKeyUp(VK_RIGHT) && _pose != SWALLOW)
	{
		_pose = IDLE;
		_playAni = true;
		DubbleKeyTimer = TIMEMANAGER->getWorldTime();
	}

	if (_keyDownNum >= 1 && DublleKeyWorldTimer - DubbleKeyTimer > 0.8f)
	{
		DubbleKeyTimer = TIMEMANAGER->getWorldTime();
		_keyDownNum = 0;
	}

	//---------------------------------------

	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		if (_pose != SWALLOW)
		{
			if (_keyDownNum < 1)
			{
				_keyDownNum += 1;
				_pose = WALK;
			}
			else
			{
				_keyDownNum += 1;
				_pose = RUN;
			}
			_alreadyMove = true;
		}
		_curRight = false;
		_playAni = true;
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && _pose != SWALLOW)
	{
		if (_pose == WALK && _alreadyMove == false)
		{
			_x -= PLAYERSPEED;
		}
		else if (_pose == RUN)
		{
			_x -= PLAYERSPEED * 1.5;
			_keyDownNum = 0;
		}
		direction = 1;
		moveCollision(objectPos, direction);
	}
	if (KEYMANAGER->isOnceKeyUp(VK_LEFT) && _pose != SWALLOW)
	{
		_pose = IDLE;
		_playAni = true;
		DubbleKeyTimer = TIMEMANAGER->getWorldTime();
	}

	//--------------------------------------------

	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		_pose = SWALLOW;
		_playAni = true;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_DOWN))
	{
		_pose = IDLE;
		_playAni = true;
	}

	//-----------------------------

	if (KEYMANAGER->isOnceKeyDown('Z'))
	{
		if (_pose == SWALLOW)
		{
			_pose = SLIDING;
			_playAni = true;
		}
		else 
		{
			_pose = JUMP;
			_playAni = true;
		}
	}
	if (KEYMANAGER->isStayKeyDown('Z'))
	{
		if (_pose == SLIDING)
		{
			_ani->pause();
		}
	}
	if (KEYMANAGER->isOnceKeyUp('Z'))
	{
		_ani->resume();
	}
	//if (KEYMANAGER->isStayKeyDown(VK_UP))
	//{
	//	_y -= PLAYERSPEED;
	//	direction = 4;
	//	moveCollision(objectPos, direction);
	//}
	//if (KEYMANAGER->isOnceKeyUp(VK_UP))
	//{
	//
	//}

	switch (_pose)
	{
	case IDLE:
		if (_curRight == true)
		{
			_starFrame = 0;
			_endFrame = 1;
		}
		else
		{
			_starFrame = 18;
			_endFrame = 19;
		}
		break;
	case WALK:
		if (_curRight == true)
		{
			_starFrame = 144;
			_endFrame = 153;
		}
		else
		{ 
			_starFrame = 162;
			_endFrame = 171;
		}
		break;
	case RUN:
		if (_curRight == true)
		{
			_starFrame = 180;
			_endFrame = 187;
		}
		else
		{
			_starFrame = 198;
			_endFrame = 205;
		}
		break;
	case SWALLOW:
		if (_curRight == true)
		{
			_starFrame = 36;
			_endFrame = 37;
		}
		else
		{
			_starFrame = 54;
			_endFrame = 55;
		}
		break;
	case SLIDING:
		if (_curRight == true)
		{
			_starFrame = 72;
			_endFrame = 73;
		}
		else
		{
			_starFrame = 90;
			_endFrame = 91;
		}
		break;
	case JUMP:
		if (_curRight == true)
		{
			_starFrame = 108;
			_endFrame = 117;
		}
		else
		{
			_starFrame = 126;
			_endFrame = 135;
		}
		break;
	default:
		break;
	}
	if (_playAni == true)
	{
		_ani->setPlayFrame(_starFrame, _endFrame, false, true);
		_ani->start();
		_playAni = false;
		//_keyDownNum = 0;
	}

}

void player::moveCollision(vector<fieldObject*> objectPos, int direction)
{
	RECT temp;

	_rc = RectMakeCenter(_x, _y, 50, 50);

	for (int i = 0; i < objectPos.size(); i++)
	{
		if (IntersectRect(&temp, &_rc, &objectPos[i]->getrc()))
		{
			switch (direction)
			{
				case 1:
					_x = objectPos[i]->getrc().left - 25;
					break;
				case 2:
					_x = objectPos[i]->getrc().right + 25;
					break;
				case 3:
					_y = objectPos[i]->getrc().top - 25;
					break;
				case 4:
					_y = objectPos[i]->getrc().bottom + 25;
					break;
			}
		}
	}
}

bool player::objectCollision(vector<fieldObject*> objectPos)
{
	RECT temp;

	bool collision = false;

	_rc = RectMakeCenter(_x, _y, 50, 50);

	for (int i = 0; i < objectPos.size(); i++)
	{
		if (IntersectRect(&temp, &_rc, &objectPos[i]->getrc()))
		{
			objectCollisionReaction(objectPos, i);
			collision = true;
		}
	}

	return collision;
}

void player::objectCollisionReaction(vector<fieldObject*> objectPos, int collisionNum)
{
	switch (objectPos[collisionNum]->getDiscernNum())
	{
		case box:
			break;
	}
}

bool player::enemyCollision(vector<enemy*> enemyPos)
{
	RECT temp;

	bool collision = false;
	
	_rc = RectMakeCenter(_x, _y, 50, 50);

	for (int i = 0; i < enemyPos.size(); i++)
	{
		if (IntersectRect(&temp, &_rc, &enemyPos[i]->getrc()))
		{
			enemyCollisionReaction(enemyPos, i);
			collision = true;
		}
	}

	return collision;
}

void player::enemyCollisionReaction(vector<enemy*> enemyPos, int collisionNum)
{
	switch (enemyPos[collisionNum]->getDiscernNum())
	{
		case enemyBox:
			enemyPos[collisionNum]->setState(2);
			break;
	}
}
