#pragma once
#include "Scene.h"
#include "DxLib.h"

/// <summary>
/// シーンマネージャー
/// </summary>
class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void GameLoop();

	void SetNowScene(const TAG_SCENE& tag);
private:
	void ClearScene();
	void SaveDeltaTime();
	Scene* currentScene;

	// デルタタイム
	float deltaTime;
	LONGLONG currentTime;
	LONGLONG time;
	int fps;
	int fpsCounter;
	LONGLONG fpsCheckTime;
};
