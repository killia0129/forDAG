#include "UI.h"

UI::UI()
{
    timeGageX = 1800;
    timeGageY = 100;
    filledRatio = 0.0f;
    filledGageY = 540;
    remainingNum = 30;
}

UI::~UI()
{
}

void UI::Update(float _time, int _deleted)
{
    remainingNum = 30 - _deleted;
    filledRatio = _time / 60.0f;
    filledGageY = 980 - (880 * filledRatio);
}

void UI::Draw()
{
    DrawBox(timeGageX, timeGageY, timeGageX + 50, 1080 - 100, GetColor(255 * (1 - filledRatio), 255 * filledRatio, 0), true);
    DrawBox(timeGageX, filledGageY, timeGageX + 50, 1080 - 100, GetColor(0, 0, 255), true);
    SetFontSize(100);
    DrawFormatString(timeGageX-160, timeGageY-50, GetColor(42, 255, 255), "%d", remainingNum);
    SetFontSize(40);
    DrawFormatString(timeGageX, timeGageY - 60, GetColor(42, 255, 255), "/30");
}


