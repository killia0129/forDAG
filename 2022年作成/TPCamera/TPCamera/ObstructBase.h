#pragma once
#include "Object.h"
class ObstructBase :
    public Object
{
public:
    ObstructBase();
    virtual ~ObstructBase();
    virtual void Update(float deltaTime) = 0;
    virtual void Draw() = 0;
    virtual void GivenDmg(float deltaTime) = 0;
    bool isDead() { return deadFlag; }
    bool isLock() { return lockFlag; }
    void setDead(bool flag) { deadFlag = flag; }
    void setLock(bool flag) { lockFlag = flag; }
    VECTOR posGetter() { return pos; }
    int TypeGetter() { return type; }
    enum TYPE
    {
        METEOR, NEEDLE
    };

protected:
    
    int type;
    bool deadFlag;
    bool lockFlag;
};

