using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
/// <summary>
/// スコア表示のパート
/// </summary>
public class ScoreDisplayPart : MonoBehaviour
{

    [SerializeField] [Header("ScoreBarを表示するスクリプト")] private ScoreBarDisplayer m_ScoreBarMana;
    [SerializeField] [Header("優勝するために必要なスコア")] private float m_ChampScore;
    [SerializeField] [Header("スコアを足し合わせる")] private ScoreTotaling m_ScoreTotaling;
    [SerializeField] private InputPlyer1 m_Player1Controller;
    [SerializeField] private GameObject m_ScoreBord;///スコアの棒グラフボード
    [SerializeField] private GoNextScene m_GoNextScene1;//次のシーン
    private bool m_IsResultFirst = false;
    private void Start()
    {
        m_ScoreBord.SetActive(false);
    }

    /// <summary>
    /// 表示始める
    /// </summary>
    public void Run()
    {
        if (!m_IsResultFirst)
        {
            m_IsResultFirst = true;
            m_ScoreBord.SetActive(true);
            m_ScoreBarMana.StartCoroutine("UpdateScoreBar");
        }
    }
    /// <summary>
    /// スコアの表示が終えたか
    /// </summary>
    /// <returns></returns>
    public bool IsDisplayEnd()
    {
        if (m_ScoreBarMana.IsDisplayEnd())
        {
            m_IsResultFirst = false;
            m_ScoreBord.SetActive(false);
            return true;
        }
        return false;
    }
    /// <summary>
    /// どっちかが勝ちましたか
    /// </summary>
    /// <returns></returns>
    public bool GetWin()
    {
        return m_ScoreTotaling.GetIsExistWinner(m_ChampScore);
    }
    /// <summary>
    /// 勝った方のリザルト画面に行く
    /// </summary>
    public void OnNextSceneChange()
    {
        ResultData.m_Player1Win = m_ScoreTotaling.GetIs1PWin();
        m_GoNextScene1.OnRun();
    }
}
