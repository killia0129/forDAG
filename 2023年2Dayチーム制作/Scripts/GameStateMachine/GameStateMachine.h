#pragma once
#include "GameStateType.h"
#include "GameStateInitializeData.h"

/// <summary>
/// ゲーム全体のステートマシン
/// </summary>
class GameStateMachine
{
public:
    GameStateMachine() = delete;
	GameStateMachine(InitializeData initData);
	~GameStateMachine();

    /// <summary>
    /// ステートを変更する
    /// </summary>
    void ChangeState(GameStateType nextStateType);

    /// <summary>
    /// 更新
    /// </summary>
    void OnUpdate(float deltaTime);

    /// <summary>
    /// 描画
    /// </summary>
    void OnDraw();
private:
    class GameStates* gameStates;
    class GameStateBase* currentState;
};