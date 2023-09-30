#include "GameStateSharkShoot.h"
#include "DxLib.h"
#include "Input/Input.h"
#include "Map/Map.h"
#include "Shark/Shark.h"
#include "Player/Player.h"

GameStateSharkShoot::GameStateSharkShoot(ChangeStateMediator changeStateMediator, GameStateMachine* gameStateMachine, InitializeData initData)
	: GameStateBase(changeStateMediator, gameStateMachine, initData)
{
}

void GameStateSharkShoot::OnEnter()
{
	initData.shark->SetScore(initData.player->GetVelocity());
	initData.map->SetSpeed(initData.player->GetVelocity());
}

void GameStateSharkShoot::OnUpdate(float deltaTime)
{
	if (Input::IsDown1P(BUTTON_ID_START))
	{
		ChangeState(GameStateType::SharkFly);
	}
	initData.shark->UpdateTurn(deltaTime);
	if (initData.shark->GetEndFlag())
	{
		ChangeState(GameStateType::SharkFly);
	}
}

void GameStateSharkShoot::OnDraw()
{
#ifdef _DEBUG
	printfDx("State:SharkShoot\n");
#endif // _DEBUG
	initData.map->DrawBeach();
	initData.shark->Draw();
	initData.player->Draw();
}

void GameStateSharkShoot::OnExit()
{
}
