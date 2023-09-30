#include "Particle.h"

const int ParticleR = 0.5f;
const float DefaultXPower = -0.5f;
const float DefaultYPower = -0.25f;
const float XPowerRange = 20.f;
const float YPowerRange = 40.f;
const float ZSpeed = 500.f;
const float MaxTime = 1.5f;
const int AlphaRatio = 128;
const unsigned int Color = GetColor(255, 0, 0);
const int DivNum = 8;
const float g = 0.49f;

Particle::Particle(VECTOR _pos)
{
	pos = _pos;
	rad = ParticleR;
	count = 0.f;
	deadFlag = false;
	xPower = DefaultXPower + ((float)(rand() % (int)XPowerRange) / XPowerRange);
	yPower = DefaultYPower + ((float)(rand() % (int)YPowerRange) / YPowerRange);
}

Particle::~Particle()
{
}

void Particle::Update(float deltaTime)
{
	rad = ((MaxTime - count) / MaxTime) * ParticleR;
	yPower -= g * deltaTime;
	pos.x += xPower*deltaTime;
	pos.y += yPower*deltaTime;
	//pos.z -= ZSpeed * deltaTime;
	count += deltaTime;
	if (count > MaxTime)
	{
		deadFlag = true;
	}
}

void Particle::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, AlphaRatio);
	DrawSphere3D(pos, rad, DivNum, Color,Color, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, MaxAlphaRatio);
}
