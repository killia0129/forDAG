#include "GameStateSharkFly.h"
#include "DxLib.h"
#include "Input/Input.h"
#include "Shark/Shark.h"
#include "Map/Map.h"
#include "Player/Player.h"
#include "ScoreDraw.h"

GameStateSharkFly::GameStateSharkFly(ChangeStateMediator changeStateMediator, GameStateMachine* gameStateMachine, InitializeData initData)
	: GameStateBase(changeStateMediator, gameStateMachine, initData)
{
}

void GameStateSharkFly::OnEnter()
{
	initData.shark->InitSharkRound();
	initData.scoreDraw->Initialize();
}

void GameStateSharkFly::OnUpdate(float deltaTime)
{
	if (Input::IsDown1P(BUTTON_ID_START))
	{
		ChangeState(GameStateType::SharkLandsOnWater);
	}
	initData.map->Update(deltaTime);
	initData.shark->UpdateSharkRound(deltaTime);
	initData.scoreDraw->Update();
	if (initData.shark->GetisLandsOnWater())
	{
		ChangeState(GameStateType::SharkLandsOnWater);
	}
}

void GameStateSharkFly::OnDraw()
{
#ifdef _DEBUG
	printfDx("State:SharkFly\n");
#endif // _DEBUG
	initData.map->Draw();
	initData.shark->Draw();
	initData.scoreDraw->Draw();
}

void GameStateSharkFly::OnExit()
{
}
