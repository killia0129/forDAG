#pragma once
#include<DxLib.h>
class Object
{
public:
    virtual void Draw() = 0;
    virtual void Update(float deltaTime) = 0;

protected:
    VECTOR pos;
};

