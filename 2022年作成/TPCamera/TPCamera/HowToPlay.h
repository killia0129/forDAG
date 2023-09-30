#pragma once
#include "Object.h"
#include"game.h"
class HowToPlay :
    public Object
{
public:
    HowToPlay();
    virtual ~HowToPlay();
    void Update(float deltaTime);
    bool isEnd() { return endFlag; }
    void Draw();

private:
    VECTOR upperRight, lowerRight, upperLeft, lowerLeft;
    VECTOR stick;
    bool leftFlag, rightFlag;
    bool endFlag;
};

