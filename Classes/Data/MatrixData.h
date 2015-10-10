#pragma once

#include "Global.h"

const int MATRIX_LINE = 7;
const int MATRIX_ROW = 7;

extern const int BLOCK_NUM;

extern const float BLOCK_WIDTH;
extern const float BLOCK_HEIGHT;

extern const Point MATRIX_CENTER;
extern const float MATRIX_LEFT;
extern const float MATRIX_RIGHT;
extern const float MATRIX_BOTTOM;
extern const float MATRIX_TOP;

extern const Point MATRIX_BOTTOM_LEFT_CENTER;
extern const Point MATRIX_BOTTOM_LEFT;
extern const Point MATRIX_TOP_RIGHT_CENTER;
extern const Point MATRIX_TOP_RIGHT;


extern const Rect MATRIX_RECT;

extern const string MATRIX_SIGN_IMG;
extern const float MATRIX_SIGN_SIZE;

extern const float GUIDELINE_WIDTH;
extern const Color4F GUIDELINE_COLOR;


Point getCenterByCoord(int line, int row);
Point getCenterByCoord(Coord c);

#define ERGODIC_BLOCK(line, row) for(int (line)=0; (line)<MATRIX_LINE; ++(line)) for(int (row)=0; (row)<MATRIX_ROW; ++(row))