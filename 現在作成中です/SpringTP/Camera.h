#pragma once
#include"game.h"
//#include"DxLib.h"
class Camera
{
public:
    Camera(VECTOR _pos);
    virtual ~Camera();
    void Update(float deltaTime,VECTOR _pos);
    float GetPitch();

private:
    VECTOR pos;
    float roll;
    float pitch;
    float yaw;
    MATRIX matX;//X����]�s��
    MATRIX matY;//Y����]�s��
    MATRIX matZ;//Z����]�s��
    VECTOR vec;//�J�����̌����Ă������
    bool cameraMoveFlag;//���������Ȃ����Ă����Ƃ��̔���p

    void MoveCamera(float deltaTime);
};

