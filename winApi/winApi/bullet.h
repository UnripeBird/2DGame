#pragma once
class bullet
{
protected:
	image* _image;
	BULLETDISCERN _discernNum;
	float _startX, _startY;
	float _x, _y;
	float _range;
	RECT _rc;

	int _frameX;
	int _frameY;

	float _frameTimer;
	float _frameWorldTimer;

	bool _fireLeftRight;
	int _speed;

	float _angle;

	int _state; //0 생존 1 삭제모션 2 삭제대기

public:
	HRESULT init(void);
	virtual HRESULT init(BULLETDISCERN, POINT, bool, float angle = -1);
	void release(void);
	virtual void update(void);

	POINT getPos() { return PointMake(_x, _y); }
	RECT getrc() { return _rc; }
	BULLETDISCERN getDiscernNum() { return _discernNum; }
	int getState() { return _state; }

	image* getImage() { return _image; }
	POINT getImageFrame() { return PointMake(_frameX,_frameY); }

	void setState(int state) { _state = state; }

	bullet() {}
	~bullet() {}
};

