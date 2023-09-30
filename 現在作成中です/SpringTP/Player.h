#pragma once
#include "Object.h"
#include"SpringBase.h"
class Player :
    public Object
{
public:
    Player(VECTOR _pos);
    virtual ~Player();
    void Update(float deltaTime);
    void Draw();
    //移動
    void Move(float cameraPitch, float deltaTime);
    VECTOR GetPos();

private:

    //構成パーツ群
    SpringBase* bodySpring;
    SpringBase* rightHandSpring;
    SpringBase* leftHandSpring;

    //構成パーツの座標
    VECTOR bodyPos;
    VECTOR rightHandPos;
    VECTOR leftHandPos;
    VECTOR conePos;

    //アニメーション
    void MoveAnim(float deltaTime);
    void AttackAnim(float deltaTime);
    void JumpAnim(float deltaTime);

    //アニメーションフラグ
    bool inAttack;
    bool inJump;
    bool moveAnimFlag;

    //プレイヤー全体としての回転
    float roll;
    float pitch;
    float yaw;

    //各パーツのYZ平面方向(最初の状態で)の回転角
    float bodyAngle;
    float rightHandAngle;
    float leftHandAngle;

    float turnRad;
};

