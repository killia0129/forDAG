#include "GameStateMachine.h"
#include "GameStates.h"

GameStateMachine::GameStateMachine(InitializeData initData)
	: gameStates(nullptr)
	, currentState(nullptr)
{
	gameStates = new GameStates(&GameStateMachine::ChangeState, this, initData);
	currentState = gameStates->GetState(GameStateType::Title);
	currentState->OnEnter();
}

GameStateMachine::~GameStateMachine()
{
	delete gameStates;
}

void GameStateMachine::ChangeState(GameStateType nextStateType)
{
	auto nextState = gameStates->GetState(nextStateType);
	currentState->OnExit();
	nextState->OnEnter();
	currentState = nextState;
}

void GameStateMachine::OnUpdate(float deltaTime)
{
	currentState->OnUpdate(deltaTime);
}

void GameStateMachine::OnDraw()
{
	currentState->OnDraw();
}
