#include "stdafx.h"
#include "mainGame.h"
#include "playScene.h"
#include "titleScene.h"

//=========================
//	## init(void) ## 초기화
//=========================
HRESULT mainGame::init(void)
{
	gameNode::init(TRUE);
	//이곳에서 초기화

	SCENEMANAGER->addScene("title", new titleScene);
	SCENEMANAGER->addScene("play", new playScene);

	SCENEMANAGER->changeScene("title");
	return S_OK;
}

//=====================
//	## release(void) ##
//=====================
void mainGame::release(void)
{
	gameNode::release();

	//동적할당을 했다면 여기에서 SAFE_DELETE() 사용
}

//=============================
//	## update(void) ## 업데이트
//=============================
void mainGame::update(void)
{
	gameNode::update();

	SCENEMANAGER->update();

	//이곳에서 계산식, 키보드, 마우스등등 업데이트를 한다
}

//============================
//	## render(HDC hdc) ## 렌더
//============================

void mainGame::render(float setfps)
{
	//검은색 빈 비트맵 (이것도 렌더에 그대로 둘것)
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
	//=============================================================

	SCENEMANAGER->render();

	TIMEMANAGER->render(getMemDC());

	//=============================================================
	//백버퍼의 내용을 HDC에 그린다
	this->getBackBuffer()->render(getHDC());
}
