#pragma once
#define speed 3.0f;
#include "bullet.h"

class fieldObject
{
protected:
	image* _image; // ������Ʈ�̹���

	int _appearMapNum;

	int _countBoom;

	OBJECTDISCERN _discernNum;
	float _x, _y;
	RECT _rc;
	RECT _boomCheck[4];

	int _state; //0 ��Ÿ�� 1 ������� 2 �����»���

	//�÷��̾���ǥ �޾ƿ���
	POINT _playerPoint;

	//�÷��̾� ���� ���� ��Ʈ �޾ƿ���! - ������Ʈ�� ��ȣ�ۿ�
	RECT _playerAttack;

	//�÷��̾� ���� �� �޾ƿ���! - ������Ʈ ��ȣ�ۿ�
	bool _curRight;

	//�÷��̾� ������Ʈ �ѹ�
	int _objNumberY;
	int _objNumberX;

	//���� ���ͼ�Ʈ��Ʈ�� ��Ʈ
	RECT _rcTemp;

public:
	virtual HRESULT init(string,OBJECTDISCERN, int, POINT);
	void release(void);
	virtual void update(POINT playerPosition, vector<bullet*> bulletPos);
	virtual void boomEffect();

	POINT getPos() { return PointMake(_x, _y); }
	RECT getrc() { return _rc; }
	OBJECTDISCERN getDiscernNum() { return _discernNum; }
	int getAppearMapNum() { return _appearMapNum; }
	int getState() { return _state; }

	void setState(int state) { _state = state; }

	void playerPos(POINT pos) { _playerPoint = pos; }

	image* getImage() { return _image; }
	

	//�÷��̾� ������Ʈ �ѹ� ��
	int getObjNumberY() { return _objNumberY; }
	int getObjNumberX() { return _objNumberX; }


	fieldObject() {}
	~fieldObject() {}
};

