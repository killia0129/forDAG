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
    //�ړ�
    void Move(float cameraPitch, float deltaTime);
    VECTOR GetPos();

private:

    //�\���p�[�c�Q
    SpringBase* bodySpring;
    SpringBase* rightHandSpring;
    SpringBase* leftHandSpring;

    //�\���p�[�c�̍��W
    VECTOR bodyPos;
    VECTOR rightHandPos;
    VECTOR leftHandPos;
    VECTOR conePos;

    //�A�j���[�V����
    void MoveAnim(float deltaTime);
    void AttackAnim(float deltaTime);
    void JumpAnim(float deltaTime);

    //�A�j���[�V�����t���O
    bool inAttack;
    bool inJump;
    bool moveAnimFlag;

    //�v���C���[�S�̂Ƃ��Ẳ�]
    float roll;
    float pitch;
    float yaw;

    //�e�p�[�c��YZ���ʕ���(�ŏ��̏�Ԃ�)�̉�]�p
    float bodyAngle;
    float rightHandAngle;
    float leftHandAngle;

    float turnRad;
};

