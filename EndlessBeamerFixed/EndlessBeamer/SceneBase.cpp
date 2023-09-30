#include "SceneBase.h"

SceneBase::SceneBase()
{
	sceneEndFlag = false;
	nextScene = GAME;
}

SceneBase::~SceneBase()
{
}

bool SceneBase::IsEnd()
{
	return sceneEndFlag;
}

GameScenes SceneBase::NextScene()
{
	return nextScene;
}
