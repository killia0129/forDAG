#include "UI.h"

const int DefaultTimeGageX = 100;
const int DefaultTimeGageY = 900;
const float DefaultFillRatio = 1.f;
const int MaxRemainNum = 30;
const float MaxTime = 60.f;
const int WindowMidX = 1920 / 2;
const int TimeGageHeight = 50;
const int RemainPosX = 10;
const int RemainPosY = 10;
const int MaxNumX = 20;
const int MaxNumY = 13;
const int RemainColor = GetColor(42, 255, 255);

UI::UI()
{
    timeGageX = DefaultTimeGageX;
    timeGageY = DefaultTimeGageY;
    fillRatio = DefaultFillRatio;
    remainNum = MaxRemainNum;
}

UI::~UI()
{
}

void UI::Update(float _time, int _deleteNum)
{
    remainNum = MaxRemainNum - _deleteNum;
    fillRatio = 1.f - (_time / MaxTime);
    timeGageX = (int)(DefaultTimeGageX * fillRatio);
}

void UI::Draw()
{
    unsigned int color = GetColor(MaxColorRatio * fillRatio, MaxColorRatio * (1 - fillRatio), 0);
    DrawBox(timeGageX + WindowMidX, timeGageY, WindowMidX, timeGageY + TimeGageHeight, color, true);
    DrawBox(-timeGageX + WindowMidX, timeGageY, WindowMidX, timeGageY + TimeGageHeight, color, true);
    SetFontSize(100);
    DrawFormatString(RemainPosX, RemainPosY, RemainColor, "%d", remainNum);
    SetFontSize(40);
    DrawFormatString(MaxNumX, MaxNumY, RemainColor, "/30");
}
