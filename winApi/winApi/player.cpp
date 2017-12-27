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
	//벽 충돌
	FLY, //날기 대기상태
	FLYMOVE, //날기 무빙상태
	INHALE,	//공기 들이 마심
	EXHALE, //공기 내쉼
	FAIL_INHALE,//흡입 실패
	//막 흡입했을때
	M_INHALE, //몹 흡입
	M_EXHALE, //몹 뱉기
	M_SWALLOW,//삼키기, 변신
	//M_IDLE,//흡입 상태 기본
	M_WALK,//흡입 상태 걷기
	M_JUMP,//흡입 상태 점프
	COLLISION,//충돌
	DIE,//죽음
	ATTACK//변신 커비 공격
};

enum INHALE_KIND
{
	KIRBY,
	BURNING,
	FREEZE,
	SPARK
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
	_inhaleKind = KIRBY;
	_curInhale = false;

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
	move(objectPos, BulletManager);
	objectCollision(objectPos);
	enemyCollision(enemyPos);
	_ani->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
	
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		BulletManager->bulletFire(Star, PointMake(_x, _y), !_curRight);
	}

	if (_pose == LANDING)
	{
		_pose = IDLE;
		_playAni = true;
	}

	//애니메이션이 정지 했을때
	if (_pose == SWALLOW && _ani->isPlay() == false && _curInhale == true)
	{
		if (_inhaleKind == BURNING)
		{
			_curInhale = false;
			_pose = IDLE;
			_playAni = true;
			_ani->setFPS(8);
			_fileNum = 1;
		}
		_image = IMAGEMANAGER->findImage(_fileName[_fileNum]);
		_ani->init(_image->getWidth(), _image->getHeight(), _image->getFrameWidth(), _image->getFrameHeight());
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

void player::move(vector<fieldObject*> objectPos, bulletManager* BulletManager)
{
	int direction = 0;
	DublleKeyWorldTimer = TIMEMANAGER->getWorldTime();

	//오른쪽
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		if (_pose != SWALLOW && _pose == IDLE)
		{
			if (_curInhale == true)
			{
				_pose = WALK;
			}
			else
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
		}
		_curRight = true;
		_playAni = true;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && _pose != SWALLOW)
	{
		if (_pose == WALK && rightMove() && !objectRightMove(objectPos))
		{
			_x += PLAYERSPEED;
		}
		else if (_pose == RUN && rightMove() && !objectRightMove(objectPos))
		{
			_x += PLAYERSPEED * 1.5;
			_keyDownNum = 0;
		}
		else if (_pose == JUMPING && rightMove() && !objectRightMove(objectPos) || _pose == FLY && rightMove() && !objectRightMove(objectPos))
		{
			_x += PLAYERSPEED;
			_curRight = true;
		}
		else if (_pose == FALLING && rightMove() && !objectRightMove(objectPos))
		{
			_x += PLAYERSPEED;
			_curRight = true;
		}
		RECT temp;

		_rc = RectMakeCenter(_x, _y, 50, 50);
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
			if (_curInhale == true)
			{
				_pose = WALK;
			}
			else
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
		}
		_curRight = false;
		_playAni = true;
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && _pose != SWALLOW)
	{
		if (_pose == WALK && leftMove() && !objectLeftMove(objectPos))
		{
			_x -= PLAYERSPEED;
		}
		else if (_pose == RUN && leftMove() && !objectLeftMove(objectPos))
		{
			_x -= PLAYERSPEED * 1.5;
			_keyDownNum = 0;
		}
		else if (_pose == JUMPING && leftMove() && !objectLeftMove(objectPos) || _pose == FLY && leftMove() && !objectLeftMove(objectPos))
		{
			_x -= PLAYERSPEED;
			_curRight = false;
		}
		else if (_pose == FALLING && leftMove() && !objectLeftMove(objectPos))
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
		cout << _pose << endl;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_DOWN) && _pose == SWALLOW)
	{
		if (_curInhale == false)
		{
			_pose = IDLE;
			_playAni = true;
			_curSwallow = false;
		}
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
		if (_pose == SWALLOW  && _curInhale == false) //슬라이딩
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
		if (_pose == FLY && !objectTopMove(objectPos))
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
		if (_pose == FLY)// 공기 뱉기
		{
			BulletManager->bulletFire(Breath, PointMake(_x, _y), !_curRight);
			_pose = EXHALE;
			_playAni = true;
		}
		else if(_pose != M_INHALE && _inhaleKind == KIRBY)//몬스터 흡입, 기본 커비일때만 가능
		{
			_pose = M_INHALE;
			_playAni = true;
		}
	}
	if (KEYMANAGER->isStayKeyDown('X'))
	{
		if (_inhaleKind == KIRBY) //기본 커비시에만 흡입 모션, 다른 모션으로 흡입시에 이미지 초기화가 다르기 때문에 터짐
		{
			RECT temp;
			RECT rc_inhale;
			if (_curRight == true)
			{
				rc_inhale.left = _x;
				rc_inhale.right = _x + 100;
				rc_inhale.top = _y - 40;
				rc_inhale.bottom = _y + 20;
			}
			else
			{
				rc_inhale.left = _x - 100;
				rc_inhale.right = _x;
				rc_inhale.top = _y - 40;
				rc_inhale.bottom = _y + 20;
			}
			for (int i = 0; i < objectPos.size(); i++)
			{
				//흡입 할 때 지워지는 것들
				if (IntersectRect(&temp, &rc_inhale, &objectPos[i]->getrc()) && _pose == M_INHALE && _curInhale == false)
				{
					objectPos[i]->absorption(PointMake(_x, _y));
					//흡입 도중 플레이어와 부딪혔을 때
					if (IntersectRect(&temp, &_rc, &objectPos[i]->getrc()))
					{
						if (objectPos[i]->getDiscernNum() == starbox ||
							objectPos[i]->getDiscernNum() == upItem ||
							objectPos[i]->getDiscernNum() == candyitem ||
							objectPos[i]->getDiscernNum() == maxtem ||
							objectPos[i]->getDiscernNum() == meat ||
							objectPos[i]->getDiscernNum() == drink ||
							objectPos[i]->getDiscernNum() == cherry)
						{
							//입에 담고 있어야하는 것들
							//if ()
							//{
							//
							//}
							_pose = IDLE;
							_playAni = true;
							_curInhale = true;
							//_inhaleKind = OBJECT;
							objectPos[i]->setState(4);

						}

						if (objectPos[i]->getDiscernNum() == starbox)
						{
							_inhaleKind = BURNING;
						}
					}
				}
			}
		}
	}
	if (KEYMANAGER->isOnceKeyUp('X'))
	{
		if (_pose == M_INHALE && _curInhale == false)
		{
			_pose = IDLE;
			_playAni = true;
		}
	}

	if (KEYMANAGER->isOnceKeyDown(VK_BACK))
	{

	}

	//애니메이션
	switch (_pose)
	{
	case IDLE:
		if (_curInhale == false)
		{
			if (_curRight == true && _inhaleKind == KIRBY) { _starFrame = 0; _endFrame = 0; }
			else if (_curRight == false && _inhaleKind == KIRBY) { _starFrame = 18; _endFrame = 18; }

			if (_curRight == true && _inhaleKind == BURNING) { _starFrame = 0; _endFrame = 3; }
			else if (_curRight == false && _inhaleKind == BURNING) { _starFrame = 24; _endFrame = 26; }

			if (_curRight == true && _inhaleKind == FREEZE) { _starFrame = 0; _endFrame = 0; }
			else if (_curRight == false && _inhaleKind == FREEZE) { _starFrame = 18; _endFrame = 18; }

			if (_curRight == true && _inhaleKind == SPARK) { _starFrame = 0; _endFrame = 0; }
			else if (_curRight == false && _inhaleKind == SPARK) { _starFrame = 18; _endFrame = 18; }
		}
		else if (_curInhale == true)
		{
			if (_curRight == true) { _starFrame = 540; _endFrame = 540; }
			else if (_curRight == false) { _starFrame = 558; _endFrame = 558; }
		}
		break;
	case WALK:
		if (_curInhale == false)
		{
			if (_curRight == true && _inhaleKind == KIRBY) { _starFrame = 144; _endFrame = 153; }
			else if (_curRight == false && _inhaleKind == KIRBY) { _starFrame = 162; _endFrame = 171; }

			if (_curRight == true && _inhaleKind == BURNING) { _starFrame = 184; _endFrame = 203; }
			else if (_curRight == false && _inhaleKind == BURNING) { _starFrame = 207; _endFrame = 226; }

			if (_curRight == true && _inhaleKind == FREEZE) { _starFrame = 0; _endFrame = 0; }
			else if (_curRight == false && _inhaleKind == FREEZE) { _starFrame = 18; _endFrame = 18; }

			if (_curRight == true && _inhaleKind == SPARK) { _starFrame = 0; _endFrame = 0; }
			else if (_curRight == false && _inhaleKind == SPARK) { _starFrame = 18; _endFrame = 18; }
		}
		else if (_curInhale == true)
		{
			if (_curRight == true) { _starFrame = 612; _endFrame = 627; }
			else if (_curRight == false) { _starFrame = 630; _endFrame = 645; }
		}
		break;
	case RUN:
		if (_curRight == true && _inhaleKind == KIRBY) { _starFrame = 180; _endFrame = 187; }
		else if (_curRight == false && _inhaleKind == KIRBY) { _starFrame = 198; _endFrame = 205; }

		if (_curRight == true && _inhaleKind == BURNING) { _starFrame = 230; _endFrame = 237; }
		else if (_curRight == false && _inhaleKind == BURNING) { _starFrame = 253; _endFrame = 260; }

		if (_curRight == true && _inhaleKind == FREEZE) { _starFrame = 0; _endFrame = 0; }
		else if (_curRight == false && _inhaleKind == FREEZE) { _starFrame = 18; _endFrame = 18; }

		if (_curRight == true && _inhaleKind == SPARK) { _starFrame = 0; _endFrame = 0; }
		else if (_curRight == false && _inhaleKind == SPARK) { _starFrame = 18; _endFrame = 18; }
		break;
	case SWALLOW:
		if (_curInhale == false)
		{
			if (_curRight == true && _inhaleKind == KIRBY) { _starFrame = 36; _endFrame = 36; }
			else if (_curRight == false && _inhaleKind == KIRBY) { _starFrame = 54; _endFrame = 54; }

			if (_curRight == true && _inhaleKind == BURNING) { _starFrame = 46; _endFrame = 49; }
			else if (_curRight == false && _inhaleKind == BURNING) { _starFrame = 69; _endFrame = 72; }

			if (_curRight == true && _inhaleKind == FREEZE) { _starFrame = 0; _endFrame = 0; }
			else if (_curRight == false && _inhaleKind == FREEZE) { _starFrame = 18; _endFrame = 18; }

			if (_curRight == true && _inhaleKind == SPARK) { _starFrame = 0; _endFrame = 0; }
			else if (_curRight == false && _inhaleKind == SPARK) { _starFrame = 18; _endFrame = 18; }
		}
		else if (_curInhale == true)
		{
			if (_curRight == true) { _starFrame = 504; _endFrame = 512; }
			else { _starFrame = 522; _endFrame = 530; }
		}
		break;
	case SLIDING:
		if (_curRight == true && _inhaleKind == KIRBY) { _starFrame = 72; _endFrame = 72; }
		else if (_curRight == false && _inhaleKind == KIRBY) { _starFrame = 90; _endFrame = 90; }

		if (_curRight == true && _inhaleKind == BURNING) { _starFrame = 92; _endFrame = 95; }
		else if (_curRight == false && _inhaleKind == BURNING) { _starFrame = 115; _endFrame = 118; }

		if (_curRight == true && _inhaleKind == FREEZE) { _starFrame = 0; _endFrame = 0; }
		else if (_curRight == false && _inhaleKind == FREEZE) { _starFrame = 18; _endFrame = 18; }

		if (_curRight == true && _inhaleKind == SPARK) { _starFrame = 0; _endFrame = 0; }
		else if (_curRight == false && _inhaleKind == SPARK) { _starFrame = 18; _endFrame = 18; }
		break;
	case JUMPING:
		if (_curInhale == false)
		{
			if (_curRight == true && _inhaleKind == KIRBY) { _starFrame = 108; _endFrame = 108; }
			else if (_curRight == false && _inhaleKind == KIRBY) { _starFrame = 126; _endFrame = 126; }

			if (_curRight == true && _inhaleKind == BURNING) { _starFrame = 138; _endFrame = 139; }
			else if (_curRight == false && _inhaleKind == BURNING) { _starFrame = 161; _endFrame = 162; }

			if (_curRight == true && _inhaleKind == FREEZE) { _starFrame = 0; _endFrame = 0; }
			else if (_curRight == false && _inhaleKind == FREEZE) { _starFrame = 18; _endFrame = 18; }

			if (_curRight == true && _inhaleKind == SPARK) { _starFrame = 0; _endFrame = 0; }
			else if (_curRight == false && _inhaleKind == SPARK) { _starFrame = 18; _endFrame = 18; }
		}
		else if (_curInhale == true)
		{
			if (_curRight == true) { _starFrame = 576; _endFrame = 578; }
			else if (_curRight == false) { _starFrame = 594; _endFrame = 596; }
		}
		break;
	case FALLING:
		if (_curRight == true && _inhaleKind == KIRBY) { _starFrame = 109; _endFrame = 116; }
		else if (_curRight == false && _inhaleKind == KIRBY) { _starFrame = 127; _endFrame = 134; }

		if (_curRight == true && _inhaleKind == BURNING) { _starFrame = 140; _endFrame = 147; }
		else if (_curRight == false && _inhaleKind == BURNING) { _starFrame = 163; _endFrame = 170; }

		if (_curRight == true && _inhaleKind == FREEZE) { _starFrame = 0; _endFrame = 0; }
		else if (_curRight == false && _inhaleKind == FREEZE) { _starFrame = 18; _endFrame = 18; }

		if (_curRight == true && _inhaleKind == SPARK) { _starFrame = 0; _endFrame = 0; }
		else if (_curRight == false && _inhaleKind == SPARK) { _starFrame = 18; _endFrame = 18; }
		break;
	case LANDING:
		if (_curRight == true && _inhaleKind == KIRBY) { _starFrame = 117; _endFrame = 117; }
		else if (_curRight == false && _inhaleKind == KIRBY) { _starFrame = 135; _endFrame = 135; }

		if (_curRight == true && _inhaleKind == BURNING) { _starFrame = 148; _endFrame = 148; }
		else if (_curRight == false && _inhaleKind == BURNING) { _starFrame = 171; _endFrame = 171; }

		if (_curRight == true && _inhaleKind == FREEZE) { _starFrame = 0; _endFrame = 0; }
		else if (_curRight == false && _inhaleKind == FREEZE) { _starFrame = 18; _endFrame = 18; }

		if (_curRight == true && _inhaleKind == SPARK) { _starFrame = 0; _endFrame = 0; }
		else if (_curRight == false && _inhaleKind == SPARK) { _starFrame = 18; _endFrame = 18; }

		break;
	case FLY:
		if (_curRight == true && _inhaleKind == KIRBY) { _starFrame = 288; _endFrame = 291; }
		else if (_curRight == false && _inhaleKind == KIRBY) { _starFrame = 306; _endFrame = 309; }

		if (_curRight == true && _inhaleKind == BURNING) { _starFrame = 368; _endFrame = 373; }
		else if (_curRight == false && _inhaleKind == BURNING) { _starFrame = 391; _endFrame = 396; }

		if (_curRight == true && _inhaleKind == FREEZE) { _starFrame = 0; _endFrame = 0; }
		else if (_curRight == false && _inhaleKind == FREEZE) { _starFrame = 18; _endFrame = 18; }

		if (_curRight == true && _inhaleKind == SPARK) { _starFrame = 0; _endFrame = 0; }
		else if (_curRight == false && _inhaleKind == SPARK) { _starFrame = 18; _endFrame = 18; }

		break;
	case FLYMOVE:
		if (_curRight == true && _inhaleKind == KIRBY) { _starFrame = 288; _endFrame = 291; }
		else if (_curRight == false && _inhaleKind == KIRBY) { _starFrame = 306; _endFrame = 309; }

		if (_curRight == true && _inhaleKind == BURNING) { _starFrame = 368; _endFrame = 373; }
		else if (_curRight == false && _inhaleKind == BURNING) { _starFrame = 391; _endFrame = 396; }

		if (_curRight == true && _inhaleKind == FREEZE) { _starFrame = 0; _endFrame = 0; }
		else if (_curRight == false && _inhaleKind == FREEZE) { _starFrame = 18; _endFrame = 18; }

		if (_curRight == true && _inhaleKind == SPARK) { _starFrame = 0; _endFrame = 0; }
		else if (_curRight == false && _inhaleKind == SPARK) { _starFrame = 18; _endFrame = 18; }

		break;
	case INHALE:
		if (_curRight == true && _inhaleKind == KIRBY) { _starFrame = 288; _endFrame = 291; }
		else if (_curRight == false && _inhaleKind == KIRBY) { _starFrame = 306; _endFrame = 309; }

		if (_curRight == true && _inhaleKind == BURNING) { _starFrame = 278; _endFrame = 280; }
		else if (_curRight == false && _inhaleKind == BURNING) { _starFrame = 301; _endFrame = 303; }

		if (_curRight == true && _inhaleKind == FREEZE) { _starFrame = 0; _endFrame = 0; }
		else if (_curRight == false && _inhaleKind == FREEZE) { _starFrame = 18; _endFrame = 18; }

		if (_curRight == true && _inhaleKind == SPARK) { _starFrame = 0; _endFrame = 0; }
		else if (_curRight == false && _inhaleKind == SPARK) { _starFrame = 18; _endFrame = 18; }
		
		break;
	case EXHALE:
		if (_curRight == true && _inhaleKind == KIRBY) { _starFrame = 324; _endFrame = 325; }
		else if (_curRight == false && _inhaleKind == KIRBY) { _starFrame = 342; _endFrame = 343; }

		if (_curRight == true && _inhaleKind == BURNING) { _starFrame = 0; _endFrame = 3; }
		else if (_curRight == false && _inhaleKind == BURNING) { _starFrame = 18; _endFrame = 18; }

		if (_curRight == true && _inhaleKind == FREEZE) { _starFrame = 0; _endFrame = 0; }
		else if (_curRight == false && _inhaleKind == FREEZE) { _starFrame = 18; _endFrame = 18; }

		if (_curRight == true && _inhaleKind == SPARK) { _starFrame = 0; _endFrame = 0; }
		else if (_curRight == false && _inhaleKind == SPARK) { _starFrame = 18; _endFrame = 18; }
		if (_ani->isPlay() == false && _pose == EXHALE)
		{
			_pose = FALLING;
			_playAni = true;
		}
		break;
	case M_INHALE:
		if (_curRight == true) { _starFrame = 399; _endFrame = 400; }
		else { _starFrame = 417; _endFrame = 418; }
		break;
	case M_EXHALE:
		if (_curRight == true) { _starFrame = 288; _endFrame = 291; }
		else { _starFrame = 306; _endFrame = 309; }
		break;
	default:
		break;
	}
	if (_playAni == true && _pose != FALLING && _pose != EXHALE && _curInhale == false)
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
	if (_inhaleKind == KIRBY || _curInhale == true)
	{
		_imageX = _x - (_ani->getFrameWidth() / 2);
		_imageY = _y - (_ani->getFrameHeight() / 2) - 23;
	}
	else if (_inhaleKind == BURNING)
	{
		_imageX = _x - (_ani->getFrameWidth() / 2);
		_imageY = _y - (_ani->getFrameHeight() / 2) + 23;
	}
}

