#pragma once
#include<DxLib.h>
class UI
{
public:
    UI();
    virtual ~UI();
    void Update(float _time, int _deleted);
    void Draw();

private:
    int timeGageX;
    int timeGageY;
    float filledRatio;
    int filledGageY;
    int remainingNum;
};

