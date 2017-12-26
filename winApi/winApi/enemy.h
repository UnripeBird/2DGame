#pragma once
#include "animation.h"
#include "fieldObject.h"
#include "bullet.h"

enum direction
{
	drright,
	drleft,


};
enum burningdr
{
	bup,
	bdown,
	bright,
	bleft
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
	
	BOOL _hitCount;
	BOOL _moveselect;
	BOOL _collisioncheck;
	BOOL _anicheck;
	BOOL _attactmotion;
	BOOL _burningselect;
	
	
	float _hitTimer;
	float _hitWorldTimer;
	float _gravity;
	RECT _probe[4];
	
	direction _dr;
	burningdr _bdr;
	int _state; //0 드랍상태 1 행동상태 2 삭제대기

public:
	HRESULT init(void);
	virtual HRESULT init(string, ENEMYDISCERN, int, POINT);
	void release(void);
	virtual void update(image* pixelimage, POINT playerPoint, vector<fieldObject*> objectVec, vector<bullet*> bulletVec);
	void pixelcollision();
	void brontocollision();
	void burningcollision(vector<fieldObject*> objectVec);
	virtual void Hit() = 0;

	animation* getAni() { return _ani; }
	POINT getPos() { return PointMake(_x, _y); }
	RECT getrc() { return _rc; }
	RECT getprobex(int x) { return _probe[x]; }


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

