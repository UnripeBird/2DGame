#pragma once
#include "gameNode.h"

class NumberSample : public gameNode
{
private:

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	NumberSample() {};
	~NumberSample() {};
};

