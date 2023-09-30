#pragma once
#include "Object.h"

const int MaxColorValue = 255;
const float MarkerPosY = -20.f;

class ObstructBase :
    public Object
{
public:
    virtual void Update(float deltaTime)override = 0;//���t���[���Ăяo��
    virtual void Draw()override = 0;//�`��

protected:
    float maxHp;//����HP
    unsigned int color;//�`��F
    int redColorValue;//�ԐF�̊���
    VECTOR posMarker;//���ɐ��₷���̉���pos
    void ColorCanger();
};

