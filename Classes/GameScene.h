
#pragma once

#include "Global.h"
#include "State/StateMachine.h"
#include "Interface/Interface.h"
#include "User/User.h"

class GameScene : public Scene
{
protected:
	BackgroundLayer* background; //背景层
	MatrixLayer* matrix; //矩阵层
	InformationLayer* information; //信息层
	PropLayer* prop; //道具层
	InteractiveLayer* interactive; //交互层

	Players* players; //玩家信息

	int gameMoney; //该局游戏收益

	void clearSelect(); //清除用户选择的道具和格子

	void showInformation(); //显示游戏信息
	void showPrice(); //显示使用道具价格
	void showRest(); //显示矩阵中物品剩余数量

	void moneyNotEnough(); //金钱不足道具价格时的提示

	void restart(Ref* pSender); //开始新游戏

	void createQuitButton(string normal, string selected); //创建退出游戏按钮
	void quitGame(Ref* pSender); //退出游戏

public:
	CREATE_FUNC(GameScene);
	bool init();

	void initBackground(); //初始化背景层
	void initMatrix(); //初始化矩阵层
	void initInformation(); //初始化信息层
	void initProp(); //初始化道具层
	void initInteractive(); //初始化交互层

	void initData(); //初始化用户数据
	void initPlayers(); //初始化玩家信息
	void initLead(); //初始化操控者

	void randBlocks(); //随机在矩阵中生成物品

	void gameOver(); //游戏结束时的提示

	int checkOk(); //检查并响应按下确定按钮
	void checkCancel(); //检查并响应按下取消按钮

	//测试时使用的后门
	//////////////////////////////////////////////////////////////////////////
	void checkShow(); //检查并响应按下全部显示按钮
	void checkHide(); //检查并响应按下全部隐藏按钮
	//////////////////////////////////////////////////////////////////////////

public:
	StateMachine* stateMachine; //状态机
	StateMachine* getStateMachine(); //返回状态机指针
	void update(float dt);
};

