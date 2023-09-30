#pragma once
#include <DxLib.h>
#include"ObstructBase.h"
#include"game.h"
class Meteor :
    public ObstructBase
{
public:
    Meteor(VECTOR _pos,bool _wave);
    virtual ~Meteor();
    void Draw();
    void Update(float deltaTime);
    void GivenDmg(float deltaTime) { HP -= deltaTime; }

private:
    float firstPosX;
    float moveDis;
    float rad;
    float yaw;
    float ang;
    float wave;
    bool waveMoveFlag;
    unsigned int Color;
    void addAngle(float& _ang, float deltaTime);
    void ColorChanger();
    int redColorValue;
    float deltaSpeed;
    float HP;
};

