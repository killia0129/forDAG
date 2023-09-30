#pragma once
#include "Common.h"

const int TEXTURE_NUM = 3;

class CountDownUI
{
public:
	CountDownUI(Pos position);
	~CountDownUI();

	void Update(double currentTime);

	void Draw();

	void Terminate();

private:
	int graphHandles[TEXTURE_NUM];
	int index;
	bool isDraw;
	bool isCall[TEXTURE_NUM];

	Pos position;
	Size size[TEXTURE_NUM];
};