using System.Collections;
using System.Collections.Generic;
using UnityEngine;


/// <summary>
/// プレイヤー１人１人のスコアを記録する
/// </summary>
public class PlayerScore : MonoBehaviour
{
    PlayerScoreStruct m_ScoreStruct;

    /// <summary>
    /// スコアの更新
    /// </summary>
    /// <param name="getNowRoundScore"></param>
    public void UpdateScore(PlayerScoreStruct getNowRoundScore)
    {
        m_ScoreStruct.m_GoalScore += getNowRoundScore.m_GoalScore;
        m_ScoreStruct.m_CoinScore += getNowRoundScore.m_CoinScore;
        m_ScoreStruct.m_PlayerKillScore += getNowRoundScore.m_PlayerKillScore;
    }
    /// <summary>
    /// スコアの合計値を出す
    /// </summary>
    /// <returns></returns>
    public float GetTotalScore()
    {
        return m_ScoreStruct.m_CoinScore + m_ScoreStruct.m_GoalScore + m_ScoreStruct.m_PlayerKillScore;
    }

}
