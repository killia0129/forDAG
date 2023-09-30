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
    float rad;//Meteor�̉�]�p
    float waveRad;//�E�F�[�u����p
    bool waveFlag;//�E�F�[�u�ړ�����Ȃ�true
    VECTOR upperPos;//�����̂̏��pos
    VECTOR lowerPos;//�����̂̉���pos
    float firstPosX;//�������ꂽpos��x���W

    void AddRad(float deltaTime, float& _rad);//���W�A���p�̒ǉ��A2.0�ȏ�ɂȂ����烊�Z�b�g
};

