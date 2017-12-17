#include "stdafx.h"
#include "player.h"


HRESULT player::init(void)
{
	_x = 100;
	_y = 100;

	/* 파일출력 연습
	HANDLE file;
	char str[64] = "게임 잘 만들어 부자되라";
	DWORD write;

	file = CreateFile("너희가게임을아느냐.txt", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, str, strlen(str), &write, NULL);
	CloseHandle(file);
	*/

	return S_OK;
}

void player::release(void)
{
}

void player::update(vector<fieldObject*> objectPos, vector<enemy*> enemyPos)
{
	move(objectPos);
	objectCollision(objectPos);
	enemyCollision(enemyPos);
}

void player::move(vector<fieldObject*> objectPos)
{
	int direction = 0;
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_x += PLAYERSPEED;
		direction = 1;
		moveCollision(objectPos, direction);
	}

	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_x -= PLAYERSPEED;
		direction = 2;
		moveCollision(objectPos, direction);
	}

	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_y += PLAYERSPEED;
		direction = 3;
		moveCollision(objectPos, direction);
	}

	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_y -= PLAYERSPEED;
		direction = 4;
		moveCollision(objectPos, direction);
	}
}

void player::moveCollision(vector<fieldObject*> objectPos, int direction)
{
	RECT temp;

	_rc = RectMakeCenter(_x, _y, 50, 50);

	for (int i = 0; i < objectPos.size(); i++)
	{
		if (IntersectRect(&temp, &_rc, &objectPos[i]->getrc()))
		{
			switch (direction)
			{
				case 1:
					_x = objectPos[i]->getrc().left - 25;
					break;
				case 2:
					_x = objectPos[i]->getrc().right + 25;
					break;
				case 3:
					_y = objectPos[i]->getrc().top - 25;
					break;
				case 4:
					_y = objectPos[i]->getrc().bottom + 25;
					break;
			}
		}
	}
}

bool player::objectCollision(vector<fieldObject*> objectPos)
{
	RECT temp;

	bool collision = false;

	_rc = RectMakeCenter(_x, _y, 50, 50);

	for (int i = 0; i < objectPos.size(); i++)
	{
		if (IntersectRect(&temp, &_rc, &objectPos[i]->getrc()))
		{
			objectCollisionReaction(objectPos, i);
			collision = true;
		}
	}

	return collision;
}

void player::objectCollisionReaction(vector<fieldObject*> objectPos, int collisionNum)
{
	switch (objectPos[collisionNum]->getDiscernNum())
	{
		case box:
			break;
	}
}

bool player::enemyCollision(vector<enemy*> enemyPos)
{
	RECT temp;

	bool collision = false;
	
	_rc = RectMakeCenter(_x, _y, 50, 50);

	for (int i = 0; i < enemyPos.size(); i++)
	{
		if (IntersectRect(&temp, &_rc, &enemyPos[i]->getrc()))
		{
			enemyCollisionReaction(enemyPos, i);
			collision = true;
		}
	}

	return collision;
}

void player::enemyCollisionReaction(vector<enemy*> enemyPos, int collisionNum)
{
	switch (enemyPos[collisionNum]->getDiscernNum())
	{
		case enemyBox:
			enemyPos[collisionNum]->setState(2);
			break;
	}
}
