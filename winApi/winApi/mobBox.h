#pragma once
#include "fieldObject.h"
#include<math.h>

#define PI 3.141159265358979323
#define Speed 2.0f;

struct mobStruct
{
	float angle;	//각도
	float radius;	//반지름
	float _mobx;
	float _moby;
};

class mobBox :
	public fieldObject
{
private:
	mobStruct mobstruct;
	randomFunction* rand;
	//몹 오브젝트용 카운트 타이머
	int mobCount;
	float _mobTimer;
	float _mobWorldTimer;

	//총알 폭발
	int count;
	float _boomTimer;
	float _boomWorldTimer;

	//좌우이동
	int circleCount;
	float _circleTimer;
	float _circleWorldTimer;
	bool circleBool;

	//상하 이동
	int updownCount;
	float _updownTimer;
	float _updownWorldTimer;
	bool updownBool;

	int _rand;
public:

	HRESULT init(string objectName, OBJECTDISCERN discernNum, int mapNum, POINT pos);
	void update(POINT playerPosition, vector<bullet*> bulletPos);

	void move();
	void bulletEffect();
	void moving();
	void moving01();
	void moving2();
	void circle();

	mobBox(){}
	~mobBox(){}
};

