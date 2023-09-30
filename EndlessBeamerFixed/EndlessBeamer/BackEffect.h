#pragma once
#include "Object.h"
class BackEffect :
    public Object
{
public:
    BackEffect();
    virtual ~BackEffect();
    void Update(float deltaTime)override;
    void Draw()override;

private:
    enum LINE_TYPE
    {
        STRAIGHT, CURVE_HI, CURVE_LOW, STRAYLIGHT
    };

    bool curvingFlag;
    bool curvedFlag;
    LINE_TYPE curveType;
    VECTOR midPos;
    VECTOR endPos;
    void StraightUpdate(float deltaTime);
    void CurveHiUpdate(float deltaTime);
    void CurveLowUpdate(float deltaTime);
    void StrayLightUpdate(float deltaTime);
};

