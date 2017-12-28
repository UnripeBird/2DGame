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
	FLY, //날기 대기상태
	FLYMOVE, //날기 무빙상태
	INHALE,	//공기 들이 마심
	EXHALE, //공기 내쉼
	M_INHALE, //몹 흡입
	M_EXHALE //별 뱉기
};

HRESULT player::init(void)
{
	_x = 100;
	_y = 400;
	_curJump = 0;
	_maxJump = 0;
	_curSliding = 0;
	_maxSliding = 0;
	_gravity = 4;
	_life = 99;
	_maxHp = 6;
	_curHp = _maxHp;

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
	_curSwallow = false;
	_curjumping = false;
	groundCollision = false;

	_image = IMAGEMANAGER->findImage(_fileName[_fileNum]);

	_ani = new animation;
	_ani->init(1728, 3648, 96, 96);
	_ani->setPlayFrame(_starFrame, _endFrame, false, true);
	_ani->setFPS(5);
	_ani->start();

	DublleKeyWorldTimer = 0;
	DubbleKeyTimer = 0;

	_imageX = _x - (_ani->getFrameWidth() / 2);
	_imageY = _y - (_ani->getFrameHeight() / 2) - 23;

	return S_OK;
}

void player::release(void)
{
}

void player::update(vector<fieldObject*> objectPos, vector<enemy*> enemyPos, image* pixelimage, bulletManager* BulletManager)
{
	groundCollision = false; //
	_pixelImage = pixelimage;
	move(objectPos);
	objectCollision(objectPos);
	enemyCollision(enemyPos);
	_ani->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
	
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		BulletManager->bulletFire(Star, PointMake(_x, _y), !_curRight);
		for (int i = 0; i < 5; i++)
		{
	//		enemyPos[i]->Hit();
		}
	//BulletManager->getBullet()[0]->getrc()

	}
	if (KEYMANAGER->isStayKeyDown(VK_SPACE))
	{

		for (int i = 2; i < 5; i++)
		{
			enemyPos[i]->Eating(getPos());
		}


	}
	if (KEYMANAGER->isOnceKeyUp(VK_SPACE))
	{
		for (int i = 2; i < 5; i++)
		{
			enemyPos[i]->setState(2);
		}

	}
	if (_pose == LANDING)
	{
		_pose = IDLE;
		_playAni = true;
	}

	//충돌 - 아래
	for (int i = _rc.bottom - 1; i < _rc.bottom + 1; i++)
	{
		COLORREF color = GetPixel(_pixelImage->getMemDC(), _x, i);
	
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);
	
		if (r == 255 && g == 0 && b == 0)
		{
			_y = i - 25 ;
			groundCollision = true;
			if (_pose == FALLING)
				{
					_curjumping =	false;
					_pose = LANDING;
					_playAni = true;
				}

			break;
		}
	}

	//바닥에 충돌할때까지 하강
	if (!groundCollision)
	{
		if (_pose != FLY)
		{
			_y += _gravity;
		}
		else //_pose == FLY 일때 하강 속도
		{
			_y += _gravity / 2;
		}
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
		if (_curRight == true && _curSliding <= _maxSliding && rightMove())
		{
			_x += 3;
			_curSliding = _x;
		}
		else if (_curRight == false && _curSliding >= _maxSliding && leftMove())
		{
			_x -= 3;
			_curSliding = _x;
		}
		else if (_curSwallow == true)
		{
			_aniControl = NONE;
			_pose = SWALLOW;
			_playAni = true;
		}
		else
		{
			_aniControl = NONE;
			_pose = IDLE;
			_playAni = true;
		}
	}
}

