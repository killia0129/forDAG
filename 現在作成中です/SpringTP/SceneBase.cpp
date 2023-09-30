#include "SceneBase.h"

SceneBase::SceneBase()
{
    endFlag = false;
}

SceneBase::~SceneBase()
{
}

bool SceneBase::isEnd()
{
    return endFlag;
}
