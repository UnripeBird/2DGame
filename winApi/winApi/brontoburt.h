#pragma once
#include "enemy.h"
class brontoburt :
	public enemy
{
private:

	float _moveSpeed;

	POINT _rezen;
	BOOL _sitdown;
public:
	HRESULT init(string, ENEMYDISCERN, int, POINT);
	void update(image* pixelimage, POINT playerPoint);
	void Hit();

	brontoburt() {}
	~brontoburt() {}
};