void player::move(vector<fieldObject*> objectPos)
{
	int direction = 0;
	DublleKeyWorldTimer = TIMEMANAGER->getWorldTime();

	//오른쪽
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		if (_pose != SWALLOW && _pose == IDLE)
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
		else if (_pose == RUN && rightMove())
		{
			_x += PLAYERSPEED * 1.5;
			_keyDownNum = 0;
		}
		else if (_pose == JUMPING && rightMove() || _pose == FLY && rightMove())
		{
			_x += PLAYERSPEED;
			_curRight = true;
		}
		else if (_pose == FALLING && rightMove())
		{
			_x += PLAYERSPEED;
			_curRight = true;
		}
	}

	if (KEYMANAGER->isOnceKeyUp(VK_RIGHT) && _pose != SWALLOW && _pose != JUMPING && _pose != FALLING && _pose != FLY)
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
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		if (_pose != SWALLOW && _pose == IDLE)
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
		else if (_pose == JUMPING && leftMove() || _pose == FLY && leftMove())
		{
			_x -= PLAYERSPEED;
			_curRight = false;
		}
		else if (_pose == FALLING && leftMove())
		{
			_x -= PLAYERSPEED;
			_curRight = false;
		}
	}
	if (KEYMANAGER->isOnceKeyUp(VK_LEFT) && _pose != SWALLOW && _pose != JUMPING && _pose != FALLING && _pose != FLY)
	{
		_pose = IDLE;
		_playAni = true;
		DubbleKeyTimer = TIMEMANAGER->getWorldTime();
	}

	//아래키
	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		if (_pose == IDLE || _pose == WALK || _pose == RUN)
		{
			_pose = SWALLOW;
			_playAni = true;
			_curSwallow = true;
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
	}
	if (KEYMANAGER->isOnceKeyUp(VK_DOWN) && _pose == SWALLOW)
	{
		_pose = IDLE;
		_playAni = true;
		_curSwallow = false;
	}

	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		if (_pose == FLY)
		{
			_y -= PLAYERSPEED + 1.5;
		}
	}


	//Z - 점프, 날기, 공격
	if (KEYMANAGER->isOnceKeyDown('Z'))
	{
		if (_pose == SWALLOW) //슬라이딩
		{
			_pose = SLIDING;
			_playAni = true;
			_aniControl = SLIDING;
			_curSliding = _x;
			if (_curRight == true)
			{
				_curSliding = _x;
				_maxSliding = _curSliding + 120;
			}
			else if (_curRight == false)
			{
				_curSliding = _x;
				_maxSliding = _curSliding - 120;
			}
		}
		else if(_pose != SLIDING && _pose != FLY && _curjumping == false && _pose != EXHALE) //점프
		{
			_pose = JUMPING;
			_playAni = true;
			_curjumping = true;
			_curJump = _y;
			_maxJump = _curJump - 200;
		}
		else if (_curjumping == true || _pose == FALLING || _pose == EXHALE)
		{
			_pose = FLY;
			_curjumping = false;
			_playAni = true;
		}
	}
	if (KEYMANAGER->isStayKeyDown('Z'))
	{
		if (_pose == FLY)
		{
			_y -= PLAYERSPEED + 1.5;
		}
	}
	if (KEYMANAGER->isOnceKeyUp('Z'))
	{
	}

	//x - 흡입, 뱉기
	if (KEYMANAGER->isOnceKeyDown('X'))
	{
		if (_pose == FLY)
		{
			_pose = EXHALE;
			_playAni = true;
		}
		else if(_pose != M_INHALE)
		{
			_pose = M_INHALE;
			_playAni = true;
		}
	}
	if (KEYMANAGER->isStayKeyDown('X'))
	{
	}
	if (KEYMANAGER->isOnceKeyUp('X'))
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
		if (_curRight == true) { _starFrame = 72; _endFrame = 72; }
		else { _starFrame = 90; _endFrame = 90; }
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
		if (_curRight == true) { _starFrame = 288; _endFrame = 291; }
		else { _starFrame = 306; _endFrame = 309; }
		break;
	case FLYMOVE:
		if (_curRight == true) { _starFrame = 288; _endFrame = 291; }
		else { _starFrame = 306; _endFrame = 309; }
		break;
	case INHALE:
		if (_curRight == true) { _starFrame = 288; _endFrame = 291; }
		else { _starFrame = 306; _endFrame = 309; }
		break;
	case EXHALE:
		if (_curRight == true) { _starFrame = 324; _endFrame = 325; }
		else { _starFrame = 342; _endFrame = 343; }
		if (_ani->isPlay() == false && _pose == EXHALE)
		{
			_pose = FALLING;
			_playAni = true;
		}
		break;
	case M_INHALE:
		if (_curRight == true) { _starFrame = 398; _endFrame = 400; }
		else { _starFrame = 416; _endFrame = 418; }
		break;
	case M_EXHALE:
		if (_curRight == true) { _starFrame = 288; _endFrame = 291; }
		else { _starFrame = 306; _endFrame = 309; }
		break;
	default:
		break;
	}
	if (_playAni == true && _pose != FALLING && _pose != EXHALE)
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
	moveCollision(objectPos);

	//플레이어 이미지 위치 업데이트
	//기본 커비일때 위치 초기화
	_imageX = _x - (_ani->getFrameWidth() / 2);
	_imageY = _y - (_ani->getFrameHeight() / 2) - 23;

}

