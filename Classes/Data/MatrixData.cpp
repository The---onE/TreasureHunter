#include "MatrixData.h"

const float BLOCK_WIDTH = 80;
const float BLOCK_HEIGHT = 80;

const int BLOCK_NUM = MATRIX_LINE * MATRIX_ROW;

const Point MATRIX_CENTER = visibleSize / 2;
const float MATRIX_LEFT = MATRIX_CENTER.x - BLOCK_WIDTH*(float(MATRIX_ROW) / 2);
const float MATRIX_RIGHT = MATRIX_CENTER.x + BLOCK_WIDTH*(float(MATRIX_ROW) / 2);
const float MATRIX_BOTTOM = MATRIX_CENTER.y - BLOCK_HEIGHT*(float(MATRIX_LINE) / 2);
const float MATRIX_TOP = MATRIX_CENTER.y + BLOCK_HEIGHT*(float(MATRIX_LINE) / 2);

const Point MATRIX_BOTTOM_LEFT = Point(MATRIX_LEFT, MATRIX_BOTTOM);
const Point MATRIX_BOTTOM_LEFT_CENTER = MATRIX_BOTTOM_LEFT + Point(BLOCK_WIDTH / 2, BLOCK_HEIGHT / 2);
const Point MATRIX_TOP_RIGHT = Point(MATRIX_RIGHT, MATRIX_TOP);
const Point MATRIX_TOP_RIGHT_CENTER = MATRIX_TOP_RIGHT - Point(BLOCK_WIDTH / 2, BLOCK_HEIGHT / 2);

const Rect MATRIX_RECT = Rect(MATRIX_BOTTOM_LEFT.x, MATRIX_BOTTOM_LEFT.y, BLOCK_WIDTH*MATRIX_ROW, BLOCK_HEIGHT*MATRIX_LINE);

const string MATRIX_SIGN_IMG = "images/sign.png";
const float MATRIX_SIGN_SIZE = 0.05f;

const float GUIDELINE_WIDTH = 2.5f;
const Color4F GUIDELINE_COLOR = Color4F(0, 255, 0, 0.25f);


Point getCenterByCoord(int line, int row)
{
	Point center = MATRIX_BOTTOM_LEFT_CENTER;
	center += Point(BLOCK_WIDTH*row, BLOCK_HEIGHT*line);
	return center;
}
Point getCenterByCoord(Coord c)
{
	Point center = MATRIX_BOTTOM_LEFT_CENTER;
	center += Point(BLOCK_WIDTH*c.row, BLOCK_HEIGHT*c.line);
	return center;
}