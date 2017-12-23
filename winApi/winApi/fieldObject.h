#pragma once
class fieldObject
{
protected:
	image* _image; // 오브젝트이미지
	image* _boomImage;// 폭발이미지

	int _appearMapNum;

	int _countBoom;

	OBJECTDISCERN _discernNum;
	float _x, _y;
	RECT _rc;
	RECT _boomCheck[4];

	int _state; //0 나타남 1 삭제대기 2 터지는상태

	//플레이어좌표 받아오자
	POINT _playerPoint;

	//플레이어 오브젝트 넘버

	int _objNumberY;
	int _objNumberX;


public:
	virtual HRESULT init(string,OBJECTDISCERN, int, POINT);
	void release(void);
	virtual void update(void);
	virtual void boomEffect();

	POINT getPos() { return PointMake(_x, _y); }
	RECT getrc() { return _rc; }
	OBJECTDISCERN getDiscernNum() { return _discernNum; }
	int getAppearMapNum() { return _appearMapNum; }
	int getState() { return _state; }

	void setState(int state) { _state = state; }

	void playerPos(POINT pos) { _playerPoint = pos; }

	image* getImage() { return _image; }
	image* getBoomImage() { return _boomImage; }
	

	//플레이어 오브젝트 넘버 겟
	int getObjNumberY() { return _objNumberY; }
	int getObjNumberX() { return _objNumberX; }


	fieldObject() {}
	~fieldObject() {}
};

