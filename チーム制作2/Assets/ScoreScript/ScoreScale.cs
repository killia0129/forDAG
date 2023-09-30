using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[CreateAssetMenu(menuName = "データ/CreateScoreScaleData")]
public class ScoreScale : ScriptableObject
{ 
    [SerializeField]
    [Header("ゴールのスコア")]
    private float m_SetGoalScore;
    [SerializeField]
    [Header("コインのスコア")]
    private float m_SetCoinScore;
    [SerializeField]
    [Header("プレイヤーキルしたときのスコア")]
    private float m_SetPlayerKillScore;
    public float m_GoalScore { get => m_SetGoalScore; }

    public float m_CoinScore { get => m_SetCoinScore; }

    public float m_PlayerKillScore { get => m_SetPlayerKillScore; }
}
