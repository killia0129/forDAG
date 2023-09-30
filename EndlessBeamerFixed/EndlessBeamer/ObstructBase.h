#pragma once
#include "Object.h"

const int MaxColorValue = 255;
const float MarkerPosY = -20.f;

class ObstructBase :
    public Object
{
public:
    virtual void Update(float deltaTime)override = 0;//毎フレーム呼び出す
    virtual void Draw()override = 0;//描画

protected:
    float maxHp;//初期HP
    unsigned int color;//描画色
    int redColorValue;//赤色の割合
    VECTOR posMarker;//下に生やす線の下のpos
    void ColorCanger();
};

