using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ScoreBarDisplayer : MonoBehaviour
{
    [SerializeField] [Header("スコアを集計する奴")] private ScoreTotaling m_ScoreTotaling;
    [SerializeField] [Header("1pのスコアグラフ")] private ScoreBar m_ScoreBar1;
    [SerializeField] [Header("2pのスコアグラフ")] private ScoreBar m_ScoreBar2;
    [SerializeField] private NowRoundScore m_NowRoundScoreP1;
    [SerializeField] private NowRoundScore m_NowRoundScoreP2;
    [SerializeField] [Header("スコアを表示するときに鳴る音4つめはスコアが0のときに鳴る")] private List<AudioClip> m_AudioList = new List<AudioClip>();
    [SerializeField] private float m_DisplayTime;
    private AudioSource m_Audio;// 音が複数なると危険なのでここに実装
    private const int m_ScoreKind = 3;
    private bool m_IsDisplayEnd = false;
    private void Start()
    {
        m_Audio = gameObject.GetComponent<AudioSource>();
    }
    /// <summary>
    /// 音を鳴らして表示
    /// </summary>
    /// <param name="score1"></param>
    /// <param name="score2"></param>
    /// <param name="scoreKind"></param>
    /// <param name="SE"></param>
    private void DisplayScore(float score1,float score2,int scoreKind,AudioClip SE)
    {
        m_ScoreBar1.DisplayScore(score1, scoreKind);
        m_ScoreBar2.DisplayScore(score2, scoreKind);
        m_Audio.PlayOneShot(SE);
    }
    /// <summary>
    /// スコアバーを表示させる
    /// </summary>
    /// <returns></returns>
    IEnumerator UpdateScoreBar()
    {
        m_IsDisplayEnd = false;
        m_NowRoundScoreP1.SetPlaeyerKillScore(m_NowRoundScoreP2.NowRoundDie());
        m_NowRoundScoreP2.SetPlaeyerKillScore(m_NowRoundScoreP1.NowRoundDie());
        PlayerScoreStruct p1Struct = m_NowRoundScoreP1.GetNowRoundScore();
        PlayerScoreStruct p2Struct = m_NowRoundScoreP2.GetNowRoundScore();
        m_ScoreTotaling.UpdatePlayersScore(p1Struct, p2Struct);

        yield return new WaitForSeconds(m_DisplayTime);
        for (int i = 0; i < m_ScoreKind; i++)
        {
            switch (i)
            {
                case 0://ゴールスコアの表示
                    if (p1Struct.m_GoalScore + p2Struct.m_GoalScore != 0)
                    {
                        DisplayScore(p1Struct.m_GoalScore, p2Struct.m_GoalScore, i, m_AudioList[i]);
                        yield return new WaitForSeconds(m_DisplayTime);
                    }
                    break;
                case 1://コインスコアの表示
                    if (p1Struct.m_CoinScore + p2Struct.m_CoinScore != 0)
                    {
                        DisplayScore(p1Struct.m_CoinScore, p2Struct.m_CoinScore, i, m_AudioList[i]);
                        yield return new WaitForSeconds(m_DisplayTime);
                    }
                    break;
                case 2://プレイヤーキルスコアの表示
                    if (p1Struct.m_PlayerKillScore + p2Struct.m_PlayerKillScore != 0)
                    {
                        DisplayScore(p1Struct.m_PlayerKillScore, p2Struct.m_PlayerKillScore, i, m_AudioList[i]);
                        yield return new WaitForSeconds(m_DisplayTime);
                    }
                    break;
            }
        }

        m_IsDisplayEnd = true;
        yield break;
    }
    
    /// <summary>
    /// 表示し終えたかどうか
    /// </summary>
    /// <returns></returns>
    public bool IsDisplayEnd()
    {
        return m_IsDisplayEnd;
    }

}
