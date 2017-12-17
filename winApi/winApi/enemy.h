#pragma once
class enemy
{
protected:
	image* _image;
	int _appearMapNum;
	ENEMYDISCERN _discernNum;
	float _x, _y;
	RECT _rc;

	int _state; //0 ���� 1 ������� 2 �������

public:
	HRESULT init(void);
	virtual HRESULT init(string, ENEMYDISCERN, int, POINT);
	void release(void);
	virtual void update(void);

	POINT getPos() { return PointMake(_x, _y); }
	RECT getrc() { return _rc; }
	ENEMYDISCERN getDiscernNum() { return _discernNum; }
	int getAppearMapNum() { return _appearMapNum; }
	int getState() { return _state; }

	void setState(int state) { _state = state; }

	enemy() {}
	~enemy() {}
};

