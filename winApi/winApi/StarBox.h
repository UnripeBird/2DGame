#pragma once
#include "fieldObject.h"
class StarBox : public fieldObject
{
private:
	//폭발 이펙트때 사용
	int count;
	float _boomTimer;
	float _boomWorldTimer;

	//플레이어 방향체크
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

