#include<math.h>
#include "Boss.h"

const float MainR = 14.f;
const float CoreR = 7.f;
const float DefaultHp = 2.f;
const float XSpeed = 0.3f;
const float YSpeed = 0.4f;
const float QuarterRad = 0.5f;
const float OneEighthRad = 0.25f;
const float MainToBitDis = 20.f;
const float MainToNeedleDis = 14.f;
const float MainToNeedleTopDis = 25.f;
const float TurnSpeed = 1.f;
const float StopPosZ = 200.f;
const float Speed = 15.f;
const float StageHalfWidth = StageWidth / 2.f;
const float BitSpeed[4] = { 1.5f,2.0f,1.f,2.5f };
const float BitR = 2.f;
const float NeedleR = 4.f;
const int AfterImageAlpha = 64;
const int MainAlpha = 128;
const int AlfaBlendDiff = 2;
const int DivNum = 16;
const int BitNum = 4;
const int LineNum = 2;
const int NeedleNum = 4;

Boss::Boss(VECTOR _pos)
{
	deadFlag = false;
	pos = _pos;
	for (int i = 0; i < AfterImageNum; i++)
	{
		prevPos[i] = _pos;
	}
	hp = DefaultHp;
	xSpeed = XSpeed;
	ySpeed = YSpeed;
	rad = 0.f;
	color = GetColor(0, MaxColorValue, 0);
	for (int i = 0; i < BitNum; i++)
	{
		if (i == 1)
		{
			bitRad[i] = OneEighthRad;
		}
		else
		{
			bitRad[i] = 0.f;
		}
	}
	MoveDecoration();
}

Boss::~Boss()
{
}

void Boss::Update(float deltaTime)
{
	//Žc‘œ‚ðAfterImageNum•ª•Û‘¶(‚Ð‚Æ‚Â‘O‚ÌprevPos‚ÉˆÚ“®)
	for (int i = AfterImageNum - 1; i >= 1; i--)
	{
		prevPos[i] = prevPos[i - 1];
	}
	prevPos[0] = pos;

	//–{‘Ì‚ð‰ñ“]
	rad += TurnSpeed * deltaTime;
	AddRad(rad, deltaTime, TurnSpeed);

	//StopPos‚Ü‚ÅˆÚ“®‚³‚¹‚é
	if (pos.z >= StopPosZ)
	{
		pos.z -= Speed * deltaTime;
	}

	//’[‚Á‚±‚És‚Á‚½‚çx,y‚ÌˆÚ“®‚ð”½“]
	if (pos.x > StageHalfWidth || pos.x < -StageHalfWidth)
	{
		xSpeed *= -1;
	}
	if (pos.y > StageHalfWidth || pos.y < -StageHalfWidth)
	{
		ySpeed *= -1;
	}
	pos.x += xSpeed;
	pos.y += ySpeed;
	
	//‘•ü‚Ì‹…‚ð‰ñ“]
	for (int i = 0; i < BitNum; i++)
	{
		AddRad(bitRad[i], deltaTime, BitSpeed[i]);
	}
	MoveDecoration();

	ColorCanger();

	if (hp <= 0.0f)
	{
		deadFlag = true;
	}
}

void Boss::Draw()
{
	//Žc‘œ•`‰æ
	for (int i = 0; i < AfterImageNum; i++)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, AfterImageAlpha - AlfaBlendDiff * i);
		DrawSphere3D(prevPos[i], MainR * ((float)(AfterImageNum - (i / 2)) / (float)AfterImageNum), DivNum, color, color, true);
	}
	//–{‘Ì•`‰æ
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, MainAlpha);
	DrawSphere3D(pos, MainR, DivNum, color, color, true);
	//ƒRƒA•`‰æ
	SetDrawBlendMode(DX_BLENDGRAPHTYPE_ALPHA, MaxAlphaRatio);
	DrawSphere3D(pos, CoreR, DivNum, color, color, true);
	//‘•ü‚Ìü•`‰æ
	for (int i = 0; i < LineNum; i++)
	{
		DrawLine3D(lineStart[i], lineEnd[i], color);
	}
	//ƒrƒbƒg‚Ì•`‰æ
	for (int i = 0; i < BitNum; i++)
	{
		DrawSphere3D(bitPos[i], BitR, DivNum, color, color, false);
	}
	//ƒgƒQ‚Ì•`‰æ
	for (int i = 0; i < NeedleNum; i++)
	{
		DrawCone3D(needleTopPos[0], needlePos[0], NeedleR, DivNum, color, color, true);
	}
	//‰º‚Éü•`‰æ
	DrawLine3D(pos, VGet(pos.x, MarkerPosY, pos.z), color);
}

void Boss::AddRad(float& _rad, float deltaTime, float _turnSpeed)
{
	_rad += deltaTime * _turnSpeed;
	if (_rad > MaxRad)
	{
		_rad = _rad - MaxRad;
	}
}

