#pragma once
class fieldObject
{
protected:
	image* _image;
	int _appearMapNum;
	OBJECTDISCERN _discernNum;
	float _x, _y;
	RECT _rc;

	int _state; //0 ��Ÿ�� 1 �������



	//�÷��̾� ������Ʈ �ѹ�

	int _objStarBox;	// Y ������ 4��°��ġ - �÷��̾� ��� ��ȣ�ۿ� ������Ʈ
	int _objBoomBox;	// Y ������ 0��° ��ġ - �÷��̾� ���� ��ȣ�ۿ� ������Ʈ
	int _objStonBox;	// Y ������ 6��° ��ġ - �÷��̾� ��� ��ȣ�ۿ� ������Ʈ : ����ÿ� �÷��̾� ������ ��������. ��ź ������Ʈ�� ������
	int _objIronBox;	// Y ������ 1��° ��ġ - �÷��̾� ���ݿ� �Ⱥμ�����. ��ź�� ���� �������� ���� �Ҹ� 
	int _objIronBox01;	// Y ������ 2��° ��ġ - �÷��̾� ���ݿ� �Ⱥμ�����. ��ź�� ����������� ���� �Ҹ�
	int _objIronBox02;	//Y ������ 5��° ��ġ - �÷��̾� ���ݿ� �Ⱥμ�����. ��ź�� ����������� ���� �Ҹ�
	int _objIronBox03;	// Y ������ 3��° ��ġ - �÷��̾� ���ݿ� �Ⱥμ�����. ��ź ����������� �Ҹ� �ȵ�.


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

	//�÷��̾� ������Ʈ �ѹ� ��
	int getObjStarBox() { return _objStarBox; }		  // Y ������ 4��°��ġ - �÷��̾� ��� ��ȣ�ۿ� ������Ʈ
	int getObjBoomBox() { return _objBoomBox; }		  // Y ������ 0��° ��ġ - �÷��̾� ���� ��ȣ�ۿ� ������Ʈ
	int getObjStonBox() { return _objStonBox; }		  // Y ������ 6��° ��ġ - �÷��̾� ��� ��ȣ�ۿ� ������Ʈ : ����ÿ� �÷��̾� ������ ��������. ��ź ������Ʈ�� ������
	int getObjIronBox() { return _objIronBox; }		  // Y ������ 1��° ��ġ - �÷��̾� ���ݿ� �Ⱥμ�����. ��ź�� ���� �������� ���� �Ҹ� 
	int getObjIronBox01() { return _objIronBox01; }	  // Y ������ 2��° ��ġ - �÷��̾� ���ݿ� �Ⱥμ�����. ��ź�� ����������� ���� �Ҹ�
	int getObjIronBox02() { return _objIronBox02; }	  //Y ������ 5��° ��ġ - �÷��̾� ���ݿ� �Ⱥμ�����. ��ź�� ����������� ���� �Ҹ�
	int getObjIronBox03() { return _objIronBox03; }	  // Y ������ 3��° ��ġ - �÷��̾� ���ݿ� �Ⱥμ�����. ��ź ����������� �Ҹ� �ȵ�.


	fieldObject() {}
	~fieldObject() {}
};

