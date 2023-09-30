#pragma once
#include "Object.h"
#include"game.h"
class SpringBase :
    public Object
{
public:
    SpringBase(VECTOR _pos,VECTOR _vec,float _length,float _size,float _roll,float _pitch,float _yaw);
    virtual ~SpringBase();
    void Draw();
    void Update(float deltaTime);
    void SetRoll(float _roll);
    void SetPitch(float _pitch);
    void SetYaw(float _yaw);
    void SetRotate(float _roll, float _pitch, float _yaw);
    void SetPos(VECTOR _pos);

protected:
    VECTOR vec;//中心軸のベクトル
    VECTOR normedVec;//正規化したvec
    float length;//長さ
    float size;//円の大きさ
    float roll;
    float pitch;
    float yaw;
    MATRIX matX;//X軸回転行列
    MATRIX matY;//Y軸回転行列
    MATRIX matZ;//Z軸回転行列
    unsigned int color;

    //最後に加える回転関連
    MATRIX rolled;
    MATRIX pitched;
    MATRIX yawed;
    VECTOR veced;
};

