#pragma once
#include<DxLib.h>
#include "Object.h"
#include"Move.h"
#include"InputMove.h"
class Player :
    public Object
{
public:
    Player();
    virtual ~Player();
    void Update(float deltaTime);
    void HPGetter();
    VECTOR posGetter();
    void Draw();

private:
    int HP;
    Move move;
    InputMove input;
    VECTOR prevPos[16];
    void SetDrawPoint(VECTOR _pos);
};

