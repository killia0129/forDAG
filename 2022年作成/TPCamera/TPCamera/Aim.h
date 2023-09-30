#pragma once
#include<DxLib.h>
class Aim
{
public:
	Aim();
	virtual ~Aim();
	void Update(float deltaTime,VECTOR pPos);
	void Draw(bool lockFlag);
	VECTOR MarkGetter() { return aimMark; }

private:
	VECTOR nearSquare;
	VECTOR farSquare;
	int mousePointX;
	int mousePointY;
	VECTOR aimMark;
	VECTOR playerPos;
	VECTOR lineLast;
	VECTOR prevPlayerPos[16];
	VECTOR prevLineLast[16];
	unsigned int color;
	unsigned int normalColor;
	unsigned int lockedColor;
	const float nearMarkRatio = 50.0f / 80.0f;
	const float farMarkRatio = 110.0f / 80.0f;
	const float lastMarkRatio = 500.0f / 80.0f;
};

