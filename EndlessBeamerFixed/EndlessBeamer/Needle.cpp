#include "Needle.h"


const float DefaultHP = 0.25f;
const float Speed = 50.f;
const int MainAlphaRatio = 200;
const float NeedleLength = 2.f;
const float NeedleWidth = 2.5f;
const int DivNum = 8;

Needle::Needle(VECTOR _pos)
{
	pos = _pos;
	bottomPos = _pos;
	bottomPos.z += NeedleLength;
	color = GetColor(0, MaxColorValue, 0);
	type = NEEDLE;
	hp = DefaultHP;
	posMarker = pos;
	deadFlag = false;
	maxHp = hp;
}

Needle::~Needle()
{
}

void Needle::Update(float deltaTime)
{
	pos.z -= Speed * deltaTime;//zç¿ïWÇå∏ÇÁÇ∑
	bottomPos = pos;
	posMarker = pos;
	bottomPos.z += NeedleLength;
	posMarker.y = MarkerPosY;
	if (hp < 0.f)
	{
		deadFlag = true;
	}
	ColorCanger();
}

void Needle::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, MainAlphaRatio);
	DrawCone3D(pos, bottomPos, NeedleWidth, DivNum, color, color, true);
	SetDrawBlendMode(DX_BLENDGRAPHTYPE_ALPHA, MaxAlphaRatio);
	DrawCone3D(pos, bottomPos, NeedleWidth, DivNum, color, color, false);
	DrawLine3D(pos, posMarker, color);
}
