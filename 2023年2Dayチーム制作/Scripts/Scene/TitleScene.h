#pragma once
#include <vector>
#include "Scene.h"

/// <summary>
/// タイトルシーン
/// </summary>
class TitleScene : public Scene
{
public:
	TitleScene(); // コンストラクタ
	~TitleScene() override; // デストラクタ

	TAG_SCENE Update(float deltaTime) override; // 更新
	void Draw() override; // 描画
private:
};