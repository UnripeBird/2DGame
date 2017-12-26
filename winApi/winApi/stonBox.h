#pragma once
#include "fieldObject.h"
class stonBox :
	public fieldObject
{
private:
	//좌표 초기값
	int box_x;

	//좌우판단
	bool curRight;

	//흡수할때 사용
	float _absoTimer;
	float _absoWorldTimer;
	int _absoCount;

	//흔들리는 효과 카운트
	int countR;
	int countL;

	int count;
	float _boomTimer;
	float _boomWorldTimer;


public:
	HRESULT init(string objectName, OBJECTDISCERN discernNum, int mapNum, POINT pos);
	void update(POINT playerPosition, vector<bullet*> bulletPos);

	void move();
	void absorption(POINT playerPoint); // 플레이어 흡수에 끌리는 오브젝트
	void bulletEffect();

	stonBox(){}
	~stonBox(){}
};

