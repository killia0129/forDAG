#include<math.h>
#include "Meteor.h"

const float MeteorSize = 1.5f;
const float WaveSpeed = 0.5f;
const float MeteorSpeed = 0.75f;
const int MaxHP = 3;
const VECTOR YAxis = VGet(0, 1, 0);
const VECTOR XYZOneVec = VNorm(VGet(1, 1, 1));
const unsigned int NormalColor = GetColor(0, 255, 0);
const unsigned int OneHitColor = GetColor(255, 0, 0);

Meteor::Meteor(VECTOR _pos, int _tag, bool _waveFlag)
{
	pos = _pos;
	tag = _tag;
	waveFlag = _waveFlag;
	waveController = ZERO_F;
	HP = MaxHP;
	//crossVec = VTransform(aheadVec, MGetRotY(RoundRad * QUARTER * DX_PI_F));
	crossVec = VCross(aheadVec, YAxis);
	crossVec = VNorm(crossVec);
}

Meteor::~Meteor()
{
}

void Meteor::Update(float deltaTime)
{
	if (waveFlag)
	{
		WaveMove(deltaTime);
	}
	else
	{
		StraightMove(deltaTime);
	}
	if (HP <= ZERO_I)
	{
		isAlive = false;
	}
}

void Meteor::Draw()
{
	DrawCube3D(VAdd(pos, VScale(XYZOneVec, MeteorSize)), VSub(pos, VScale(XYZOneVec, MeteorSize)), NormalColor, NormalColor, true);
}

void Meteor::WaveMove(float deltaTime)
{
	VECTOR plusVec = VAdd(aheadVec, VScale(crossVec, sinf(waveController * DX_PI_F)));
	plusVec = VNorm(plusVec);
	pos = VAdd(pos, VScale(plusVec, MeteorSpeed * deltaTime));
	waveController += WaveSpeed * deltaTime;
	if (waveController > RoundRad)
	{
		waveController -= RoundRad;
	}
}

void Meteor::StraightMove(float deltaTime)
{
	pos = VAdd(pos, VScale(aheadVec, MeteorSpeed * deltaTime));
}
