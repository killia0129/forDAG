#pragma once
#include<DxLib.h>
class Beam
{
public:
    Beam(int laneNum);
    virtual ~Beam();
    void Update(float deltaTime);
    void Draw();
    void Start();
    bool HitCheck(VECTOR pPos);
  

private:
    VECTOR pos;
    int phase;
    float count;
    int lane;
    float blinkController;
    bool blinkFlag;
    VECTOR beamLast;
    float beamR;
    bool hitFlag;

    enum PHASENAME
    {
        READY,ANNOUNCE,ONFIRE,COOLDOWN
    };
};

