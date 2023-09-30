#pragma once
#include "ObstructBase.h"
class Needle :
    public ObstructBase
{
public:
    Needle(VECTOR _pos);//コンストラクタ
    virtual ~Needle();//デストラクタ
    void Update(float deltaTime)override;//毎フレーム呼び出す
    void Draw()override;//描画

private:
    VECTOR bottomPos;
};

