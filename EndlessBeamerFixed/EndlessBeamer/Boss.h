#pragma once
#include"ObstructBase.h"

const int AfterImageNum = 32;
class Boss :
    public ObstructBase
{
public:
    Boss(VECTOR _pos);
    virtual ~Boss();
    void Update(float deltaTime)override;
    void Draw()override;

private:
    float rad;
    float xSpeed;
    float ySpeed;
    float bitRad[4];
    VECTOR lineStart[2];
    VECTOR lineEnd[2];
    VECTOR needlePos[4];
    VECTOR needleTopPos[4];
    VECTOR bitPos[4];
    VECTOR prevPos[AfterImageNum];

    void AddRad(float& _rad, float deltaTime, float _turnSpeed);
    void MoveDecoration();
};

