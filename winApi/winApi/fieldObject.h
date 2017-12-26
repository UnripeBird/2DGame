#pragma once
#define speed 3.0f;
#include "bullet.h"

class fieldObject
{
protected:
	image* _image; // ������Ʈ�̹���
	image* _effectImage;// ����Ʈ �̹���

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
	bool _effectBullet;

	//�÷��̾� ������Ʈ �ѹ�
	int _objNumberY;
	int _objNumberX;

	//����Ʈ ������Ʈ �ѹ�
	int _effectNumberX;
	int _effectNumberY;

	//���� ���ͼ�Ʈ��Ʈ�� ��Ʈ
	RECT _rcTemp;
	//�Ѿ� �浹����Ʈ�� ��Ʈ
	RECT _bulletRc;


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

	//����Ʈ�� �߰�
	image* getEffect() { return _effectImage; }
	RECT getrcTemp() { return _rcTemp; }
	int getEffectNumberY() { return _effectNumberY; }
	int getEffectNumberX() { return _effectNumberX; }
	bool getbulletEffect() { return _effectBullet; }

	fieldObject() {}
	~fieldObject() {}
};

