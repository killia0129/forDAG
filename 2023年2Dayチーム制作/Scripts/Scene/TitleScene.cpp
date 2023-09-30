#include "TitleScene.h"
#include "DxLib.h"
#include "Input/Input.h"

/// <summary>
/// コンストラクタ
/// </summary>
TitleScene::TitleScene()
{
	// 処理なし
}

/// <summary>
/// デストラクタ
/// </summary>
TitleScene::~TitleScene()
{
	// 処理なし
}

/// <summary>
/// 更新
/// </summary>
TAG_SCENE TitleScene::Update(float deltaTime)
{
	// 次のシーンへ
	if (Input::IsDown1P(BUTTON_ID_START))
	{
		return TAG_SCENE::TAG_PLAY;
	}

	// 終了
	if (Input::IsDown1P(BUTTON_ID_BACK))
	{
		return TAG_SCENE::TAG_END;
	}

	// 次のループもこのシーンを継続
	return TAG_SCENE::TAG_NONE;
}

/// <summary>
/// 描画
/// </summary>
void TitleScene::Draw()
{
#ifdef _DEBUG
	printfDx("TitleScene\n");
#endif // _DEBUG
}