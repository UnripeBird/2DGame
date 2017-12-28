#pragma once
#include "enemy.h"
class waddle :
	public enemy
{
private:

	float _moveSpeed;

	POINT _rezen;

public:
	HRESULT init(string, ENEMYDISCERN, int, POINT);
	void update(image* pixelimage, POINT playerPoint, vector<fieldObject*> objectVec, vector<bullet*> bulletVec, bulletManager* BulletManager);
	void Hit();
	void moveright();
	void moveleft();

	void hitright();
	void hitleft();
	void Eating(POINT playerpoint);
	void death(vector<bullet*> bulletVec);
	waddle() {}
	~waddle() {}
};

