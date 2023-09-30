#pragma once
#include"game.h"
class SceneBase
{
public:
	SceneBase();
	virtual ~SceneBase();

	virtual void Update() = 0;
	virtual bool IsEnd();
	virtual GameScenes NextScene();

protected:
	bool sceneEndFlag;//���̃V�[�����I�������true
	GameScenes nextScene;//���̃V�[����

	float deltaTime;
	float nowTime;
	float prevTime;

	int colorScreen;
	int DownScaleScreen;
	int gaussScreen;
};

