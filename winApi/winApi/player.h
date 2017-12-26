#pragma once
#include "fieldObject.h"
#include "enemy.h"
#include "animation.h"
#include "bulletManager.h"

#define PLAYERSPEED 2.5
#define FILENUM 4

class player
{
private:
	float _x;
	float _y;
	float _imageX;
	float _imageY;
	int _curJump; //점프를 어느정도 높이로 뛰는가
	int _maxJump;
	int _curSliding;
	int _maxSliding;
	int _gravity;
	int _life;
	int _curHp;
	int _maxHp;

	int _starFrame, _endFrame;

	string _fileName[FILENUM];
	int _fileNum;
	int _pose;
	int _aniControl;
	int _keyDownNum;
	bool _curRight;
	bool _playAni;
	bool _curSwallow;
	bool _curjumping; //점핑 상태인가
	bool groundCollision;

	float DubbleKeyTimer;
	float DublleKeyWorldTimer;

	image* _image;
	animation* _ani;
	RECT _rc;

	image* _pixelImage;
public:
	HRESULT init(void);
	void release(void);
	void update(vector<fieldObject*>, vector<enemy*>, image*, bulletManager*);

	void move(vector<fieldObject*>);
	void moveCollision(vector<fieldObject*>);

	bool objectCollision(vector<fieldObject*>);
	void objectCollisionReaction(vector<fieldObject*>, int);

	bool enemyCollision(vector<enemy*>);
	void enemyCollisionReaction(vector<enemy*>, int);

	bool rightMove();
	bool leftMove();

	POINT getPos() { return PointMake(_x, _y); }
	POINT getImagePos() { return PointMake(_imageX, _imageY); }

	int getLife() { return _life; }
	int getCurHp() { return _curHp; }
	int getMaxHP() { return _maxHp; }

	image* getImage() { return _image; }
	animation* getAni() { return _ani; }

	player() {}
	~player() {}
};

