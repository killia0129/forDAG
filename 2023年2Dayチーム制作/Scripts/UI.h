#pragma once

class UI
{
public:
	UI();
	~UI();

	void ControllerDraw(float x,float y);
	void ButtonADraw(float x, float y);
private:
	int controllerImg;
	int buttonAImg;
};

