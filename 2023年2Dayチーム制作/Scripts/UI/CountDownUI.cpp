#include "CountDownUI.h"
#include "DxLib.h"

CountDownUI::CountDownUI(Pos position)
	: graphHandles()
	, index(0)
	, position()
	, size()
	, isDraw(false)
	, isCall()
{
	graphHandles[0] = LoadGraph("Textures/Number/3.png");
	graphHandles[1] = LoadGraph("Textures/Number/2.png");
	graphHandles[2] = LoadGraph("Textures/Number/1.png");

	this->position = position;

	for (int i = 0; i < TEXTURE_NUM; i++)
	{
		GetGraphSize(graphHandles[i], &size[i].w, &size[i].h);
		isCall[i] = false;
	}
}

CountDownUI::~CountDownUI()
{
	DeleteGraph(graphHandles[0]);
	DeleteGraph(graphHandles[1]);
	DeleteGraph(graphHandles[2]);
}

void CountDownUI::Update(double currentTime)
{
	
	
	if (currentTime > 1.0 && !isCall[0])
	{
		isCall[0] = true;
		isDraw = true;
	}
	if (currentTime > 2.0 && !isCall[1])
	{
		isCall[1] = true;
		index++;
	}
	if (currentTime > 3.0 && !isCall[2])
	{
		isCall[2] = true;
		index++;
	}
}

void CountDownUI::Draw()
{
	if (!isDraw) { return; }
	DrawGraph(position.x - size[index].w / 2, position.y - size[index].h / 2, graphHandles[index], TRUE);
}

void CountDownUI::Terminate()
{
	isDraw = false;
	index = 0;
	for (int i = 0; i < TEXTURE_NUM; i++)
	{
		isCall[i] = false;
	}
}
