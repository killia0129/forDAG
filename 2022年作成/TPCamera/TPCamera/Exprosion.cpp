#include<math.h>
#include "Exprosion.h"

const float MaxCount = 0.5f;
const float CountDownSpeed = 1.2f;
const unsigned int Color = GetColor(255, 0, 0);
const int FirstAlfa = 255;
const int SecondAlfa = 200;
const int DivNum = 8;
const int DefaultFontSize = 40;
const int NiceFontSize = 20;
const float MaxR = 500.f;
const float FadeCount = 1.f;
const unsigned int NiceColor = GetColor(255, 255, 255);
const int NiceAdjustX = 40;
const int NiceAdjustY = 5;

Exprosion::Exprosion(VECTOR _pos)
{
    pos = _pos;
    count = MaxCount;
    end = false;
}

Exprosion::~Exprosion()
{
}

void Exprosion::Update(float deltaTime)
{
    count -= CountDownSpeed*deltaTime;
    if (count < 0.0f)
    {
        end = true;
    }
}

void Exprosion::Draw()
{
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, FirstAlfa * count);
    DrawSphere3D(pos, MaxR * (FadeCount-count), DivNum, Color, Color, false);
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, SecondAlfa * count);
    DrawSphere3D(pos, MaxR * (FadeCount-count), DivNum, Color, Color, true);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    SetFontSize(NiceFontSize);
    DrawString(ConvWorldPosToScreenPos(pos).x - NiceAdjustX, ConvWorldPosToScreenPos(pos).y - NiceAdjustY, "NICE!", NiceColor);
    SetFontSize(DefaultFontSize);
}
