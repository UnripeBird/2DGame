#include "stdafx.h"
#include "player.h"

enum POSE
{
	NONE,
	IDLE,
	SLIDING,
	WALK,
	RUN,
	SWALLOW,
	JUMPING,
	FALLING,
	LANDING,
	FLY
};

HRESULT player::init(void)
{
	_x = 100;
	_y = 400;
	_curJump = 0;
	_maxJump = 0;
	_maxJump = 0;
	_gravity = 2;

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
	_aniControl = NONE;

	_starFrame = 0;
	_endFrame = 0;
	_curRight = true;
	_keyDownNum = 0;
	_playAni = false;

	_image = IMAGEMANAGER->findImage(_fileName[_fileNum]);

	_ani = new animation;
	_ani->init(1728, 3648, 96, 96);
	_ani->setPlayFrame(_starFrame, _endFrame, false, true);
	_ani->setFPS(5);
	_ani->start();

	DublleKeyWorldTimer = 0;
	DubbleKeyTimer = 0;

	return S_OK;
}

void player::release(void)
{
}

void player::update(vector<fieldObject*> objectPos, vector<enemy*> enemyPos, image* pixelimage)
{
	_pixelImage = pixelimage;
	move(objectPos);
	objectCollision(objectPos);
	enemyCollision(enemyPos);
	_ani->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);

	//픽셀 충돌
	bool groundCollision = false;
	if (_pose == LANDING)
	{
		_pose = IDLE;
		_playAni = true;
	}

	//충돌 - 아래
	for (int i = _rc.bottom - 1; i < _rc.bottom + 1; i++)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("pixel0")->getMemDC(), _x, i);
	
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);
	
		if (r == 255 && g == 0 && b == 0)
		{
			_y = i - 25 ;
			groundCollision = true;
			
			if (_pose == FALLING)
				{
					_pose = LANDING;
					_playAni = true;
				}

			break;
		}
	}

	if (!groundCollision)
	{
		_y += _gravity;
	}

	if (!groundCollision)
	{
		_y += _gravity;
	}
	
	if (_pose == JUMPING && _curJump >= _maxJump) //올라가는 중
	{
		_y -= 8;
		_curJump = _y;
	}
	else if (_pose == JUMPING) //내려오는 중
	{
		_pose = FALLING;
		_playAni = true;
	}

	//슬라이딩
	if (_aniControl == SLIDING)
	{

	}
}

void player::move(vector<fieldObject*> objectPos)
{
	DublleKeyWorldTimer = TIMEMANAGER->getWorldTime();
	int direction = 0;

	//오른쪽
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT) && _pose == IDLE)
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
		}
		_curRight = true;
		_playAni = true;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && _pose != SWALLOW)
	{
		if (_pose == WALK && rightMove())
		{
			_x += PLAYERSPEED;
		}
		else if(_pose == RUN && rightMove())
		{
			_x += PLAYERSPEED * 1.5;
			_keyDownNum = 0;
		}
		else if (_pose == JUMPING && rightMove())
		{
			_x += PLAYERSPEED;
			_curRight = true;
		}
		else if (_pose == FALLING && rightMove())
		{
			_x += PLAYERSPEED;
			_curRight = true;
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

	//왼쪽
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT) && _pose == IDLE)
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
		}
		_curRight = false;
		_playAni = true;
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && _pose != SWALLOW)
	{
		if (_pose == WALK && leftMove())
		{
			_x -= PLAYERSPEED;
		}
		else if (_pose == RUN && leftMove())
		{
			_x -= PLAYERSPEED * 1.5;
			_keyDownNum = 0;
		}
		else if (_pose == JUMPING && rightMove())
		{
			_x -= PLAYERSPEED;
			_curRight = false;
		}
		else if (_pose == FALLING && rightMove())
		{
			_x -= PLAYERSPEED;
			_curRight = false;
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

	//아래키
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

	//Z
	if (KEYMANAGER->isOnceKeyDown('Z'))
	{
		if (_pose == SWALLOW)
		{
			_pose = SLIDING;
			_playAni = true;
			_aniControl = SLIDING;
		}
		else 
		{
			_pose = JUMPING;
			_playAni = true;
			_curJump = _y;
			_maxJump = _curJump - 200;
		}
	}
	if (KEYMANAGER->isStayKeyDown('Z'))
	{
	}
	if (KEYMANAGER->isOnceKeyUp('Z'))
	{
	}

	//애니메이션
	switch (_pose)
	{
	case IDLE:
		if (_curRight == true) { _starFrame = 0; _endFrame = 0; }
		else { _starFrame = 18; _endFrame = 18; }
		break;
	case WALK:
		if (_curRight == true) { _starFrame = 144; _endFrame = 153; }
		else { _starFrame = 162; _endFrame = 171; }
		break;
	case RUN:
		if (_curRight == true) { _starFrame = 180;  _endFrame = 187; }
		else { _starFrame = 198; _endFrame = 205; }
		break;
	case SWALLOW:
		if (_curRight == true) { _starFrame = 36; _endFrame = 37; }
		else { _starFrame = 54; _endFrame = 55; }
		break;
	case SLIDING:
		if (_curRight == true) { _starFrame = 72; _endFrame = 73; }
		else { _starFrame = 90; _endFrame = 91; }
		break;
	case JUMPING:
		if (_curRight == true) { _starFrame = 108; _endFrame = 108; }
		else { _starFrame = 126; _endFrame = 126; }
		break;
	case FALLING:
		if (_curRight == true) { _starFrame = 109; _endFrame = 116; }
		else { _starFrame = 127; _endFrame = 134; }
		break;
	case LANDING:
		if (_curRight == true) { _starFrame = 117; _endFrame = 117; }
		else { _starFrame = 135; _endFrame = 135; }
		break;
	case FLY:
		if (_curRight == true) { _starFrame = 218; _endFrame = 120; }
		else { _starFrame = 135; _endFrame = 135; }
		break;
	default:
		break;
	}
	if (_playAni == true && _pose != FALLING)
	{
		_ani->setPlayFrame(_starFrame, _endFrame, false, true);
		_ani->start();
		_playAni = false;
	}
	else if (_playAni == true)
	{
		_ani->setPlayFrame(_starFrame, _endFrame, false, false);
		_ani->start();
		_playAni = false;
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

bool player::rightMove()
{
	bool _horizonMove = true;
	for (int i = _rc.right - 1; i < _rc.right + 1; i++)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("pixel0")->getMemDC(), i, _y);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (r == 255 && g == 0 && b == 0)
		{
			_x = i - 25;
			_horizonMove = false;
			break;
		}
	}
	return _horizonMove;
}

bool player::leftMove()
{
	bool _horizonMove = true;
	for (int i = _rc.left + 1; i < _rc.left - 1; i++)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("pixel0")->getMemDC(), i, _y);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (r == 255 && g == 0 && b == 0)
		{
			_x = i + 25;
			_horizonMove = false;
			break;
		}
	}
	return _horizonMove;
}

