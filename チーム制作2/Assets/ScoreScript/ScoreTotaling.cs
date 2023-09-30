using System.Collections;
using System.Collections.Generic;
using UnityEngine;
/// <summary>
/// 各プレイヤーの合計値を出したりスコアの倍率を反映
/// </summary>
public class ScoreTotaling : MonoBehaviour
{
    [SerializeField] [Header("1pのスコア")] private PlayerScore m_PlayerScore1;
    [SerializeField] [Header("2pのスコア")] private PlayerScore m_PlayerScore2;
    /// <summary>
    /// 1p2pのスコアを更新
    /// </summary>
    /// <param name="_P1Score">このラウンドで得た1pのスコア</param>
    /// <param name="_P2Score">このラウンドで得た2pのスコア</param>
    public void UpdatePlayersScore(PlayerScoreStruct _P1Score,PlayerScoreStruct _P2Score)
    {
        m_PlayerScore1.UpdateScore(_P1Score);
        m_PlayerScore2.UpdateScore(_P2Score);
    }
    /// <summary>
    /// ゲームを終わらせた人がいるか
    /// </summary>
    /// <param name="champScore"></param>
    /// <returns></returns>
    public bool GetIsExistWinner(float champScore)
    {
        Debug.Log(m_PlayerScore2.GetTotalScore());
        if (m_PlayerScore1.GetTotalScore() > champScore)
        {
            return true;
        }
        //以下、後で変える必要あり
        else if (m_PlayerScore2.GetTotalScore() > champScore)
        {
            return true;
        }
        return false;
    }
    /// <summary>
    /// 1pは2pよりスコアが多いか？
    /// </summary>
    /// <returns></returns>
    public bool GetIs1PWin()
    {
        if (m_PlayerScore1.GetTotalScore() > m_PlayerScore2.GetTotalScore()) 
        {
            return true;
        }
        return false;
    }
}
