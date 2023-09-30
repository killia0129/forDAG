#pragma once

/// <summary>
/// アプリケーション
/// </summary>
class App
{
public:
	App();
	~App();

	void GameLoop();
private:
	class SceneManager* sceneManager;
};