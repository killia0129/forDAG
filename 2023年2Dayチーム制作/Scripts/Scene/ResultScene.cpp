#include "ResultScene.h"
#include "Input/Input.h"

/// <summary>
/// コンストラクタ
/// </summary>
ResultScene::ResultScene()
{
	// 処理なし
}

/// <summary>
/// デストラクタ
/// </summary>
ResultScene::~ResultScene()
{
	// 処理なし
}

/// <summary>
/// 更新
/// </summary>
TAG_SCENE ResultScene::Update(float deltaTime)
{
	if (Input::IsDown1P(BUTTON_ID_START))
	{
		return TAG_SCENE::TAG_TITLE;
	}
	if (Input::IsDown1P(BUTTON_ID_BACK))
	{
		return TAG_SCENE::TAG_END;
	}

	return TAG_SCENE::TAG_NONE;
}

/// <summary>
/// 描画
/// </summary>
void ResultScene::Draw()
{
#ifdef _DEBUG
	printfDx("GameOverScene\n");
#endif // _DEBUG
}