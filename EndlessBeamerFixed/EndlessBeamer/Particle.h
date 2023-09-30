#pragma once
#include "Object.h"
#include"game.h"
class Particle :
    public Object
{
public:
    Particle(VECTOR _pos);
    virtual ~Particle();
    void Update(float deltaTime)override;
    void Draw()override;

private:
    float rad;
    float count;
    float xPower;
    float yPower;
};

