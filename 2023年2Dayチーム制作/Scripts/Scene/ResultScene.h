#pragma once
#include "Scene.h"

/// <summary>
/// リザルトシーン
/// </summary>
class ResultScene : public Scene
{
public:
	ResultScene();
	~ResultScene() override;

	TAG_SCENE Update(float deltaTime) override;
	void Draw() override;

private:
};
