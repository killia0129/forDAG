#include "ResultScoreUI.h"
#include "DxLib.h"
#include <string>

ResultScoreUI::ResultScoreUI(Pos position)
	: font(0)
	, score(0)
	, position()
{
	font = CreateFontToHandle("Impact", 100, 0, DX_FONTTYPE_ANTIALIASING_EDGE);
	this->position = position;
}

ResultScoreUI::~ResultScoreUI()
{
}

void ResultScoreUI::Initialize(int score)
{
	this->score = score;
}

void ResultScoreUI::Draw()
{
	DrawStringToHandle(position.x-550, position.y-200, ("Record : " + std::to_string(score) + " Km").c_str(), GetColor(0, 0, 0), font);
}