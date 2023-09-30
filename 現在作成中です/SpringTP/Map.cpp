#include "Map.h"

const VECTOR MapPos = VGet(0.0f, 0.0f, 50.0f);
const int LineNum = 100;
const float LineDis = 10.f;
const unsigned int color = GetColor(0, 255, 0);
const int AlphaBlendRatio = 75;
const float TowerHeght = 30.f;
const float TowerSize = 5.f;
const int TowerDivNum = 16;
const VECTOR TowerTop = { 0,100.f,0 };

Map::Map()
{
	pos = MapPos;
}

Map::~Map()
{
}

void Map::Draw()
{
	SetDrawBlendMode(DX_BLENDGRAPHTYPE_ALPHA, AlphaBlendRatio);
	for (int i = ZERO_I; i < LineNum; i++)
	{
		VECTOR lineStart, lineLast;
		lineStart = pos;
		lineLast = pos;
		lineStart.x -= LineNum * LineDis * HALF;
		lineLast.x += LineNum * LineDis * HALF;
		lineStart.z += i * LineDis - LineNum * LineDis * HALF;
		lineLast.z += i * LineDis - LineNum * LineDis * HALF;
		DrawLine3D(lineStart, lineLast, color);
	}
	for (int i = ZERO_I; i < LineNum; i++)
	{
		VECTOR lineStart, lineLast;
		lineStart = pos;
		lineLast = pos;
		lineStart.z -= LineNum * LineDis * HALF;
		lineLast.z += LineNum * LineDis * HALF;
		lineStart.x += i * LineDis - LineNum * LineDis * HALF;
		lineLast.x += i * LineDis - LineNum * LineDis * HALF;

		DrawLine3D(lineStart, lineLast, color);
	}

	SetDrawBlendMode(DX_BLENDGRAPHTYPE_ALPHA, AlphaBlendRatio * TWICE);

	DrawCapsule3D(ZERO_POS, TowerTop, TowerSize, TowerDivNum, color, color, true);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, ZERO_I);

}
