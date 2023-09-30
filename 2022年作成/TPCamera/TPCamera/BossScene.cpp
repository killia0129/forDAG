#include "BossScene.h"

const int AfterImageNum = 32;
const float MainR = 14.f;
const float CoreR = 7.f;
const float MaxHP = 2.f;
const float XSpeed = 0.3f;
const float YSpeed = 0.4f;
const float HalfRad = 0.5f;
const float NinetyDigreeRad = 0.5f;
const unsigned int DefaultColor = GetColor(0, 255, 0);
const float MainToBitDiff = 20.f;
const float QuarterRad = 0.25f;
const float MainToNeedleDiff = 14.0f;
const float MainToNeedleTopDiff = 25.f;
const float TurnSpeed = 1.f;
const float RoundRad = 2.f;
const float SpeedUpZ = 200.f;
const float SpeedUpSpeed = 15.f;
const float StageSize = 20.f;
const float OneRad = 1.f;
const float Bit1Speed = 1.5f;
const float Bit2Speed = 2.0f;
const float Bit3Speed = 1.0f;
const float Bit4Speed = 2.5f;
const int DefaultAlfa = 64;
const int AlfaBlendDiff = 2;
const int DivNum = 16;
const int MainRAlfa = 128;
const float BitR = 2.f;
const float NeedleR = 4.f;
const int MaxColorValue = 255;

