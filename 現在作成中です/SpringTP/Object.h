#pragma once
#include"game.h"
class Object
{
public:
    Object();
    virtual ~Object();
    virtual void Update(float deltaTime) = 0;

protected:
    VECTOR pos;
};