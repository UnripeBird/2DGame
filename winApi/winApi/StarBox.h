#pragma once
#include "fieldObject.h"
class StarBox : public fieldObject
{
private:
	//���� ����Ʈ�� ���
	int count;
	float _boomTimer;
	float _boomWorldTimer;

	//�÷��̾� ����üũ
	bool _curRight;

	RECT rcTemp;

public:
	HRESULT init(string, OBJECTDISCERN, int, POINT);
	void update(POINT playerPosition, vector<bullet*> bulletPos);

	void move();
	void boomEffect();
	void bulletEffect();
	void starabso(POINT playerPos);

	StarBox() {}
	~StarBox() {}
};

