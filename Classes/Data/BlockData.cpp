#include "BlockData.h"

const int KEY_NUM = 8;
const int TREASURE_NUM = 1;
const int BOMB_NUM = 8;
const int GOLD_NUM = 8;

const int NO_SIGN = -1;

const string PIT_IMG = "images/pit.png";
const float PIS_SIZE = 0.05f;

const string KEY_IMG = "images/key.png";
const float KEY_SIZE = 0.05f;

const string TREASURE_IMG = "images/treasure.png";
const float TREASURE_SIZE = 0.05f;

const string BOMB_IMG = "images/bomb.png";
const float BOMB_SIZE = 0.05f;

const string GOLD_IMG = "images/gold.png";
const float GOLD_SIZE = 0.05f;

const string EXPLODE_IMG = "images/explode.png";
const float EXPLODE_SIZE = 0.08f;

const char* KEY_EFFECT = "sounds/key.mp3";
const char* GOLD_EFFECT = "sounds/gold.mp3";
const char* DIG_EFFECT = "sounds/dig.mp3";
const char* EXPLODE_EFFECT = "sounds/bomb.mp3";

const int GOLD_PRICE = 1200;
const int BOMB_BASE_HURT = 6000;
const float HURT_INCREASE_COEFFICIENT = 3;
const int TREASURE_BASE_PRICE = 1500;
const float TREASURE_INCREASE_COEFFICIENT = 2;
