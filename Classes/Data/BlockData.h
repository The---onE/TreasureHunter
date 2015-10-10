#pragma once

#include "Global.h"

const int ERROR_ITEM = -100;
const int PIT = -1;
const int NO_ITEM = 0;
const int KEY = 1;
const int TREASURE = 2;
const int BOMB = 3;
const int GOLD = 4;

extern const int KEY_NUM;
extern const int TREASURE_NUM;
extern const int BOMB_NUM;
extern const int GOLD_NUM;

extern const int NO_SIGN;

extern const string PIT_IMG;
extern const float PIS_SIZE;
extern const string KEY_IMG;
extern const float KEY_SIZE;
extern const string TREASURE_IMG;
extern const float TREASURE_SIZE;
extern const string BOMB_IMG;
extern const float BOMB_SIZE;
extern const string GOLD_IMG;
extern const float GOLD_SIZE;

extern const string EXPLODE_IMG;
extern const float EXPLODE_SIZE;

extern const char* KEY_EFFECT;
extern const char* GOLD_EFFECT;
extern const char* DIG_EFFECT;
extern const char* EXPLODE_EFFECT;

extern const int GOLD_PRICE;
extern const int BOMB_BASE_HURT;
extern const float HURT_INCREASE_COEFFICIENT;
extern const int TREASURE_BASE_PRICE;
extern const float TREASURE_INCREASE_COEFFICIENT;