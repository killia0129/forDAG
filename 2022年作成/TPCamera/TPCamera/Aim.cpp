#include<math.h>
#include "Aim.h"
#include"game.h"

const int DefaultMousePointX = 1920 / 2;
const int DefaultMousePointY = 1080 / 2;
const VECTOR NereAimSquarePos = VGet(0, 0, 80.f);
const VECTOR FarAimSquarePos = VGet(0, 0, 140.f);
const VECTOR PlayerDefaultPos = VGet(0, 0, 30.f);
const VECTOR DefaultLineEndPos = VGet(0, 0, 530.f);
const int AfterImageNum = 16;
const VECTOR DefaultAimMarkPos = VGet(0, 0, 110.f);
const unsigned int NormalColor = GetColor(0, 255, 0);
const unsigned int LockedColor = GetColor(255, 0, 0);
const int aimSpeed = 10.f;
const int mouseBuffer = 0;
const float MaxStickSize = 32768.f;
const float PlayerHalfSize = playerSize / 2.f;
const float OneThirdRad = DX_PI_F / 3.f;
const int MaxAlfaBlend = 128;
const int AlfaBlendDiff = 8;
const float BeamR = 0.5f;
const int BeamDivNum = 4;
const unsigned int AfterImageBeamColor = GetColor(10, 10, 255);
const unsigned int BeamColor = GetColor(42, 255, 255);
const float AimMarkR = 1.f;
const int AimMarkDivNum = 16;
const float AimLineLength = 20.f;

Aim::Aim()
{
	SetMousePoint(DefaultMousePointX, DefaultMousePointY);
	nearSquare = NereAimSquarePos;
	farSquare = FarAimSquarePos;
	playerPos = PlayerDefaultPos;
	lineLast = DefaultLineEndPos;
	for (int i = 0; i < AfterImageNum; i++)
	{
		prevPlayerPos[i] = playerPos;
		prevLineLast[i] = lineLast;
	}
	mousePointX = 0;
	mousePointY = 0;
	aimMark = DefaultAimMarkPos;
	normalColor = NormalColor;
	lockedColor = LockedColor;
	color = normalColor;
}

Aim::~Aim()
{
}

void Aim::Update(float deltaTime, VECTOR pPos)
{
	for (int i = AfterImageNum - 1; i >= 1; i--)
	{
		prevPlayerPos[i] = prevPlayerPos[i - 1];
		prevLineLast[i] = prevLineLast[i - 1];
	}
	prevPlayerPos[0] = playerPos;
	prevLineLast[0] = lineLast;
	playerPos = pPos;
	GetMousePoint(&mousePointX, &mousePointY);
	if (mousePointX > DefaultMousePointX + mouseBuffer)
	{
		aimMark.x += (mousePointX - DefaultMousePointX - mouseBuffer) * aimSpeed * deltaTime;
	}
	if (mousePointX < DefaultMousePointX - mouseBuffer)
	{
		aimMark.x += (mousePointX - DefaultMousePointX - mouseBuffer) * aimSpeed * deltaTime;
	}
	if (mousePointY > DefaultMousePointY + mouseBuffer)
	{
		aimMark.y -= (mousePointY - DefaultMousePointY - mouseBuffer) * aimSpeed * deltaTime;
	}
	if (mousePointY < DefaultMousePointY - mouseBuffer)
	{
		aimMark.y -= (mousePointY - DefaultMousePointY - mouseBuffer) * aimSpeed * deltaTime;
	}

	XINPUT_STATE padInput;
	GetJoypadXInputState(DX_INPUT_KEY_PAD1, &padInput);
	

	aimMark.x += aimSpeed * deltaTime * ((float)padInput.ThumbRX / MaxStickSize);
	aimMark.y += aimSpeed * deltaTime * ((float)padInput.ThumbRY / MaxStickSize);

	playerPos.z +=PlayerHalfSize;

	nearSquare.x = (aimMark.x - playerPos.x) * nearMarkRatio + playerPos.x;
	nearSquare.y = (aimMark.y - playerPos.y) * nearMarkRatio + playerPos.y;
	farSquare.x = (aimMark.x - playerPos.x) * farMarkRatio + playerPos.x;
	farSquare.y = (aimMark.y - playerPos.y) * farMarkRatio + playerPos.y;
	lineLast.x = (aimMark.x - playerPos.x) * lastMarkRatio + playerPos.x; 
	lineLast.y = (aimMark.y - playerPos.y) * lastMarkRatio + playerPos.y;
	SetMousePoint(DefaultMousePointX, DefaultMousePointY);
}

void Aim::Draw(bool lockFlag)
{
	if (lockFlag)
	{
		color = lockedColor;
	}
	else
	{
		color = normalColor;
	}
	DrawTriangle3D(VGet(nearSquare.x, nearSquare.y + aimR, nearSquare.z),
		VGet(nearSquare.x + aimR * sinf(2.0f * OneThirdRad), nearSquare.y + aimR * cosf(2.0f * OneThirdRad), nearSquare.z),
		VGet(nearSquare.x + aimR * sinf(4.0f * OneThirdRad), nearSquare.y + aimR * cosf(4.0f * OneThirdRad), nearSquare.z),
		color, false);
	DrawTriangle3D(VGet(farSquare.x, farSquare.y + aimR, farSquare.z),
		VGet(farSquare.x + aimR * sinf(2.0f * OneThirdRad), farSquare.y + aimR * cosf(2.0f * OneThirdRad), farSquare.z),
		VGet(farSquare.x + aimR * sinf(4.0f * OneThirdRad), farSquare.y + aimR * cosf(4.0f * OneThirdRad), farSquare.z),
		color, false);

	for (int i = 0; i < AfterImageNum; i++)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, MaxAlfaBlend - AlfaBlendDiff * i);
		DrawCapsule3D(prevPlayerPos[i], prevLineLast[i], BeamR, BeamDivNum, AfterImageBeamColor, AfterImageBeamColor, true);
	}

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	DrawCapsule3D(playerPos, lineLast, BeamR, BeamDivNum, BeamColor, BeamColor, true);
	DrawCapsule3D(playerPos, lineLast, BeamR, 1, lockedColor, lockedColor, false);


	DrawSphere3D(aimMark, AimMarkR, AimMarkDivNum, lockedColor, lockedColor, true);
	DrawLine3D(aimMark, VGet(aimMark.x, -AimLineLength, aimMark.z), lockedColor);
	DrawLine3D( VGet(-AimLineLength, -AimLineLength, aimMark.z), VGet(AimLineLength, -AimLineLength, aimMark.z),lockedColor);
	DrawLine3D(VGet(-AimLineLength, aimMark.y, aimMark.z), VGet(AimLineLength, aimMark.y, aimMark.z), lockedColor);
	DrawLine3D(VGet(-AimLineLength, -AimLineLength, aimMark.z), VGet(-AimLineLength, AimLineLength, aimMark.z), lockedColor);
	DrawLine3D(VGet(AimLineLength, -AimLineLength, aimMark.z), VGet(AimLineLength, AimLineLength, aimMark.z), lockedColor);
}
