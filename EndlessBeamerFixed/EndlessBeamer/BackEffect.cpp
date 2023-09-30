#include<math.h>
#include "BackEffect.h"

const int CurveTypeNum = 4;
const int CurveDefaultPosXLength = 100;
const int CurveDefaultPosYLength = 50;
const float DefaultX = 20.f;
const float DefaultY = 20.f;
const float DefaultZ = 550.f;
const int RandomPosNum = 2;
const float LineLength = 20.0f;
const float LineSpeed = 500.0f;
const float StraightSpeedX = 0.01f;
const int StraightSize = 7.5f;
const int StraightDivNUm = 16;
const unsigned int Color = GetColor(0, MaxColorRatio, 0);
const int AlphaRatio = 80;
const int CurveRatio = 50;
const int StrayLightRandomRad = 10;
const float StrayLightRandItoFRatio = 10.f;
const int StrayLightRandMoveRatio = 2.f;
const int StrayLightSpeed = 100.f;
const int StrayLightMoveR = 10.f;
const float OneThirdPi = DX_PI_F / 3.f;

BackEffect::BackEffect()
{
    deadFlag = false;
    curvingFlag = false;
    curvedFlag = false;
    switch (rand() % CurveTypeNum)
    {
    case 0:
        curveType = STRAIGHT;
        break;

    case 1:
        curveType = CURVE_HI;
        break;

    case 2:
        curveType = CURVE_LOW;
        break;

    case 3:
        curveType = STRAYLIGHT;
        break;
    default:
        curveType = STRAYLIGHT;
        break;
    }

    if (rand() % RandomPosNum == 0)
    {
        if (rand() % RandomPosNum == 0)
        {
            pos = VGet(DefaultX + (float)(rand() % CurveDefaultPosXLength), DefaultY + (float)(rand() % CurveDefaultPosYLength), DefaultZ);
        }
        else
        {
            pos = VGet(DefaultX + (float)(rand() % CurveDefaultPosXLength), -DefaultY - (float)(rand() % CurveDefaultPosYLength), DefaultZ);
        }
    }
    else
    {
        if (rand() % RandomPosNum == 0)
        {
            pos = VGet(-DefaultX - (float)(rand() % CurveDefaultPosXLength), DefaultY + (float)(rand() % CurveDefaultPosYLength), DefaultZ);
        }
        else
        {
            pos = VGet(-DefaultX - (float)(rand() % CurveDefaultPosXLength), -DefaultY - (float)(rand() % CurveDefaultPosYLength), DefaultZ);
        }
    }
    midPos = pos;
    midPos.z -= LineLength / 2.f;//ê^ÇÒíÜÇ»ÇÃÇ≈îºï™ÇÃí∑Ç≥à¯Ç≠
    endPos = pos;
    endPos.z -= LineLength;
}

BackEffect::~BackEffect()
{
}

void BackEffect::Update(float deltaTime)
{
    switch (curveType)
    {
    case STRAIGHT:
        StraightUpdate(deltaTime);
        break;

    case CURVE_HI:
        CurveHiUpdate(deltaTime);
        break;

    case CURVE_LOW:
        CurveLowUpdate(deltaTime);
        break;

    case STRAYLIGHT:
        StrayLightUpdate(deltaTime);
        break;

    default:
        StraightUpdate(deltaTime);
        break;
    }

    if (endPos.z < 0.0f)
    {
        deadFlag = true;
    }
}

void BackEffect::Draw()
{
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, AlphaRatio);
    if (curveType == STRAIGHT)
    {
        DrawCone3D(pos, midPos, StraightSize, StraightDivNUm, Color, Color, false);
    }
    else
    {
        DrawLine3D(pos, midPos, Color);
        DrawLine3D(midPos, endPos, Color);
        if (curveType == STRAYLIGHT)
        {
            DrawLine3D(pos, endPos, Color);
        }
    }
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, MaxAlphaRatio);
}

