#include "PropData.h"

const string SCAN_IMG = "images/scan.png";
const Point SCAN_POSITION = Point(WIDTH*0.25f, HEIGHT*0.15f);
const float SCAN_SIZE = 0.08f;

const string DIG_IMG = "images/dig.png";
const Point DIG_POSITION = Point(WIDTH*0.5f, HEIGHT*0.15f);
const float DIG_SIZE = 0.08f;

const string DETECT_IMG = "images/detect.png";
const Point DETECT_POSITION = Point(WIDTH*0.75f, HEIGHT*0.15f);
const float DETECT_SIZE = 0.08f;

const string PROP_SIGN_IMG = "images/sign.png";
const float PROP_SIGN_SIZE = 0.085f;

const int SCAN_BASE_PRICE = 125;
const float SCAN_INCREASE_COEFFICIENT = 1.5f;

const int DIG_BASE_PRICE = 90;
const float DIG_INCREASE_COEFFICIENT = 1.35f;

const int DETECT_BASE_PRICE = 160;
const float DETECT_INCREASE_COEFFICIENT = 1.6f;

const float SCAN_ANIMATE_TIME = 2.0f;
const string SCAN_ANIMATE_IMG = "images/scan_animate.png";
const float SCAN_ANIMATE_SIZE = 0.21f;

const float DETECT_ANIMATE_TIME = 2.0f;
const string DETECT_ANIMATE_IMG = "images/detect_animate.png";
const float DETECT_ANIMATE_SIZE = 0.21f;

const int DIG_VIBRATE_TIME = 50;
const int EXPLODE_VIBRATE_TIME = 300;

const int SCAN_VIBRATE_TIME = 50;
const int DETECT_VIBRATE_TIME = 50;

const float SHOW_ITEM_TIME = 0.6f;
const float SHOW_DIG_TIME = 1.8f;

const float EXPLODE_TIME = 2.5f;

const string COUNT_FONT = GLOBAL_FONT;
const int COUNT_FONTSIZE = 100;
const float COUNT_SIZE = 0.06f;

const int KEY_COUNT_R = 0;
const int KEY_COUNT_G = 255;
const int KEY_COUNT_B = 0;
const int KEY_COUNT_A = 255;
const float SCAN_STAND_TIME = 3.0f;

const int BOMB_COUNT_R = 255;
const int BOMB_COUNT_G = 0;
const int BOMB_COUNT_B = 0;
const int BOMB_COUNT_A = 255;
const float DETECT_STAND_TIME = 3.0f;

const char* SCAN_EFFECT = "sounds/scan.mp3";
const char* DETECT_EFFECT = "sounds/detect.mp3";
