#include "Star.h"

Star::Star()
{
	x = (float)(rand() % 1920) + 1950.f;
	y = (float)(rand() % 1080);
	r = (float)(rand() % 21) / 10.f + 2.f;
	biggerRRatio = 1.f;
	rad = 0.f;
	speedRatio = ((float)(rand() % 3) + 1.f) * 300.f;
	deadFlag = false;
}

Star::~Star()
{
}

void Star::Update(float deltaTime)
{
	x -= deltaTime * speedRatio;
	rad += deltaTime;
	biggerRRatio = sinf(rad * DX_PI_F) + 1.f;
	if (x < -5.f)
	{
		deadFlag = true;
	}
}

void Star::Draw(float _alpha)
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 * _alpha*0.5f);
	DrawCircle(x, y, biggerRRatio*r, GetColor(255, 255, 255), 1, 1);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 * _alpha);
	DrawCircle(x, y, r, GetColor(255, 255, 255), 1, 1);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}
