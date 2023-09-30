#pragma once
#include "Object.h"
class EnemyBase :
    public Object
{
public:
    EnemyBase();
    virtual ~EnemyBase();
    virtual void Update(float deltaTime) = 0;
    virtual void Draw() = 0;

protected:
    VECTOR aheadVec;
    int tag;
    bool isLocked;
    bool isAlive;
    int HP;
};

