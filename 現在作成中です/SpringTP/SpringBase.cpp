#include "SpringBase.h"
#include"DxLib.h"


const int SpringRollNum = 6;
const float SpringRollRatio = 0.2f;
const float SpringRollMidDiff = 0.001f;
const int SpringRollDivNum = 16;

SpringBase::SpringBase(VECTOR _pos, VECTOR _vec, float _length, float _size, float _roll, float _pitch, float _yaw)
{
	pos = _pos;
	vec = _vec;
	normedVec = VNorm(vec);
	length = _length;
	size = _size;
	roll = _roll;
	pitch = _pitch;
	yaw = _yaw;
	matX = MGetRotX(roll * DX_PI_F);
	matY = MGetRotY(pitch * DX_PI_F);
	matZ = MGetRotZ(yaw * DX_PI_F);
	rolled = matX;
	pitched = matY;
	yawed = matZ;
	vec = VTransform(normedVec, matX);
	vec = VTransform(vec, matY);
	vec = VTransform(vec, matZ);
	veced = vec;
	color = GetColor(0, 255, 0);
}

SpringBase::~SpringBase()
{
}

void SpringBase::Draw()
{
	VECTOR lineLast = VAdd(pos, VScale(veced, length));
	DrawLine3D(pos, lineLast, color);
	for (int i = ZERO_I; i < SpringRollNum; i++)
	{
		DrawCone3D(VAdd(pos, VScale(veced, length*SpringRollRatio * (float)i)), VAdd(pos, VScale(veced, length * SpringRollRatio  * (float)i + SpringRollMidDiff)), size,SpringRollDivNum, color, color, false);
	}
}

void SpringBase::Update(float deltaTime)
{
	matX = MGetRotX(roll * DX_PI_F);
	matY = MGetRotY(pitch * DX_PI_F);
	matZ = MGetRotZ(yaw * DX_PI_F);
	vec = VTransform(normedVec, matX);
	vec = VTransform(vec, matY);
	vec = VTransform(vec, matZ);
}

void SpringBase::SetRoll(float _roll)
{
	roll = _roll;
}

void SpringBase::SetPitch(float _pitch)
{
}

void SpringBase::SetYaw(float _yaw)
{
}

void SpringBase::SetRotate(float _roll, float _pitch, float _yaw)
{
	veced = vec;
	rolled = MGetRotX(_roll * DX_PI_F);
	pitched = MGetRotY(_pitch * DX_PI_F);
	yawed = MGetRotZ(_yaw * DX_PI_F);
	veced = VTransform(veced, rolled);
	veced = VTransform(veced, pitched);
	veced = VTransform(veced, yawed);
}

void SpringBase::SetPos(VECTOR _pos)
{
	pos = _pos;
}

