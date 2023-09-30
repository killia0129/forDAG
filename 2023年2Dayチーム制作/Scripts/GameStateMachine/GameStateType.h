#pragma once

/// <summary>
/// ゲームシーンのステートの種類
/// </summary>
enum GameStateType
{
    Title, // タイトルステート
    StartCountDown, // 始まるまでのカウントダウンのステート
    PlayerRound, // プレイヤーを回転させるステート
    SharkShoot, // サメを投げた時のステート
    SharkFly, // サメが飛んでいる時のステート
    SharkLandsOnWater, // サメが着水した時のステート
    Result, // リザルトのステート
    None
};