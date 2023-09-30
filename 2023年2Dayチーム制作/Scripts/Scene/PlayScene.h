#pragma once
#include "Scene.h"

/// <summary>
/// プレイシーン
/// </summary>
class PlayScene : public Scene
{
public:
	PlayScene();
	~PlayScene() override;

	TAG_SCENE Update(float deltaTime) override;
	void Draw() override;

private:
	class GameStateMachine* gameStateMachine;
	class Shark* shark;
	class Player* player;
	class Map* map;
	class StopWatch* stopWatch;
	class CountDownUI* countDownUI;
	class PressAUI* pressAToStartUI;
	class ResultScoreUI* resultSocreUI;
	class ScoreDraw* scoreDraw;
	class UI* ui;
};
