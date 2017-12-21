#pragma once
class fieldObject
{
protected:
	image* _image;
	int _appearMapNum;
	OBJECTDISCERN _discernNum;
	float _x, _y;
	RECT _rc;

	int _state; //0 나타남 1 삭제대기



	//플레이어 오브젝트 넘버

	int _objStarBox;	// Y 프레임 4번째위치 - 플레이어 흡수 상호작용 오브젝트
	int _objBoomBox;	// Y 프레임 0번째 위치 - 플레이어 공격 상호작용 오브젝트
	int _objStonBox;	// Y 프레임 6번째 위치 - 플레이어 흡수 상호작용 오브젝트 : 흡수시에 플레이어 쪽으로 끌려간다. 폭탄 오브젝트에 안터짐
	int _objIronBox;	// Y 프레임 1번째 위치 - 플레이어 공격에 안부서진다. 폭탄에 연쇄 반응으로 같이 소멸 
	int _objIronBox01;	// Y 프레임 2번째 위치 - 플레이어 공격에 안부서진다. 폭탄에 연쇄반응으로 같이 소멸
	int _objIronBox02;	//Y 프레임 5번째 위치 - 플레이어 공격에 안부서진다. 폭탄에 연쇄반응으로 같이 소멸
	int _objIronBox03;	// Y 프레임 3번째 위치 - 플레이어 공격에 안부서진다. 폭탄 연쇄반응으로 소멸 안됨.


public:
	HRESULT init(void);
	virtual HRESULT init(string,OBJECTDISCERN, int, POINT);
	void release(void);
	virtual void update(void);

	POINT getPos() { return PointMake(_x, _y); }
	RECT getrc() { return _rc; }
	OBJECTDISCERN getDiscernNum() { return _discernNum; }
	int getAppearMapNum() { return _appearMapNum; }
	int getState() { return _state; }

	void setState(int state) { _state = state; }


	image* getImage() { return _image; }

	//플레이어 오브젝트 넘버 겟
	int getObjStarBox() { return _objStarBox; }		  // Y 프레임 4번째위치 - 플레이어 흡수 상호작용 오브젝트
	int getObjBoomBox() { return _objBoomBox; }		  // Y 프레임 0번째 위치 - 플레이어 공격 상호작용 오브젝트
	int getObjStonBox() { return _objStonBox; }		  // Y 프레임 6번째 위치 - 플레이어 흡수 상호작용 오브젝트 : 흡수시에 플레이어 쪽으로 끌려간다. 폭탄 오브젝트에 안터짐
	int getObjIronBox() { return _objIronBox; }		  // Y 프레임 1번째 위치 - 플레이어 공격에 안부서진다. 폭탄에 연쇄 반응으로 같이 소멸 
	int getObjIronBox01() { return _objIronBox01; }	  // Y 프레임 2번째 위치 - 플레이어 공격에 안부서진다. 폭탄에 연쇄반응으로 같이 소멸
	int getObjIronBox02() { return _objIronBox02; }	  //Y 프레임 5번째 위치 - 플레이어 공격에 안부서진다. 폭탄에 연쇄반응으로 같이 소멸
	int getObjIronBox03() { return _objIronBox03; }	  // Y 프레임 3번째 위치 - 플레이어 공격에 안부서진다. 폭탄 연쇄반응으로 소멸 안됨.


	fieldObject() {}
	~fieldObject() {}
};

