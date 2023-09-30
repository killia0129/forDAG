#include "GameStates.h"
#include "GameStateTitle.h"
#include "GameStateStartCountDown.h"
#include "GameStatePlayerRound.h"
#include "GameStateSharkShoot.h"
#include "GameStateSharkFly.h"
#include "GameStateSharkLandsOnWater.h"
#include "GameStateResult.h"

GameStates::GameStates(ChangeStateMediator changeStateMediator, GameStateMachine* gameStateMachine, InitializeData initData)
    : gameStates(NULL)
    , gameStateTitle(nullptr)
    , gameStateStartCountDown(nullptr)
    , gameStatePlayerRound(nullptr)
    , gameStateSharkShoot(nullptr)
    , gameStateSharkFly(nullptr)
    , gameStateResult(nullptr)
{
    gameStateTitle = new GameStateTitle(changeStateMediator, gameStateMachine, initData);
    gameStateStartCountDown = new GameStateStartCountDown(changeStateMediator, gameStateMachine, initData);
    gameStatePlayerRound = new GameStatePlayerRound(changeStateMediator, gameStateMachine, initData);
    gameStateSharkShoot = new GameStateSharkShoot(changeStateMediator, gameStateMachine, initData);
    gameStateSharkFly = new GameStateSharkFly(changeStateMediator, gameStateMachine, initData);
    gameStateResult = new GameStateResult(changeStateMediator, gameStateMachine, initData);
    gameStateSharkLandsOnWater = new GameStateSharkLandsOnWater(changeStateMediator, gameStateMachine, initData);
    gameStates.push_back(gameStateTitle);
    gameStates.push_back(gameStateStartCountDown);
    gameStates.push_back(gameStatePlayerRound);
    gameStates.push_back(gameStateSharkShoot);
    gameStates.push_back(gameStateSharkFly);
    gameStates.push_back(gameStateSharkLandsOnWater);
    gameStates.push_back(gameStateResult);
}

GameStates::~GameStates()
{
    delete gameStateTitle;
    delete gameStateStartCountDown;
    delete gameStatePlayerRound;
    delete gameStateSharkShoot;
    delete gameStateSharkFly;
    delete gameStateSharkLandsOnWater;
    delete gameStateResult;
    gameStates.clear();
}

GameStateBase* GameStates::GetState(const GameStateType type)
{
    return gameStates[(int)type];
}
