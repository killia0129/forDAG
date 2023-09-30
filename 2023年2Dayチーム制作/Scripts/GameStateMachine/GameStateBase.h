#pragma once
#include "GameStateType.h"
#include "GameStateMachine.h"
#include "GameStateInitializeData.h"

typedef void (GameStateMachine::*ChangeStateMediator)(GameStateType);

/// <summary>
/// GameStateのBaseクラス
/// </summary>
class GameStateBase
{
public:

    

    GameStateBase() = delete; // デフォルトコンストラクタの使用制限
    /// <summary>
    /// コンストラクタ
    /// </summary>
    GameStateBase(ChangeStateMediator changeStateMediator, GameStateMachine* gameStateMachine, InitializeData initData);

    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~GameStateBase();

    /// <summary>
    /// ステートを開始した時に呼ばれる
    /// </summary>
    virtual void OnEnter() { }

    /// <summary>
    /// 毎フレーム呼ばれる更新
    /// </summary>
    virtual void OnUpdate(float deltaTime) { }

    /// <summary>
    /// 毎フレーム呼ばれる描画
    /// </summary>
    virtual void OnDraw() { }

    /// <summary>
    /// ステートを終了した時に呼ばれる
    /// </summary>
    virtual void OnExit() { }
protected:
    /// <summary>
    /// ステートを変更する
    /// </summary>
    void ChangeState(GameStateType nextStateType);

    InitializeData initData;
private:
    ChangeStateMediator changeStateMediator;
    GameStateMachine* gameStateMachine;
};