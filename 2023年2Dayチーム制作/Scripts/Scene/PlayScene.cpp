#include "PlayScene.h"
#include "DxLib.h"
#include "Input/Input.h"
#include "GameStateMachine/GameStateMachine.h"
#include "GameStateMachine/GameStateBase.h"
#include "Shark/Shark.h"
#include "Player/Player.h"
#include "Map/Map.h"
#include "Time/StopWatch.h"
#include "UI/CountDownUI.h"
#include "UI/PressAUI.h"
#include "UI/ResultScoreUI.h"
#include "ScoreDraw.h"
#include "UI.h"

/// <summary>
/// コンストラクタ
/// </summary>
PlayScene::PlayScene()
	: gameStateMachine(nullptr)
	, shark(nullptr)
	, player(nullptr)
	, map(nullptr)
	, stopWatch(nullptr)
	, countDownUI(nullptr)
	, pressAToStartUI(nullptr)
	, resultSocreUI(nullptr)
	, scoreDraw(nullptr)
	, ui(nullptr)
{
	shark = new Shark();
	player = new Player();
	map = new Map();
	stopWatch = new StopWatch();
	stopWatch->Initialize();
	countDownUI = new CountDownUI({SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2});
	pressAToStartUI = new PressAUI("Textures/UI/PressAToStart.png", "Textures/UI/PressAToTitle.png", { SCREEN_WIDTH / 2 , SCREEN_HEIGHT * 2 / 3});
	resultSocreUI = new ResultScoreUI({ SCREEN_WIDTH / 2 , SCREEN_HEIGHT / 2 });
	scoreDraw = new ScoreDraw();
	ui = new UI();
	InitializeData initData;
	initData.shark = shark;
	initData.player = player;
	initData.map = map;
	initData.stopWatch = stopWatch;
	initData.countDownUI = countDownUI;
	initData.pressAUI = pressAToStartUI;
	initData.resultScoreUI = resultSocreUI;
	initData.scoreDraw = scoreDraw;
	initData.ui = ui;
	gameStateMachine = new GameStateMachine(initData);
}

/// <summary>
/// デストラクタ
/// </summary>
PlayScene::~PlayScene()
{
	delete gameStateMachine;
	delete shark;
	delete player;
	delete map;
	delete stopWatch;
	delete countDownUI;
	delete pressAToStartUI;
	delete resultSocreUI;
}

/// <summary>
/// 更新
/// </summary>
TAG_SCENE PlayScene::Update(float deltaTime)
{
	// 終了
	if (Input::IsDown1P(BUTTON_ID_BACK))
	{
		return TAG_SCENE::TAG_END;
	}

	gameStateMachine->OnUpdate(deltaTime);

	// 次のループもこのシーンを継続
	return TAG_SCENE::TAG_NONE;
}

/// <summary>
/// 描画
/// </summary>
void PlayScene::Draw()
{
#ifdef _DEBUG
	printfDx("PlayScene\n");
#endif // _DEBUG
	gameStateMachine->OnDraw();
}