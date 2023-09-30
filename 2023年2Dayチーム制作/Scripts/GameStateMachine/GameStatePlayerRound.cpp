#include "GameStatePlayerRound.h"
#include "DxLib.h"
#include "Input/Input.h"
#include "Shark/Shark.h"
#include "Player/Player.h"
#include "Map/Map.h"
#include "UI.h"

GameStatePlayerRound::GameStatePlayerRound(ChangeStateMediator changeStateMediator, GameStateMachine* gameStateMachine, InitializeData initData)
	: GameStateBase(changeStateMediator, gameStateMachine, initData)
{
}

void GameStatePlayerRound::OnEnter()
{
}

void GameStatePlayerRound::OnUpdate(float deltaTime)
{
	if (Input::IsDown1P(BUTTON_ID_START))
	{
		ChangeState(GameStateType::SharkShoot);
	}

	initData.player->Update(deltaTime);
	initData.shark->SetplayerAngle(initData.player->GetRotationRad());
	auto isPushButton = initData.player->GetIsPushButton();
	initData.shark->SetisThrow(isPushButton);
	initData.shark->UpdatePlayerRound(deltaTime);
	if (isPushButton)
	{
		ChangeState(GameStateType::SharkShoot);
	}

}

void GameStatePlayerRound::OnDraw()
{
#ifdef _DEBUG
	printfDx("State:PlayerRound\n");
#endif // _DEBUG
	initData.map->DrawBeach();
	initData.player->Draw();
	initData.shark->Draw();
	initData.ui->ControllerDraw(1000,500);
}

void GameStatePlayerRound::OnExit()
{
}
