#include "GameStateSharkLandsOnWater.h"
#include "DxLib.h"
#include "Input/Input.h"
#include "Map/Map.h"

GameStateSharkLandsOnWater::GameStateSharkLandsOnWater(ChangeStateMediator changeStateMediator, GameStateMachine* gameStateMachine, InitializeData initData)
	: GameStateBase(changeStateMediator, gameStateMachine, initData)
{
}

void GameStateSharkLandsOnWater::OnEnter()
{
}

void GameStateSharkLandsOnWater::OnUpdate(float deltaTime)
{
	if (Input::IsDown1P(BUTTON_ID_START))
	{
		ChangeState(GameStateType::Result);
	}
	initData.map->SprashUpdate(deltaTime);

	if (initData.map->GetSprashEndFlag())
	{
		ChangeState(GameStateType::Result);
	}
}

void GameStateSharkLandsOnWater::OnDraw()
{
#ifdef _DEBUG
	printfDx("State:SharkLandsOnWater\n");
#endif // _DEBUG
	initData.map->Draw();
	initData.map->DrawWaterSprash();
}

void GameStateSharkLandsOnWater::OnExit()
{
}
