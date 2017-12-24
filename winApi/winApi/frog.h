#pragma once
#include "enemy.h"
class frog :
	public enemy
{
private:

	float _moveSpeed;

	POINT _rezen;

public:
	HRESULT init(string, ENEMYDISCERN, int, POINT);
	void update(void);
	void Hit();
	frog() {}
	~frog() {}
};

