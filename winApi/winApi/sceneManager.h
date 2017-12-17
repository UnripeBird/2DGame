#pragma once
#include "singletonBase.h"

class gameNode;

class sceneManager : public singletonBase <sceneManager>
{
public:
	typedef map<string, gameNode*> mapSceneList;
	typedef map<string, gameNode*>::iterator mapSceneIter;

private:
	static gameNode* _currentScene;		//현재 씬
	static gameNode* _loadingScene;		//로딩 씬
	static gameNode* _readyScene;		//교체 대기중인 씬

	mapSceneList _mSceneList;			//씬 리스트
	mapSceneList _mLoadingSceneList;	//로딩 씬 리스트

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	//씬 추가
	gameNode* addScene(string sceneName, gameNode* scene);
	gameNode* addLoadingScene(string loadingSceneName, gameNode* scene);

	//씬 체인지
	HRESULT changeScene(string sceneName);

	//로딩 쓰레드 함수
	friend DWORD CALLBACK loadingThread(LPVOID prc);

	sceneManager() {}
	~sceneManager() {}
};