BossScene::BossScene(VECTOR pos)
{
    BossScene::pos = pos;
    for (int i = 0; i < AfterImageNum; i++)
    {
        prevPos[i] = BossScene::pos;
    }
    mainR = MainR;
    coreR = CoreR;
    HP = MaxHP;
    rad = 0.0f;
    xSpeed = XSpeed;
    ySpeed = YSpeed;
    line1Start = VGet(pos.x + mainR * sinf(HalfRad) * cosf(rad * DX_PI_F), pos.y + mainR * cos(HalfRad), pos.z + mainR * sinf(HalfRad) * sinf(rad * DX_PI_F));
    line1End = VGet(pos.x - mainR * sinf(HalfRad) * cosf(rad * DX_PI_F), pos.y - mainR * cos(HalfRad), pos.z - mainR * sinf(HalfRad) * sinf(rad * DX_PI_F));
    line2Start = VGet(pos.x + mainR * sinf(HalfRad) * cosf((rad + NinetyDigreeRad) * DX_PI_F), pos.y - mainR * cos(HalfRad), pos.z + mainR * sinf(HalfRad) * sinf((rad + NinetyDigreeRad) * DX_PI_F));
    line2End = VGet(pos.x - mainR * sinf(HalfRad) * cosf((rad + NinetyDigreeRad) * DX_PI_F), pos.y + mainR * cos(HalfRad), pos.z - mainR * sinf(HalfRad) * sinf((rad + NinetyDigreeRad) * DX_PI_F));
    Color = DefaultColor;
    redColorValue = 0;
    bit1Rad = 0.0f;
    bit2Rad = QuarterRad;
    bit3Rad = 0.0f;
    bit4Rad = 0.0f;
    bit1Pos = VGet(pos.x + (MainToBitDiff * cosf(bit1Rad * DX_PI_F) * cosf(QuarterRad * DX_PI_F)), pos.y + (MainToBitDiff * cosf(bit1Rad * DX_PI_F) * cosf(QuarterRad * DX_PI_F)), pos.z - (MainToBitDiff * sinf(bit1Rad * DX_PI_F)));
    bit2Pos = VGet(pos.x - (MainToBitDiff * cosf(bit2Rad * DX_PI_F) * cosf(QuarterRad * DX_PI_F)), pos.y - (MainToBitDiff * cosf(bit2Rad * DX_PI_F) * cosf(QuarterRad * DX_PI_F)), pos.z + (MainToBitDiff * sinf(bit2Rad * DX_PI_F)));
    bit3Pos = VGet(pos.x + (MainToBitDiff * cosf(bit3Rad * DX_PI_F)), pos.y, pos.z + (MainToBitDiff * sinf(bit3Rad * DX_PI_F)));
    bit4Pos = VGet(pos.x, pos.y + (MainToBitDiff * cosf(bit4Rad * DX_PI_F)), pos.z - (MainToBitDiff * sinf(bit4Rad * DX_PI_F)));
    needle2Pos= VGet(pos.x + (MainToNeedleDiff * cosf(bit2Rad * DX_PI_F) * cosf(QuarterRad * DX_PI_F)), pos.y + (MainToNeedleDiff * cosf(bit2Rad * DX_PI_F) * cosf(QuarterRad * DX_PI_F)), pos.z - (MainToNeedleDiff * sinf(bit2Rad * DX_PI_F)));
    needle1Pos= VGet(pos.x - (MainToNeedleDiff * cosf(bit1Rad * DX_PI_F) * cosf(QuarterRad * DX_PI_F)), pos.y - (MainToNeedleDiff * cosf(bit1Rad * DX_PI_F) * cosf(QuarterRad * DX_PI_F)), pos.z + (MainToNeedleDiff * sinf(bit1Rad * DX_PI_F)));
    needle3Pos= VGet(pos.x - (MainToNeedleDiff * cosf(bit3Rad * DX_PI_F)), pos.y, pos.z - (MainToNeedleDiff * sinf(bit3Rad * DX_PI_F)));
    needle4Pos = VGet(pos.x, pos.y - (MainToNeedleDiff * cosf(bit4Rad * DX_PI_F)), pos.z + (MainToNeedleDiff * sinf(bit4Rad * DX_PI_F)));
    needleTop1Pos = VGet(pos.x - (MainToNeedleTopDiff * cosf(bit1Rad * DX_PI_F) * cosf(QuarterRad * DX_PI_F)), pos.y - (MainToNeedleTopDiff * cosf(bit1Rad * DX_PI_F) * cosf(QuarterRad * DX_PI_F)), pos.z + (MainToNeedleTopDiff * sinf(bit1Rad * DX_PI_F)));
    needleTop2Pos = VGet(pos.x + (MainToNeedleTopDiff * cosf(bit2Rad * DX_PI_F) * cosf(QuarterRad * DX_PI_F)), pos.y + (MainToNeedleTopDiff * cosf(bit2Rad * DX_PI_F) * cosf(QuarterRad * DX_PI_F)), pos.z - (MainToNeedleTopDiff * sinf(bit2Rad * DX_PI_F)));
    needleTop3Pos = VGet(pos.x - (MainToNeedleTopDiff * cosf(bit3Rad * DX_PI_F)), pos.y, pos.z - (MainToNeedleTopDiff * sinf(bit3Rad * DX_PI_F)));
    needleTop4Pos = VGet(pos.x, pos.y - (MainToNeedleTopDiff * cosf(bit4Rad * DX_PI_F)), pos.z + (MainToNeedleTopDiff * sinf(bit4Rad * DX_PI_F)));
}

BossScene::~BossScene()
{
}