void BackEffect::StraightUpdate(float deltaTime)
{
    pos.z -= LineSpeed * deltaTime;
    endPos.z -= LineSpeed * deltaTime;
    midPos = pos;
    midPos.x -= StraightSpeedX;
}

void BackEffect::CurveHiUpdate(float deltaTime)
{
    if (rand() % CurveRatio == 0 && !curvedFlag && !curvingFlag)
    {
        curvingFlag = true;
        midPos = pos;
    }
    else
    {
        pos.z -= LineSpeed * deltaTime;
        midPos.z -= LineSpeed * deltaTime;
        endPos.z -= LineSpeed * deltaTime;
    }
    if (curvingFlag && !curvedFlag)
    {
        pos.y += LineSpeed * deltaTime;
        endPos.z -= LineSpeed * deltaTime;
        if (endPos.z <= midPos.z)
        {
            float tmp;
            tmp = midPos.z - endPos.z;
            pos.y += tmp;
            endPos = midPos;
            curvedFlag = true;
            midPos = pos;
        }
    }
    if (curvingFlag && curvedFlag)
    {
        pos.z -= LineSpeed * deltaTime;
        endPos.y += LineSpeed * deltaTime;
        if (endPos.y >= midPos.y)
        {
            float tmp;
            tmp = endPos.y - midPos.y;
            pos.z -= tmp;
            endPos = midPos;
            curvingFlag = false;
            midPos = pos;
        }
    }
    if (!curvingFlag && curvedFlag)
    {
        pos.z -= LineSpeed * deltaTime;
        midPos.z -= LineSpeed * deltaTime;
        endPos.z -= LineSpeed * deltaTime;
    }
}

void BackEffect::CurveLowUpdate(float deltaTime)
{
    if (rand() % CurveRatio == 0 && !curvedFlag && !curvingFlag)
    {
        curvingFlag = true;
        midPos = pos;
    }
    else
    {
        pos.z -= LineSpeed * deltaTime;
        midPos.z -= LineSpeed * deltaTime;
        endPos.z -= LineSpeed * deltaTime;
    }
    if (curvingFlag && !curvedFlag)
    {
        pos.y -= LineSpeed * deltaTime;
        endPos.z -= LineSpeed * deltaTime;
        if (endPos.z <= midPos.z)
        {
            float tmp;
            tmp = midPos.z - endPos.z;
            pos.y -= tmp;
            endPos = midPos;
            curvedFlag = true;
            midPos = pos;
        }
    }
    if (curvingFlag && curvedFlag)
    {
        pos.z -= LineSpeed * deltaTime;
        endPos.y -= LineSpeed * deltaTime;
        if (endPos.y <= midPos.y)
        {
            float tmp;
            tmp = midPos.y - endPos.y;
            pos.z -= tmp;
            endPos = midPos;
            curvingFlag = false;
            midPos = pos;
        }
    }
    if (!curvingFlag && curvedFlag)
    {
        pos.z -= LineSpeed * deltaTime;
        midPos.z -= LineSpeed * deltaTime;
        endPos.z -= LineSpeed * deltaTime;
    }
}

void BackEffect::StrayLightUpdate(float deltaTime)
{
    int randI;
    float randF;
    randI = rand() % StrayLightRandomRad;
    randF = (float)randI / StrayLightRandItoFRatio;
    pos.z -= LineSpeed * deltaTime * cosf(randF);
    if (randI % StrayLightRandMoveRatio == 0)
    {
        pos.y += StrayLightSpeed * deltaTime * (1.0f - sinf(randF * DX_PI_F));
    }
    else
    {
        pos.y -= StrayLightSpeed * deltaTime * (1.0f - sinf(randF * DX_PI_F));
    }
    midPos = pos;
    midPos.y -= StrayLightMoveR * cosf(OneThirdPi);
    midPos.z -= StrayLightMoveR * sinf(OneThirdPi);
    endPos = midPos;
    endPos.z += StrayLightMoveR;
}
