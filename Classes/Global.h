#pragma once

#include "cocos2d.h"
USING_NS_CC;

using namespace std; //使用string等标准库内容

#include "Custom/Vibrator.h" //震动器
using namespace Custom; //震动器定义在自定义命名空间中

//使用cocos studio制作的文件
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
using namespace ui;

//使用音乐音效引擎
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

const int WIDTH = 720; //屏幕宽度
const int HEIGHT = 1280; //屏幕高度

const Size visibleSize = Size(WIDTH, HEIGHT);  //屏幕尺寸

const float DATUM = HEIGHT; //长度基准
const float DEFAULT_WIDTH = WIDTH; //默认屏幕宽度
const float PARAM = (DATUM / DEFAULT_WIDTH); //速度标准化参数

const string GLOBAL_FONT = "fonts/ConeyIsland.ttf"; //全局常用字体

void setSize(Node* s, float size); //通过图片目标高度与长度基准比例缩放图片

int randNum(int size, int probability[]); //通过存放对应概率的数组获取随机数

int stdStoI(string s); //字符串转整型数
string stdItoS(int x); //整型数转字符串
float stdStoF(string s); //字符串转浮点数
string stdFtoS(float x); //浮点数转字符串

void addSprite(Sprite* & s, string img, Point pos, float size, Node* n, int zOrder = 0); //将Sprite添加到父节点中

//坐标结构体
class Coord
{
public:
	int line, row;
};

//键盘控制
/*#define KEYBOARD_FUNCTION void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);\
void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

#define KEYBOARD_LISTENER(CLASS) EventListenerKeyboard* keyboardListener = EventListenerKeyboard::create();\
keyboardListener->onKeyPressed = CC_CALLBACK_2(CLASS::onKeyPressed, this); \
keyboardListener->onKeyReleased = CC_CALLBACK_2(CLASS::onKeyReleased, this); \
Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);*/
