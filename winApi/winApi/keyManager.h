#pragma once
#include "singletonBase.h"

#define KEYMAX 256

class keyManager : public singletonBase<keyManager>
{
private:
	BOOL _keyUp[KEYMAX];
	BOOL _keyDown[KEYMAX];

public:
	//키매니져 초기화
	HRESULT init();

	//키가 한번만 눌렸는지
	bool isOnceKeyDown(int key);
	//누르고 띄었는지
	bool isOnceKeyUp(int key);
	//스테이 키
	bool isStayKeyDown(int key);
	//토글키
	bool isToggleKey(int key);

	keyManager() {}
	~keyManager() {}
};

