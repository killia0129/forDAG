#pragma once
#include "ObstructBase.h"
class Needle :
    public ObstructBase
{
public:
    Needle(VECTOR _pos);//�R���X�g���N�^
    virtual ~Needle();//�f�X�g���N�^
    void Update(float deltaTime)override;//���t���[���Ăяo��
    void Draw()override;//�`��

private:
    VECTOR bottomPos;
};

