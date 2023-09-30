#pragma once

enum DIR
{
    AHEAD,BACK,LEFT,RIGHT,NEUTRAL
};

const float turnSpeed = 0.75f;
const float waveSpeed = 0.5f;
const float obsSpeed = 50.0f;
const float stageLength = 500.0f;
const float stageWidth = 40.0f;
const float playerSpeed = 50.0f;
const float playerSize = 6.0f;
const float playerR = 1.5f;
const float aimR = 5.0f;
const float particleSec = 1.5f;
const float g = 0.49f;
const float particleR = 0.5f;
const int WindowWidth = 1920;
const int Windowheight = 1080;

//void AddSpeed(float deltaTime)
//{
//    obsSpeed += deltaTime / 10.0f;
//}