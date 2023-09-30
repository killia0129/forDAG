#include "GameStateStartCountDown.h"
#include "DxLib.h"
#include "Input/Input.h"
#include "Time/StopWatch.h"
#include "UI/CountDownUI.h"
#include "Player/Player.h"
#include "Map/Map.h"
#include "Shark/Shark.h"

GameStateStartCountDown::GameStateStartCountDown(ChangeStateMediator changeStateMediator, GameStateMachine* gameStateMachine, InitializeData initData)
	: GameStateBase(changeStateMediator, gameStateMachine, initData)
{
}

void GameStateStartCountDown::OnEnter()
{
	initData.stopWatch->StartCount();
}

void GameStateStartCountDown::OnUpdate(float deltaTime)
{
	if (Input::IsDown1P(BUTTON_ID_START))
	{
		ChangeState(GameStateType::PlayerRound);
	}
	initData.stopWatch->Update();
	if (initData.stopWatch->GetSeconds() > 4.0)
	{
		ChangeState(GameStateType::PlayerRound);
	}

	initData.countDownUI->Update(initData.stopWatch->GetSeconds());
}

void GameStateStartCountDown::OnDraw()
{
#ifdef _DEBUG
	printfDx("State:StartCountDown\n");
	printfDx("Count:%f", initData.stopWatch->GetSeconds());
#endif // _DEBUG
	initData.map->DrawBeach();
	initData.player->Draw();
	initData.shark->Draw();
	initData.countDownUI->Draw();
}

void GameStateStartCountDown::OnExit()
{
	initData.stopWatch->StopCount();
	initData.stopWatch->ResetCount();

	initData.countDownUI->Terminate();
}
