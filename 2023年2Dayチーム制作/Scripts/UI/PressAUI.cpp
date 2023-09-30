#include "PressAUI.h"
#include "DxLib.h"
#include <math.h>

PressAUI::PressAUI(const char* fileNameTitle, const char* fileNameResult, Pos position)
	: graphHandle()
	, alpha(255)
	, alphaCount(0.0f)
	, position()
	, size()
	, isTitleUI(true)
{
	graphHandle[0] = LoadGraph(fileNameTitle);
	graphHandle[1] = LoadGraph(fileNameResult);
	this->position = position;
	GetGraphSize(graphHandle[0], &size[0].w, &size[0].h);
	GetGraphSize(graphHandle[1], &size[1].w, &size[1].h);
}

PressAUI::~PressAUI()
{
	DeleteGraph(graphHandle[0]);
	DeleteGraph(graphHandle[1]);
}

void PressAUI::Initialize(bool isTitleUI)
{
	alpha = 255;
	alphaCount = 0.0f;
	this->isTitleUI = isTitleUI;
}

void PressAUI::Update(float deltaTime)
{
	alphaCount += deltaTime*5.0f;
	alpha = (cosf(alphaCount) * 255.0f + 510.0f) / 4.0f;
}

void PressAUI::Draw()
{
	int index = isTitleUI ? 0 : 1;
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	DrawGraph(position.x - size[index].w / 2, position.y - size[index].h / 2, graphHandle[index], TRUE);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}