void BossScene::Update(float deltaTime)
{
    for (int i = AfterImageNum - 1; i >= 1; i--)
    {
        prevPos[i] = prevPos[i - 1];
    }
    prevPos[0] = pos;
    rad += TurnSpeed * deltaTime;
    if (rad >= RoundRad)
    {
        rad = 0.0f;
    }
    if (pos.z >= SpeedUpZ)
    {
        pos.z -= SpeedUpSpeed * deltaTime;
    }
    pos.x += xSpeed;
    pos.y += ySpeed;
    if (pos.x > StageSize)
    {
        pos.x = StageSize;
        xSpeed *= -1;
    }
    if (pos.x < -StageSize)
    {
        pos.x = -StageSize;
        xSpeed *= -1;
    }
    if (pos.y > StageSize)
    {
        pos.y = StageSize;
        ySpeed *= -1;
    }
    if (pos.y < -StageSize)
    {
        pos.y = -StageSize;
        ySpeed *= -1;
    }

    line1Start = VGet(pos.x + mainR * sinf(QuarterRad * DX_PI_F) * cosf(rad * DX_PI_F), pos.y + mainR * cos(0.25f * DX_PI_F), pos.z + mainR * sinf(0.25f * DX_PI_F) * sinf(rad * DX_PI_F));
    line1End = VGet(pos.x - mainR * sinf(QuarterRad * DX_PI_F) * cosf(rad * DX_PI_F), pos.y - mainR * cos(0.25f * DX_PI_F), pos.z - mainR * sinf(0.25f * DX_PI_F) * sinf(rad * DX_PI_F));
    line2Start = VGet(pos.x - mainR * sinf(QuarterRad * DX_PI_F) * cosf((rad + OneRad) * DX_PI_F), pos.y - mainR * cos(QuarterRad * DX_PI_F), pos.z - mainR * sinf(QuarterRad * DX_PI_F) * sinf((rad + OneRad) * DX_PI_F));
    line2End = VGet(pos.x + mainR * sinf(QuarterRad * DX_PI_F) * cosf((rad + OneRad) * DX_PI_F), pos.y + mainR * cos(QuarterRad * DX_PI_F), pos.z + mainR * sinf(QuarterRad * DX_PI_F) * sinf((rad + OneRad) * DX_PI_F));


    bit1Rad += Bit1Speed * deltaTime;
    bit2Rad += Bit2Speed * deltaTime;
    bit3Rad += Bit3Speed * deltaTime;
    bit4Rad += Bit4Speed * deltaTime;
    if (bit1Rad > RoundRad)
    {
        bit1Rad = 0.0f;
    }
    if (bit2Rad > RoundRad)
    {
        bit2Rad = 0.0f;
    }
    if (bit3Rad > RoundRad)
    {
        bit3Rad = 0.0f;
    }
    if (bit3Rad > RoundRad)
    {
        bit3Rad = 0.0f;
    }

    bit1Pos = VGet(pos.x + (MainToBitDiff * cosf(bit1Rad * DX_PI_F) * cosf(QuarterRad * DX_PI_F)), pos.y + (MainToBitDiff * cosf(bit1Rad * DX_PI_F) * cosf(QuarterRad * DX_PI_F)), pos.z - (MainToBitDiff * sinf(bit1Rad * DX_PI_F)));
    bit2Pos = VGet(pos.x - (MainToBitDiff * cosf(bit2Rad * DX_PI_F) * cosf(QuarterRad * DX_PI_F)), pos.y - (MainToBitDiff * cosf(bit2Rad * DX_PI_F) * cosf(QuarterRad * DX_PI_F)), pos.z + (MainToBitDiff * sinf(bit2Rad * DX_PI_F)));
    bit3Pos = VGet(pos.x + (MainToBitDiff * cosf(bit3Rad * DX_PI_F)), pos.y, pos.z + (MainToBitDiff * sinf(bit3Rad * DX_PI_F)));
    bit4Pos = VGet(pos.x, pos.y + (MainToBitDiff * cosf(bit4Rad * DX_PI_F)), pos.z - (MainToBitDiff * sinf(bit4Rad * DX_PI_F)));
    needle2Pos = VGet(pos.x + (MainToNeedleDiff * cosf(bit2Rad * DX_PI_F) * cosf(QuarterRad * DX_PI_F)), pos.y + (MainToNeedleDiff * cosf(bit2Rad * DX_PI_F) * cosf(QuarterRad * DX_PI_F)), pos.z - (MainToNeedleDiff * sinf(bit2Rad * DX_PI_F)));
    needle1Pos = VGet(pos.x - (MainToNeedleDiff * cosf(bit1Rad * DX_PI_F) * cosf(QuarterRad * DX_PI_F)), pos.y - (MainToNeedleDiff * cosf(bit1Rad * DX_PI_F) * cosf(QuarterRad * DX_PI_F)), pos.z + (MainToNeedleDiff * sinf(bit1Rad * DX_PI_F)));
    needle3Pos = VGet(pos.x - (MainToNeedleDiff * cosf(bit3Rad * DX_PI_F)), pos.y, pos.z - (MainToNeedleDiff * sinf(bit3Rad * DX_PI_F)));
    needle4Pos = VGet(pos.x, pos.y - (MainToNeedleDiff * cosf(bit4Rad * DX_PI_F)), pos.z + (MainToNeedleDiff * sinf(bit4Rad * DX_PI_F)));
    needleTop1Pos = VGet(pos.x - (MainToNeedleTopDiff * cosf(bit1Rad * DX_PI_F) * cosf(QuarterRad * DX_PI_F)), pos.y - (MainToNeedleTopDiff * cosf(bit1Rad * DX_PI_F) * cosf(QuarterRad * DX_PI_F)), pos.z + (MainToNeedleTopDiff * sinf(bit1Rad * DX_PI_F)));
    needleTop2Pos = VGet(pos.x + (MainToNeedleTopDiff * cosf(bit2Rad * DX_PI_F) * cosf(QuarterRad * DX_PI_F)), pos.y + (MainToNeedleTopDiff * cosf(bit2Rad * DX_PI_F) * cosf(QuarterRad * DX_PI_F)), pos.z - (MainToNeedleTopDiff * sinf(bit2Rad * DX_PI_F)));
    needleTop3Pos = VGet(pos.x - (MainToNeedleTopDiff * cosf(bit3Rad * DX_PI_F)), pos.y, pos.z - (MainToNeedleTopDiff * sinf(bit3Rad * DX_PI_F)));
    needleTop4Pos = VGet(pos.x, pos.y - (MainToNeedleTopDiff * cosf(bit4Rad * DX_PI_F)), pos.z + (MainToNeedleTopDiff * sinf(bit4Rad * DX_PI_F)));



    ColorChanger();

    if (HP <= 0.0f)
    {
        deadFlag = true;
    }
}

