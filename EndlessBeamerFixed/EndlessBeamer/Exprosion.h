#pragma once
#include "Object.h"
#include"game.h"
class Exprosion :
    public Object
{
public:
    Exprosion(VECTOR _pos);
    virtual ~Exprosion();
    void Update(float deltaTime)override;
    void Draw()override;

private:
    float count;
};

