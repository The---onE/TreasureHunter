
#pragma once

#include "Global.h"
#include "State/StateMachine.h"
#include "Interface/Interface.h"
#include "User/User.h"

class GameScene : public Scene
{
protected:
	BackgroundLayer* background; //������
	MatrixLayer* matrix; //�����
	InformationLayer* information; //��Ϣ��
	PropLayer* prop; //���߲�
	InteractiveLayer* interactive; //������

	Players* players; //�����Ϣ

	int gameMoney; //�þ���Ϸ����

	void clearSelect(); //����û�ѡ��ĵ��ߺ͸���

	void showInformation(); //��ʾ��Ϸ��Ϣ
	void showPrice(); //��ʾʹ�õ��߼۸�
	void showRest(); //��ʾ��������Ʒʣ������

	void moneyNotEnough(); //��Ǯ������߼۸�ʱ����ʾ

	void restart(Ref* pSender); //��ʼ����Ϸ

	void createQuitButton(string normal, string selected); //�����˳���Ϸ��ť
	void quitGame(Ref* pSender); //�˳���Ϸ

public:
	CREATE_FUNC(GameScene);
	bool init();

	void initBackground(); //��ʼ��������
	void initMatrix(); //��ʼ�������
	void initInformation(); //��ʼ����Ϣ��
	void initProp(); //��ʼ�����߲�
	void initInteractive(); //��ʼ��������

	void initData(); //��ʼ���û�����
	void initPlayers(); //��ʼ�������Ϣ
	void initLead(); //��ʼ���ٿ���

	void randBlocks(); //����ھ�����������Ʒ

	void gameOver(); //��Ϸ����ʱ����ʾ

	int checkOk(); //��鲢��Ӧ����ȷ����ť
	void checkCancel(); //��鲢��Ӧ����ȡ����ť

	//����ʱʹ�õĺ���
	//////////////////////////////////////////////////////////////////////////
	void checkShow(); //��鲢��Ӧ����ȫ����ʾ��ť
	void checkHide(); //��鲢��Ӧ����ȫ�����ذ�ť
	//////////////////////////////////////////////////////////////////////////

public:
	StateMachine* stateMachine; //״̬��
	StateMachine* getStateMachine(); //����״̬��ָ��
	void update(float dt);
};

