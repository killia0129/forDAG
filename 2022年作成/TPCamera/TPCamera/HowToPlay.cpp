#include "HowToPlay.h"

HowToPlay::HowToPlay()
{
	pos = VGet(0, 0, 540);
	upperRight = VGet(pos.x + 20.0f, pos.y + 12.5f, pos.z);
	lowerRight = VGet(pos.x + 20.0f, pos.y - 10.0f, pos.z);
	upperLeft = VGet(pos.x - 15.0f, pos.y + 15.0f, pos.z);
	lowerLeft = VGet(pos.x - 20.0f, pos.y - 15.0f, pos.z);
	stick = VGet(pos.x - 5.0f, pos.y + 3.0f, pos.z);
	leftFlag = true;
	rightFlag = false;
	endFlag = false;
}

HowToPlay::~HowToPlay()
{
}

void HowToPlay::Update(float deltaTime)
{
	if (leftFlag)
	{
		pos.z -= obsSpeed * deltaTime * 1.5f;
		upperRight = VGet(pos.x + 20.0f, pos.y + 12.5f, pos.z);
		lowerRight = VGet(pos.x + 20.0f, pos.y - 10.0f, pos.z);
		upperLeft = VGet(pos.x - 15.0f, pos.y + 15.0f, pos.z);
		lowerLeft = VGet(pos.x - 20.0f, pos.y - 15.0f, pos.z);
		stick = VGet(pos.x - 5.0f, pos.y + 3.0f, pos.z);
		if (pos.z < 200.0)
		{
			pos.z -= obsSpeed * deltaTime;
		}
		if (pos.z < 0.0f)
		{
			leftFlag = false;
			rightFlag = true;
			pos = VGet(0, 0, 540);
		}
	}
	if (rightFlag)
	{
		pos.z -= obsSpeed * deltaTime * 1.5f;
		upperRight = VGet(pos.x + 15.0f, pos.y + 15.0f, pos.z);
		lowerRight = VGet(pos.x + 20.0f, pos.y - 15.0f, pos.z);
		upperLeft = VGet(pos.x - 20.0f, pos.y + 12.5f, pos.z);
		lowerLeft = VGet(pos.x - 20.0f, pos.y - 10.0f, pos.z);
		stick = VGet(pos.x + 5.0f, pos.y - 3.0f, pos.z);
		if (pos.z < 200.0)
		{
			pos.z -= obsSpeed * deltaTime;
		}
		if (pos.z < 0.0f)
		{
			endFlag = true;
		}
	}
}

void HowToPlay::Draw()
{
	DrawLine3D(upperRight, upperLeft, GetColor(0, 255, 0));
	DrawLine3D(upperRight, lowerRight, GetColor(0, 255, 0));
	DrawLine3D(lowerRight, lowerLeft, GetColor(0, 255, 0));
	DrawLine3D(lowerLeft, upperLeft, GetColor(0, 255, 0));
	DrawCone3D(VGet(stick.x, stick.y, stick.z - 0.1f), stick, 5.0f, 16, GetColor(0, 255, 0), GetColor(0, 255, 0), false);
	SetFontSize(120);
	if (leftFlag)
	{
		DrawString(400, 300, "MOVE L-STICK", GetColor(0, 255, 0));
	}
	if (rightFlag)
	{
		DrawString(430, 300, "AIM R-STICK", GetColor(0, 255, 0));
	}
}
