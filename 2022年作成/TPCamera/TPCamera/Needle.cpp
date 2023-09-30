#include<math.h>
#include "Needle.h"

Needle::Needle(VECTOR _pos)
{
    pos = _pos;
    moveDis = 0.0f;
    Color = GetColor(0, 255, 0);
    redColorValue = 0;
    type = NEEDLE;
    turnRad = 0.0f;
    HP = 0.25f;
}

Needle::~Needle()
{
}

void Needle::Update(float deltaTime)
{
    turnRad += turnSpeed * deltaTime * 10.0f;
    pos.z -= obsSpeed * deltaTime;
    moveDis += obsSpeed * deltaTime;
    if (HP < 0.0f)
    {
        deadFlag = true;
    }
    ColorChanger();
}

void Needle::Draw()
{
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
    DrawCone3D(pos, VGet(pos.x, pos.y, pos.z + needleLong), needleWidth, 16, Color, Color, true);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
    DrawCone3D(pos, VGet(pos.x, pos.y, pos.z + needleLong), needleWidth, 8, GetColor(0, 255, 0), GetColor(0,255,0), false);
    DrawLine3D(pos, VGet(pos.x, -20.0f, pos.z), Color);
}

void Needle::ColorChanger()
{
    redColorValue = 255 * (1-(HP / 0.5f));
    Color = GetColor(redColorValue, 255 - redColorValue, 0);
}
