#pragma once
#include "GameStateBase.h"

/// <summary>
/// ゲームステート：サメが飛んでいる時
/// </summary>
class GameStateSharkFly : public GameStateBase
{
public:
	GameStateSharkFly(ChangeStateMediator changeStateMediator, GameStateMachine* gameStateMachine, InitializeData initData);
	
    /// <summary>
    /// ステートを開始した時に呼ばれる
    /// </summary>
    void OnEnter() override;

    /// <summary>
    /// 毎フレーム呼ばれる更新
    /// </summary>
    void OnUpdate(float deltaTime) override;

    /// <summary>
    /// 毎フレーム呼ばれる描画
    /// </summary>
    void OnDraw() override;

    /// <summary>
    /// ステートを終了した時に呼ばれる
    /// </summary>
    void OnExit() override;
};