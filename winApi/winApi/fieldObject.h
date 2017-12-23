#pragma once
class fieldObject
{
protected:
	image* _image; // ������Ʈ�̹���
	image* _boomImage;// �����̹���

	int _appearMapNum;

	int _countBoom;

	OBJECTDISCERN _discernNum;
	float _x, _y;
	RECT _rc;
	RECT _boomCheck[4];

	int _state; //0 ��Ÿ�� 1 ������� 2 �����»���

	//�÷��̾���ǥ �޾ƿ���
	POINT _playerPoint;

	//�÷��̾� ������Ʈ �ѹ�

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
	

	//�÷��̾� ������Ʈ �ѹ� ��
	int getObjNumberY() { return _objNumberY; }
	int getObjNumberX() { return _objNumberX; }


	fieldObject() {}
	~fieldObject() {}
};

