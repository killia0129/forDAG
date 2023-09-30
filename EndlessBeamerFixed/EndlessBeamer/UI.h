#pragma once
#include"game.h"
class UI
{
public:
    UI();
    virtual ~UI();
    void Update(float _time, int _deleteNum);
    void Draw();

private:
    int timeGageX;
    int timeGageY;
    float fillRatio;
    int remainNum;
};

