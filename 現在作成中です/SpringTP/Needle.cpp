#include "Needle.h"

const VECTOR FirstNormedVec = VGet(1, 0, 0);
const float NeedleSpeed = 1.f;
const int MaxHP = 2;
const float NeedleSize = 1.5f;
const float NeedleR = 0.75f;
const unsigned int NormalColor = GetColor(0, 255, 0);
const unsigned int OneHitColor = GetColor(255, 0, 0);
const int ConeDivNum = 16;

Needle::Needle(VECTOR _pos, int _tag)
{
	pos = _pos;
	tag = _tag;
	aheadVec = VSub(ZERO_POS, pos);
	aheadVec = VNorm(aheadVec);
	speed = NeedleSpeed;
	tag = NEEDLE;
	normedVec = aheadVec;
	HP = MaxHP;
}

Needle::~Needle()
{
}

void Needle::Update(float deltaTime)
{
	pos = VAdd(pos, VScale(aheadVec, NeedleSpeed));
	if (HP <= ZERO_I)
	{
		isAlive = false;
	}
}

void Needle::Draw()
{
	DrawCone3D(VAdd(pos, VScale(aheadVec, NeedleSize)), pos, NeedleR, ConeDivNum, NormalColor, NormalColor, true);
	DrawCone3D(VAdd(pos, VScale(aheadVec, NeedleSize)), pos, NeedleR, ConeDivNum, NormalColor, NormalColor, false);
}
