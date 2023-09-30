#include<math.h>
#include "LineEffect.h"

LineEffect::LineEffect()
{
    endFlag = false;
    curvingFlag = false;
    curvedFlag = false;
    switch (rand()%4)
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
    if (rand() % 2 == 0)
    {
        if (rand() % 2 == 0)
        {
            pos = VGet(20.0 + (rand() % 100), 20.0 + (rand() % 50), 550);
        }
        else
        {
            pos = VGet(20.0 + (rand() % 100), -20.0 - (rand() % 50), 550);
        }
    }
    else
    {
        if (rand() % 2 == 0)
        {
            pos = VGet(-20.0 - (rand() % 100), 20.0 + (rand() % 50), 550);
        }
        else
        {
            pos = VGet(-20.0 - (rand() % 100), -20.0 - (rand() % 50), 550);
        }
    }
    midPos = pos;
    midPos.z -= LineLength / 2.0f;
    endPos = pos;
    endPos.z -= LineLength;
}

LineEffect::~LineEffect()
{
}

void LineEffect::Update(float deltaTime)
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
        endFlag = true;
    }
}

void LineEffect::Draw()
{
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 80);
    if (curveType == STRAIGHT)
    {
        //DrawSphere3D(pos, 5.0f, 0, GetColor(0, 255, 0), GetColor(0, 255, 0), false);
        DrawCone3D(pos, midPos, 7.5f, 16, GetColor(0, 255, 0), GetColor(0, 255, 0), false);
    }
    else
    {
        DrawLine3D(pos, midPos, GetColor(0, 255, 0));
        DrawLine3D(midPos, endPos, GetColor(0, 255, 0));
        if (curveType == STRAYLIGHT)
        {
            DrawLine3D(pos, endPos, GetColor(0, 255, 0));
        }
    }
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}

void LineEffect::StraightUpdate(float deltaTime)
{
    pos.z -= LineSpeed * deltaTime;
    //midPos.z -= LineSpeed * deltaTime;
    endPos.z -= LineSpeed * deltaTime;
    midPos = pos;
    midPos.x -= 0.01f;
}

void LineEffect::CurveHiUpdate(float deltaTime)
{
    if (rand() % 50 == 0 && !curvedFlag && !curvingFlag)
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

void LineEffect::CurveLowUpdate(float deltaTime)
{
    if (rand() % 50 == 0 && !curvedFlag && !curvingFlag)
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

void LineEffect::StrayLightUpdate(float deltaTime)
{
    int randI;
    float randF;
    randI = rand() % 10;
    randF = (float)randI / 10.0f;
    pos.z -= LineSpeed * deltaTime*cosf(randF);
    //endPos.z -= LineSpeed * deltaTime * cosf(randF / 2.0f);
    if (randI % 2 == 0)
    {
        pos.y += 100.0f * deltaTime * (1.0f - sinf(randF*DX_PI_F));
        //endPos.y += 100.0f * deltaTime * (1.0f - sinf(randF));
    }
    else
    {
        pos.y -= 100.0f * deltaTime * (1.0f - sinf(randF* DX_PI_F));
        //endPos.y -= 100.0f * deltaTime * (1.0f - sinf(randF));
    }
    midPos = pos;
    midPos.y -= 10.0f * cosf(DX_PI_F / 3.0f);
    midPos.z -= 10.0f * sinf(DX_PI_F / 3.0f);
    endPos = midPos;
    endPos.z += 10.0f;
}
