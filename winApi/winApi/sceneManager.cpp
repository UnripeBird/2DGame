#include "stdafx.h"
#include "sceneManager.h"
#include "gameNode.h"

//로딩 쓰레드 함수
DWORD CALLBACK loadingThread(LPVOID prc)
{
	//교체될 씬의 함수를 실행
	sceneManager::_readyScene->init();

	//현재 씬을 교체될 씬으로 바꾼다
	sceneManager::_currentScene = sceneManager::_readyScene;

	//로딩 씬 해제
	sceneManager::_loadingScene->release();
	sceneManager::_loadingScene = NULL;
	sceneManager::_readyScene = NULL;

	return 0;
}

gameNode* sceneManager::_currentScene = NULL;
gameNode* sceneManager::_loadingScene = NULL;
gameNode* sceneManager::_readyScene = NULL;

HRESULT sceneManager::init(void)
{
	_currentScene = NULL;
	_loadingScene = NULL;
	_readyScene = NULL;

	return S_OK;
}

void sceneManager::release(void)
{
	//맵 전체를 돌면서 지운다
	mapSceneIter miSceneList = _mSceneList.begin();

	for (; miSceneList != _mSceneList.end();)
	{
		if (miSceneList->second != NULL)
		{
			if (miSceneList->second == _currentScene)
			{
				miSceneList->second->release();
			}

			SAFE_DELETE(miSceneList->second);
			miSceneList = _mSceneList.erase(miSceneList);
		}

		else
		{
			++miSceneList;
		}
	}
	_mSceneList.clear();
}

void sceneManager::update(void)
{
	//현재 씬이 존재한다면 현재 씬만 업데이트
	if (_currentScene) _currentScene->update();
}

void sceneManager::render(void)
{
	if (_currentScene) _currentScene->render();
}

//씬 추가
gameNode * sceneManager::addScene(string sceneName, gameNode * scene)
{
	//씬이 없다면 NULL 리턴
	if (!scene) return NULL;

	_mSceneList.insert(make_pair(sceneName, scene));
	return scene;
}

//로딩씬 추가
gameNode * sceneManager::addLoadingScene(string loadingSceneName, gameNode * scene)
{
	if (!scene) return NULL;

	_mLoadingSceneList.insert(make_pair(loadingSceneName, scene));
	return scene;
}

//씬 체인지
HRESULT sceneManager::changeScene(string sceneName)
{
	//바꾸려고 하는 씬을 찾는다
	mapSceneIter find = _mSceneList.find(sceneName);

	//바꾸지 못하면 E_FAIL 리턴
	if (find == _mSceneList.end()) return E_FAIL;

	//바꾸려 하는 씬과 현재씬이 같으면 S_OK 리턴
	if (find->second == _currentScene) return S_OK;

	//새롭게 변경되는 씬 초기화
	if (SUCCEEDED(find->second->init()))
	{
		_currentScene = find->second;

		return S_OK;
	}
	return E_FAIL;
}

