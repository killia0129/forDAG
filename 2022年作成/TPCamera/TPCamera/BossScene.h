#pragma once
#include<math.h>
#include<DxLib.h>
#include"Stage.h"
#include"Beam.h"
#include"ObstructBase.h"
class BossScene:public ObstructBase
{
public:
    BossScene(VECTOR pos);
    virtual ~BossScene();
    void Update(float deltaTime);
    void Draw();
    void GivenDmg(float deltaTime) { HP -= deltaTime; }

private:
    float mainR;
    float coreR;
    float HP;
    float rad;
    float xSpeed;
    float ySpeed;
    VECTOR line1Start, line1End;
    VECTOR line2Start, line2End;
    VECTOR bit1Pos, bit2Pos, bit3Pos, bit4Pos;
    VECTOR needle1Pos, needle2Pos, needle3Pos, needle4Pos;
    VECTOR needleTop1Pos, needleTop2Pos, needleTop3Pos, needleTop4Pos;
    float bit1Rad, bit2Rad, bit3Rad, bit4Rad;
    VECTOR prevPos[32];
    unsigned int Color;
    void ColorChanger();
    int redColorValue;
};

