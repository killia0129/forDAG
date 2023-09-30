#include "SceneManager.h"
#include "Input/Input.h"
#include "TitleScene.h"
#include "PlayScene.h"
#include "ResultScene.h"

SceneManager::SceneManager()
	: currentScene(nullptr)
	, deltaTime(0.0f)
	, time(0)
	,fpsCheckTime(0)
	,fps(0)
	,fpsCounter(0)
{
	Input::GetInstance();
	deltaTime = 0.000001f; // 最初の経過時間は仮に0.000001f秒にしておく
	time = GetNowHiPerformanceCount(); // システム時間を取得しておく
	fpsCheckTime = GetNowHiPerformanceCount();
}

SceneManager::~SceneManager()
{
	ClearScene();
	Input::Terminate();
}

void SceneManager::GameLoop()
{
	while (!ProcessMessage())
	{
#ifdef _DEBUG
		if (Input::IsDown1P(BUTTON_ID_BACK))
		{
			break;
		}
#endif // _DEBUG

		Input::Update();

		auto tag = currentScene->Update(deltaTime);

		ClearDrawScreen();
		clsDx();

#ifdef _DEBUG
		printfDx("deltaTime:%f\n", deltaTime);
		printfDx("FPS:%d\n", fps);
#endif // _DEBUG

		currentScene->Draw();

		ScreenFlip();

		SaveDeltaTime();

		if (tag == TAG_SCENE::TAG_NONE)
		{
			continue;
		}

		ClearScene();
		if (tag == TAG_SCENE::TAG_END)
		{
			break;
		}
		SetNowScene(tag);
	}
	
}

void SceneManager::SetNowScene(const TAG_SCENE& tag)
{
	switch (tag)
	{
	case TAG_SCENE::TAG_TITLE:
		currentScene = new TitleScene();
		break;
	case TAG_SCENE::TAG_PLAY:
		currentScene = new PlayScene();
		break;
	case TAG_SCENE::TAG_RESULT:
		currentScene = new ResultScene();
		break;
	case TAG_SCENE::TAG_NONE:
		break;
	default:
		break;
	}
}

void SceneManager::ClearScene()
{
	if (currentScene != nullptr)
	{
		delete currentScene;
		currentScene = nullptr;
	}
}

void SceneManager::SaveDeltaTime()
{
	// 現在のシステム時間を取得
	currentTime = GetNowHiPerformanceCount();

	// 前回取得した時間からの経過時間を秒に変換してセット
	// ( GetNowHiPerformanceCount で取得できる値はマイクロ秒単位なので 1000000 で割ることで秒単位になる )
	deltaTime = (currentTime - time) / 1000000.0f;

	// 今回取得した時間を保存
	time = currentTime;

	// FPS関係の処理( 1秒経過する間に実行されたメインループの回数を FPS とする )
	fpsCounter++;
	if (currentTime - fpsCheckTime > 1000000)
	{
		fps = fpsCounter;
		fpsCounter = 0;
		fpsCheckTime = currentTime;
	}
}
