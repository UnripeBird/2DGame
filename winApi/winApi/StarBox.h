#pragma once
#include "fieldObject.h"
class StarBox : public fieldObject
{
private:
	int _mapState;
	bool _Loop;
	//폭발 이펙트때 사용
	int count;
	float _boomTimer;
	float _boomWorldTimer;


	//불릿 폭발 이펙트때 사용
	int bullectCount;
	float _bullectTimer;
	float _bullectWorldTimer;

	//플레이어 방향체크
	bool _curRight;

	RECT rcTemp;

public:
	HRESULT init(string, OBJECTDISCERN, int, POINT);
	void update(POINT playerPosition, vector<bullet*> bulletPos);

	void move();
	void boomEffect();			//폭탄 연쇄 반응으로 터지는 이펙트
	void boomEffectBullet();	//커비 브레스 공격으로 터지는 이펙트
	void bulletEffect();		//커비 브레스 사라지는 이펙트

	void absorption(POINT);

	StarBox() {}
	~StarBox() {}
};

