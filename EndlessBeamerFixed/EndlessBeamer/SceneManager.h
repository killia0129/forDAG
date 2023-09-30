#pragma once
#include"game.h"
#include"GameScene.h"
#include"TitleScene.h"
#include"EndScene.h"
#include"ClearScene.h"
#include"SceneBase.h"
class SceneManager
{
public:
    SceneManager();
    virtual ~SceneManager();
    void Update();

private:
    SceneBase* scene;
};

