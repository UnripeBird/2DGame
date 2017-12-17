#pragma once
#include "enemy.h"
class boxEnemy : public enemy
{
private:
	float _boxSpeed;
	float _acceleration;

public:
	HRESULT init(string, ENEMYDISCERN, int, POINT);
	void update(void);

	boxEnemy() {}
	~boxEnemy() {}
};

