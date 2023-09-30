#include "GameStateBase.h"

/// <summary>
/// コンストラクタ
/// </summary>
GameStateBase::GameStateBase(ChangeStateMediator changeStateMediator, GameStateMachine* gameStateMachine, InitializeData initData)
	: changeStateMediator(nullptr)
	, gameStateMachine(nullptr)
	, initData()
{
	this->changeStateMediator = changeStateMediator;
	this->gameStateMachine = gameStateMachine;
	this->initData = initData;
}

/// <summary>
/// デストラクタ
/// </summary>
GameStateBase::~GameStateBase()
{
	changeStateMediator = nullptr;
}

/// <summary>
/// ステートを変更する
/// </summary>
void GameStateBase::ChangeState(GameStateType nextStateType)
{
	(gameStateMachine->*changeStateMediator)(nextStateType);
}
