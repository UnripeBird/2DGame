#pragma once
#include "enemy.h"

class woodboss :
	public enemy
{
private:

	float _moveSpeed;

	POINT _rezen;

public:
	HRESULT init(string, ENEMYDISCERN, int, POINT);
	void update(image* pixelimage, POINT playerPoint, vector<fieldObject*> objectVec, vector<bullet*> bulletVec);
	void Hit();


	void face();

	void attackmoveleft();
	void attackmoveright();
	void hitmove();
	woodboss() {}
	~woodboss() {}
};

