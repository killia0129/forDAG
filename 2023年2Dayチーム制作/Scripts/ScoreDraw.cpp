#include "DxLib.h"
#include "ScoreDraw.h"
#include "Common.h"

ScoreDraw::ScoreDraw()
{
	fontHandle = CreateFontToHandle("impact", 100, 7, DX_FONTTYPE_NORMAL);
}

ScoreDraw::~ScoreDraw()
{
	// èàóùÇ»Çµ
}

void ScoreDraw::Initialize()
{
	score = 0;
}

void ScoreDraw::Update()
{
	score += 120;
}

void ScoreDraw::Draw()
{
	DrawFormatStringToHandle(SCREEN_WIDTH - 520, 0, GetColor(0., 0, 0), fontHandle, "%8.1f ", score);
	DrawStringToHandle(SCREEN_WIDTH - 130, 0, "km", GetColor(0, 0, 0), fontHandle);
}