void player::moveCollision(vector<fieldObject*> objectPos)
{
	RECT temp;

	_rc = RectMakeCenter(_x, _y, 50, 50);

	for (int i = 0; i < objectPos.size(); i++)
	{
		if (IntersectRect(&temp, &_rc, &objectPos[i]->getrc()))
		{

			//캐릭터 기준 위쪽 충돌
			if (_rc.left < objectPos[i]->getrc().right && _rc.right > objectPos[i]->getrc().left &&
				_rc.top > objectPos[i]->getrc().top && _rc.bottom > objectPos[i]->getrc().bottom)
			{
				//_y = objectPos[i]->getrc().top + 75;
				if (_pose == FLY)
				{
					_y += PLAYERSPEED + 1.5;
				}
				else
				{
					_pose = FALLING;
				}
				break;
			}
			//캐릭터 기준 아래쪽 충돌
			if (_rc.left < objectPos[i]->getrc().right && _rc.right > objectPos[i]->getrc().left &&
				_rc.top < objectPos[i]->getrc().top && _rc.bottom < objectPos[i]->getrc().bottom && !groundCollision)
			{
				_y = objectPos[i]->getrc().bottom - (objectPos[i]->getrc().bottom - objectPos[i]->getrc().top) - 25;
				groundCollision = false;
				if (_pose == FALLING || _pose == EXHALE)
				{
					_curjumping = false;
					_pose = LANDING;
					_playAni = true;
				}
				break;
			}
			//캐릭터 기준 왼쪽 충돌
			if (_rc.left > objectPos[i]->getrc().left && _rc.right > objectPos[i]->getrc().right &&
				_rc.top < objectPos[i]->getrc().bottom && _rc.bottom > objectPos[i]->getrc().top)
			{
				//_x += PLAYERSPEED;
				_x = objectPos[i]->getrc().left + (objectPos[i]->getrc().right - objectPos[i]->getrc().left) + 25;
				break;
			}
			//캐릭터 기준 오른쪽 충돌
			if (_rc.left < objectPos[i]->getrc().left && _rc.right < objectPos[i]->getrc().right &&
				_rc.top < objectPos[i]->getrc().bottom && _rc.bottom > objectPos[i]->getrc().top)
			{
				//_x -= PLAYERSPEED;
				_x = objectPos[i]->getrc().right - (objectPos[i]->getrc().right - objectPos[i]->getrc().left) - 25;
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

bool player::rightMove()
{
	bool _horizonMove = true;
	for (int i = _rc.right - 1; i < _rc.right + 1; i++)
	{
		COLORREF color = GetPixel(_pixelImage->getMemDC(), i, _y);

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
	for (int i = _rc.left + 1; i > _rc.left - 1; i--)
	{
		COLORREF color = GetPixel(_pixelImage->getMemDC(), i, _y);

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

