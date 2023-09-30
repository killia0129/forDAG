#pragma once
#include "Object.h"
class Exprosion :
    public Object
{
public:
    Exprosion(VECTOR _pos);
    virtual ~Exprosion();
    void Update(float deltaTime);
    void Draw();
    bool isEnd() { return end; }

private:
    float count;
    bool end;
};

