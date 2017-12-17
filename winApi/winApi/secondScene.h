#pragma once
#include "gameNode.h"
#include "jumpSample.h"
#include "NumberSample.h"

class secondScene : public gameNode
{
private:
	jumpSample* _jump;
	NumberSample* _number;

	//루프용 변수
	//x
	int _offsetX;
	//y
	int _offsetY;
	//루프될 배경의 이동속도(x)
	int _bgSpeed;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	secondScene(){}
	~secondScene(){}
};

