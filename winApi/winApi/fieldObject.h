#pragma once
class fieldObject
{
protected:
	image* _image;
	int _appearMapNum;
	OBJECTDISCERN _discernNum;
	float _x, _y;
	RECT _rc;

	int _state; //0 나타남 1 삭제대기

public:
	HRESULT init(void);
	virtual HRESULT init(string,OBJECTDISCERN, int, POINT);
	void release(void);
	virtual void update(void);

	POINT getPos() { return PointMake(_x, _y); }
	RECT getrc() { return _rc; }
	OBJECTDISCERN getDiscernNum() { return _discernNum; }
	int getAppearMapNum() { return _appearMapNum; }
	int getState() { return _state; }

	void setState(int state) { _state = state; }

	fieldObject() {}
	~fieldObject() {}
};

