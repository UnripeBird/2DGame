#pragma once
#include "enemy.h"
class spark : public enemy
{
private:

	float _moveSpeed;
	int attackarr[28] = { 45,46,45,46,45,46,45,46,47,48,49,50,51,47,48,52,53,47,48,54,55,47,48,56,57,47,48,58 };
	POINT _rezen;

public:
	HRESULT init(string, ENEMYDISCERN, int, POINT);
	void update(image* pixelimage, POINT playerPoint, vector<fieldObject*> objectVec, vector<bullet*> bulletVec, bulletManager* BulletManager);
	void Hit();
	void Eating(POINT playerpoint);

	void rightmove();
	void leftmove();
	void attackmove();
	void hitmoveleft();
	void hitmoveright();
	void death(vector<bullet*> bulletVec);
	spark() {}
	~spark() {}
};