void player::moveCollision(vector<fieldObject*> objectPos)
{
	RECT temp;

	_rc = RectMakeCenter(_x, _y, 50, 50);

	for (int i = 0; i < objectPos.size(); i++)
	{
		if (IntersectRect(&temp, &_rc, &objectPos[i]->getrc()))
		{
			//부딪힐 때 지워지는 것들
			if (objectPos[i]->getDiscernNum() == upItem ||
				objectPos[i]->getDiscernNum() == candyitem ||
				objectPos[i]->getDiscernNum() == maxtem ||
				objectPos[i]->getDiscernNum() == meat ||
				objectPos[i]->getDiscernNum() == drink ||
				objectPos[i]->getDiscernNum() == cherry)
			{
				objectPos[i]->setState(4);
			}
			//캐릭터 기준 위쪽 충돌
			if (_rc.left < objectPos[i]->getrc().right && _rc.right > objectPos[i]->getrc().left &&
				_rc.top > objectPos[i]->getrc().top && _rc.bottom > objectPos[i]->getrc().bottom)
			{
				if(_pose == JUMPING)
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

bool player::objectRightMove(vector<fieldObject*> objectPos)
{
	bool collision;
	collision = false;
	RECT temp;

	for (int i = 0; i < objectPos.size(); i++)
	{
		if (IntersectRect(&temp, &_rc, &objectPos[i]->getrc()))
		{
			//캐릭터 기준 오른쪽 충돌
			if (_rc.left < objectPos[i]->getrc().left && _rc.right < objectPos[i]->getrc().right &&
				_rc.top < objectPos[i]->getrc().bottom && _rc.bottom > objectPos[i]->getrc().top)
			{
				_x = objectPos[i]->getrc().right - (objectPos[i]->getrc().right - objectPos[i]->getrc().left) - 25;
				return true;
				break;
			}
		}
	}

	return collision;
}

bool player::objectLeftMove(vector<fieldObject*> objectPos)
{
	bool collision;
	collision = false;
	RECT temp;

	for (int i = 0; i < objectPos.size(); i++)
	{
		if (IntersectRect(&temp, &_rc, &objectPos[i]->getrc()))
		{
			//캐릭터 기준 왼쪽 충돌
			if (_rc.left > objectPos[i]->getrc().left && _rc.right > objectPos[i]->getrc().right &&
				_rc.top < objectPos[i]->getrc().bottom && _rc.bottom > objectPos[i]->getrc().top)
			{
				_x = objectPos[i]->getrc().left + (objectPos[i]->getrc().right - objectPos[i]->getrc().left) + 25;
				return true;
				break;
			}
		}
	}

	return collision;
}

bool player::objectTopMove(vector<fieldObject*> objectPos)
{
	bool collision;
	collision = false;
	RECT temp;

	for (int i = 0; i < objectPos.size(); i++)
	{
		//캐릭터 기준 위쪽 충돌
		if (_rc.left < objectPos[i]->getrc().right && _rc.right > objectPos[i]->getrc().left &&
			_rc.top < objectPos[i]->getrc().bottom && _rc.bottom > objectPos[i]->getrc().top)
		{
			return true;
			break;
		}
	}

	return collision;
}
