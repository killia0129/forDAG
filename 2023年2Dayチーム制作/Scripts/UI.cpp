#include "DxLib.h"
#include "UI.h"

UI::UI()
{
	controllerImg = LoadGraph("Textures/UI/Controller.png");
	buttonAImg = LoadGraph("Textures/UI/AButton.png");
}

UI::~UI()
{
	DeleteGraph(controllerImg);
	DeleteGraph(buttonAImg);
}

void UI::ControllerDraw(float x, float y)
{
	DrawGraph(x, y, controllerImg, true);
}

void UI::ButtonADraw(float x,float y)
{
	DrawGraph(x, y, buttonAImg, true);
}