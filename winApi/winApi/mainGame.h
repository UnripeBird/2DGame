#pragma once
#include "gameNode.h"

class mainGame : public gameNode
{
private:

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(float);

	mainGame() {}
	~mainGame() {}
};

