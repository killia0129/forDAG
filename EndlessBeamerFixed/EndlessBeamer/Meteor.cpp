#include "Meteor.h"
#include<math.h>

const float CubeSize = 3.5f;
const float DefaultHp = 5.f;
const float TurnSpeed = 0.75f;
const float WaveSpeed = 0.5f;
const float Speed = 40.f;
const float WaveLength = StageWidth / 4.f;
const float OneEighthRad = 0.25f;
const int MainAlphaBlend = 200;


Meteor::Meteor(VECTOR _pos, bool _waveFlag)
{
	pos = _pos;
	upperPos = pos;
	lowerPos = pos;
	posMarker = pos;
	firstPosX = _pos.x;
	rad = 0.f;
	waveRad = 0.f;
	waveFlag = _waveFlag;
	color = GetColor(0, MaxColorValue, 0);
	redColorValue = 0;
	type = METEOR;
	hp = DefaultHp;
	deadFlag = false;
	maxHp = hp;
}

Meteor::~Meteor()
{
}

void Meteor::Update(float deltaTime)
{
	AddRad(deltaTime*TurnSpeed,rad);
	if (waveFlag)
	{
		AddRad(deltaTime*WaveSpeed, waveRad);
		pos.x = firstPosX + (WaveLength * sinf(waveRad * DX_PI_F));
	}
	pos.z -= Speed * deltaTime;
	if (hp < 0.f)
	{
		deadFlag = true;
	}
	posMarker = pos;
	posMarker.y = MarkerPosY;

	//’¼•û‘Ì•`‰æ—p‚ÌÀ•WŒvŽZ
	upperPos.x = pos.x + CubeSize * cos(rad * DX_PI_F);
	lowerPos.x = pos.x - CubeSize * cos(rad * DX_PI_F);
	upperPos.y = pos.y + CubeSize * cos(OneEighthRad * DX_PI_F);
	lowerPos.y = pos.y - CubeSize * cos(OneEighthRad * DX_PI_F);
	upperPos.z = pos.z + CubeSize * sin(rad * DX_PI_F);
	lowerPos.z = pos.z - CubeSize * sin(rad * DX_PI_F);

	ColorCanger();
}

void Meteor::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, MainAlphaBlend);
	DrawCube3D(upperPos, lowerPos, color, color, true);
	SetDrawBlendMode(DX_BLENDGRAPHTYPE_ALPHA, MaxAlphaRatio);
	DrawCube3D(upperPos, lowerPos, color, color, false);
	DrawLine3D(pos, posMarker, color);
}

void Meteor::AddRad(float deltaTime,float& _rad)
{
	_rad += deltaTime;
	if (_rad > MaxRad)
	{
		_rad = _rad - MaxRad;
	}
}
