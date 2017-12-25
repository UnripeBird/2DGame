#pragma once
#include "enemy.h"
class chilly :
	public enemy
{
private:

	float _moveSpeed;
	int attackarr[16] = {24,25,26,27,24,25,26,27,28,29,30,31,28,29,30,31 };

	POINT _rezen;

public:
	HRESULT init(string, ENEMYDISCERN, int, POINT);
	void update(image* pixelimage, POINT playerPoint);
	void Hit();

	void chillymove();

	void attackmove();
	void hitmoveleft();
	void hitmoveright();

	chilly() {}
	~chilly() {}
};

