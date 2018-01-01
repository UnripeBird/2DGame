#pragma once
#include "animation.h"
#include "fieldObject.h"
#include "bulletManager.h"
#include "bullet.h"

enum direction
{
	drright,
	drleft
	

};

class enemy
{
protected:
	image* _image;
	int _appearMapNum;
	ENEMYDISCERN _discernNum;
	animation* _ani;

	float _x, _y;
	int _framex;
	int _framey;
	//타임매니저 사용 
	
	float _frameTimer;
	float _frameWorldTimer;
	RECT _rc;
	RECT _rctemp;
	BOOL _hitCount;
	BOOL _moveselect;
	BOOL _collisioncheck;
	BOOL _anicheck;
	BOOL _attactmotion;
	BOOL _burningselect;
	BOOL _eating;
	BOOL _atkreset;
	BOOL _rectcheck;
	float _hitTimer;
	float _hitWorldTimer;
	float _gravity;

	int _triangle;
	float _attacktimer;
	float _missileTimer;
	direction _dr;
	int _hp;

	int _state; //0 드랍상태 1 행동상태 2 삭제대기 3 빨려가기

	//보스 공격
	bullet* _bullet;
public:
	HRESULT init(void);
	virtual HRESULT init(string, ENEMYDISCERN, int, POINT);
	void release(void);
	virtual void update(image* pixelimage, POINT playerPoint, vector<fieldObject*> objectVec, vector<bullet*> bulletVec, bulletManager* BulletManager);
	void pixelcollision(image * pixelimage, vector<fieldObject*> objectVec);
	void brontocollision(image * pixelimage, vector<fieldObject*> objectVec);
	
	virtual void Hit() = 0;
	virtual void Eating(POINT playerpoint) = 0;
	
	animation* getAni() { return _ani; }
	POINT getPos() { return PointMake(_x, _y); }
	RECT getrc() { return _rc; }

	int gethp() { return _hp; }

	ENEMYDISCERN getDiscernNum() { return _discernNum; }
	int getAppearMapNum() { return _appearMapNum; }
	int getState() { return _state; }
	image* getimage() { return _image; }
	int getframex() { return _framex; }
	int getframey() { return _framey; }
	void setState(int state) { _state = state; }
	BOOL getatkmotion() { return _attactmotion; }
	enemy() {}
	~enemy() {}
};

