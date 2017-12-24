#pragma once
#include "enemy.h"
class brontoburt :
	public enemy
{
private:

	float _moveSpeed;

	POINT _rezen;

public:
	HRESULT init(string, ENEMYDISCERN, int, POINT);
	void update(image* pixelimage, POINT playerPoint);
	void Hit();

	brontoburt() {}
	~brontoburt() {}
};

