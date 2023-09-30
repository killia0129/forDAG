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
    MATRIX matX;//X軸回転行列
    MATRIX matY;//Y軸回転行列
    MATRIX matZ;//Z軸回転行列
    VECTOR vec;//カメラの向いている方向
    bool cameraMoveFlag;//処理を少なくしていいときの判定用

    void MoveCamera(float deltaTime);
};