void Boss::MoveDecoration()
{
	//‚»‚ê‚¼‚ê‚ÌŒÅ—L‚Ì‰ñ“]‚ð‚³‚¹‚é
	bitPos[0] = VGet(pos.x + (MainToBitDis * cosf(bitRad[0] * DX_PI_F) * cosf(OneEighthRad * DX_PI_F)), pos.y + (MainToBitDis * cosf(bitRad[0] * DX_PI_F) * cosf(OneEighthRad * DX_PI_F)), pos.z - (MainToBitDis * sinf(bitRad[0] * DX_PI_F)));
	bitPos[1] = VGet(pos.x - (MainToBitDis * cosf(bitRad[1] * DX_PI_F) * cosf(OneEighthRad * DX_PI_F)), pos.y - (MainToBitDis * cosf(bitRad[1] * DX_PI_F) * cosf(OneEighthRad * DX_PI_F)), pos.z + (MainToBitDis * sinf(bitRad[1] * DX_PI_F)));
	bitPos[2] = VGet(pos.x + (MainToBitDis * cosf(bitRad[2] * DX_PI_F)), pos.y, pos.z + (MainToBitDis * sinf(bitRad[2] * DX_PI_F)));
	bitPos[3] = VGet(pos.x, pos.y + (MainToBitDis * cosf(bitRad[3] * DX_PI_F)), pos.z - (MainToBitDis * sinf(bitRad[3] * DX_PI_F)));
	needlePos[0] = VGet(pos.x - (MainToNeedleDis * cosf(bitRad[0] * DX_PI_F) * cosf(OneEighthRad * DX_PI_F)), pos.y - (MainToNeedleDis * cosf(bitRad[0] * DX_PI_F) * cosf(OneEighthRad * DX_PI_F)), pos.z + (MainToNeedleDis * sinf(bitRad[0] * DX_PI_F)));
	needlePos[1] = VGet(pos.x + (MainToNeedleDis * cosf(bitRad[1] * DX_PI_F) * cosf(OneEighthRad * DX_PI_F)), pos.y + (MainToNeedleDis * cosf(bitRad[1] * DX_PI_F) * cosf(OneEighthRad * DX_PI_F)), pos.z - (MainToNeedleDis * sinf(bitRad[1] * DX_PI_F)));
	needlePos[2] = VGet(pos.x - (MainToNeedleDis * cosf(bitRad[2] * DX_PI_F)), pos.y, pos.z - (MainToNeedleDis * sinf(bitRad[2] * DX_PI_F)));
	needlePos[3] = VGet(pos.x, pos.y - (MainToNeedleDis * cosf(bitRad[3] * DX_PI_F)), pos.z + (MainToNeedleDis * sinf(bitRad[3] * DX_PI_F)));
	needleTopPos[0] = VGet(pos.x - (MainToNeedleTopDis * cosf(bitRad[0] * DX_PI_F) * cosf(OneEighthRad * DX_PI_F)), pos.y - (MainToNeedleTopDis * cosf(bitRad[0] * DX_PI_F) * cosf(OneEighthRad * DX_PI_F)), pos.z + (MainToNeedleTopDis * sinf(bitRad[0] * DX_PI_F)));
	needleTopPos[1] = VGet(pos.x + (MainToNeedleTopDis * cosf(bitRad[1] * DX_PI_F) * cosf(OneEighthRad * DX_PI_F)), pos.y + (MainToNeedleTopDis * cosf(bitRad[1] * DX_PI_F) * cosf(OneEighthRad * DX_PI_F)), pos.z - (MainToNeedleTopDis * sinf(bitRad[1] * DX_PI_F)));
	needleTopPos[2] = VGet(pos.x - (MainToNeedleTopDis * cosf(bitRad[2] * DX_PI_F)), pos.y, pos.z - (MainToNeedleTopDis * sinf(bitRad[2] * DX_PI_F)));
	needleTopPos[3] = VGet(pos.x, pos.y - (MainToNeedleTopDis * cosf(bitRad[3] * DX_PI_F)), pos.z + (MainToNeedleTopDis * sinf(bitRad[3] * DX_PI_F)));
	lineStart[0] = VGet(pos.x + MainR * sinf(OneEighthRad * DX_PI_F) * cosf(rad * DX_PI_F), pos.y + MainR * cos(OneEighthRad * DX_PI_F), pos.z + MainR * sinf(OneEighthRad * DX_PI_F) * sinf(rad * DX_PI_F));
	lineEnd[0] = VGet(pos.x - MainR * sinf(OneEighthRad * DX_PI_F) * cosf(rad * DX_PI_F), pos.y - MainR * cos(OneEighthRad * DX_PI_F), pos.z - MainR * sinf(OneEighthRad * DX_PI_F) * sinf(rad * DX_PI_F));
	lineStart[1] = VGet(pos.x - MainR * sinf(OneEighthRad * DX_PI_F) * cosf((rad + HalfRad) * DX_PI_F), pos.y - MainR * cos(OneEighthRad * DX_PI_F), pos.z - MainR * sinf(OneEighthRad * DX_PI_F) * sinf((rad + HalfRad) * DX_PI_F));
	lineEnd[1] = VGet(pos.x + MainR * sinf(OneEighthRad * DX_PI_F) * cosf((rad + HalfRad) * DX_PI_F), pos.y + MainR * cos(OneEighthRad * DX_PI_F), pos.z + MainR * sinf(OneEighthRad * DX_PI_F) * sinf((rad + HalfRad) * DX_PI_F));
}


