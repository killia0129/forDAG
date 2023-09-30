#pragma once
#include "ObstructBase.h"
class Meteor :
    public ObstructBase
{
public:
    Meteor(VECTOR _pos,bool _waveFlag);
    virtual ~Meteor();
    void Update(float deltaTime)override;
    void Draw()override;

private:
    float rad;//Meteorの回転角
    float waveRad;//ウェーブ制御用
    bool waveFlag;//ウェーブ移動するならtrue
    VECTOR upperPos;//直方体の上のpos
    VECTOR lowerPos;//直方体の下のpos
    float firstPosX;//生成されたposのx座標

    void AddRad(float deltaTime, float& _rad);//ラジアン角の追加、2.0以上になったらリセット
};

