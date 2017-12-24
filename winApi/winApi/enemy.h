#pragma once

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
	float _x, _y;
	int _framex;
	int _framey;
	//타임매니저 사용 
	
	float _frameTimer;
	float _frameWorldTimer;
	RECT _rc;

	BOOL _hitCount;
	float _hitTimer;
	float _hitWorldTimer;


	direction _dr;
	int _state; //0 생존 1 삭제모션 2 삭제대기

public:
	HRESULT init(void);
	virtual HRESULT init(string, ENEMYDISCERN, int, POINT);
	void release(void);
	virtual void update(image* pixelimage, POINT playerPoint);


	virtual void Hit() = 0;

	POINT getPos() { return PointMake(_x, _y); }
	RECT getrc() { return _rc; }
	ENEMYDISCERN getDiscernNum() { return _discernNum; }
	int getAppearMapNum() { return _appearMapNum; }
	int getState() { return _state; }
	image* getimage() { return _image; }
	int getframex() { return _framex; }
	int getframey() { return _framey; }
	void setState(int state) { _state = state; }

	enemy() {}
	~enemy() {}
};

