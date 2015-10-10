#pragma once

#include "Global.h"

const int NO_PROP = 0;
const int SCAN = 1;
const int DIG = 2;
const int DETECT = 3;

extern const string SCAN_IMG;
extern const Point SCAN_POSITION;
extern const float SCAN_SIZE;

extern const string DIG_IMG;
extern const Point DIG_POSITION;
extern const float DIG_SIZE;

extern const string DETECT_IMG;
extern const Point DETECT_POSITION;
extern const float DETECT_SIZE;

extern const string PROP_SIGN_IMG;
extern const float PROP_SIGN_SIZE;

extern const int SCAN_BASE_PRICE;
extern const float SCAN_INCREASE_COEFFICIENT;

extern const int DIG_BASE_PRICE;
extern const float DIG_INCREASE_COEFFICIENT;

extern const int DETECT_BASE_PRICE;
extern const float DETECT_INCREASE_COEFFICIENT;

extern const float SCAN_ANIMATE_TIME;
extern const string SCAN_ANIMATE_IMG;
extern const float SCAN_ANIMATE_SIZE;

extern const float DETECT_ANIMATE_TIME;
extern const string DETECT_ANIMATE_IMG;
extern const float DETECT_ANIMATE_SIZE;

extern const int DIG_VIBRATE_TIME;
extern const int EXPLODE_VIBRATE_TIME;

extern const int SCAN_VIBRATE_TIME;
extern const int DETECT_VIBRATE_TIME;

extern const float SHOW_ITEM_TIME;
extern const float SHOW_DIG_TIME;

extern const float EXPLODE_TIME;

extern const string COUNT_FONT;
extern const int COUNT_FONTSIZE;
extern const float COUNT_SIZE;

extern const int KEY_COUNT_R;
extern const int KEY_COUNT_G;
extern const int KEY_COUNT_B;
extern const int KEY_COUNT_A;
extern const float SCAN_STAND_TIME;

extern const int BOMB_COUNT_R;
extern const int BOMB_COUNT_G;
extern const int BOMB_COUNT_B;
extern const int BOMB_COUNT_A;
extern const float DETECT_STAND_TIME;

extern const char* SCAN_EFFECT;
extern const char* DETECT_EFFECT;