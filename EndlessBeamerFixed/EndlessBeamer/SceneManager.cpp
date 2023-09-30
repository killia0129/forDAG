#include "SceneManager.h"

SceneManager::SceneManager()
{
    //scene = new TitleScene();
    scene = new GameScene();
}

SceneManager::~SceneManager()
{
}

void SceneManager::Update()
{
    while (true)
    {
        scene->Update();
        if (scene->IsEnd())
        {
            delete scene;
            switch (scene->NextScene())
            {
            case TITLE:
                //scene = new TitleScene();
                break;

            case GAME:
                scene = new GameScene();
                break;
            default:
                break;
            }
        }

        if (CheckHitKey(KEY_INPUT_ESCAPE))
        {
            return;
        }
    }
    
}