void BossScene::Draw()
{
    for (int i = 0; i < AfterImageNum; i++)
    {
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, DefaultAlfa - AlfaBlendDiff * i);
        DrawSphere3D(prevPos[i], mainR * ((float)(AfterImageNum - (i / 2)) / (float)AfterImageNum), DivNum, Color, Color, true);
    }
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, MainRAlfa);
    DrawSphere3D(pos, mainR, DivNum, Color, Color, true);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    DrawSphere3D(pos, coreR, DivNum, Color, Color, true);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    DrawLine3D(line1Start, line1End, Color);
    DrawLine3D(line2Start, line2End, Color);
    DrawSphere3D(bit1Pos, BitR, DivNum, Color, Color, false);
    DrawSphere3D(bit2Pos, BitR, DivNum, Color, Color, false);
    DrawSphere3D(bit3Pos, BitR, DivNum, Color, Color, false);
    DrawSphere3D(bit4Pos, BitR, DivNum, Color, Color, false);
    DrawCone3D(needleTop1Pos, needle1Pos, NeedleR, DivNum, Color, Color, true);
    DrawCone3D(needleTop2Pos, needle2Pos, NeedleR, DivNum, Color, Color, true);
    DrawCone3D(needleTop3Pos, needle3Pos, NeedleR, DivNum, Color, Color, true);
    DrawCone3D(needleTop4Pos, needle4Pos, NeedleR, DivNum, Color, Color, true);
    DrawLine3D(pos, VGet(pos.x, -StageSize, pos.z), Color);
}

void BossScene::ColorChanger()
{
    redColorValue = MaxColorValue * (1 - (HP / MaxHP));
    Color = GetColor(redColorValue, MaxColorValue - redColorValue, 0);
}
