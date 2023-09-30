using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
public class RoundUpdater : MonoBehaviour
{
    [SerializeField] [Header("現在のroundの表記してあるテキスト")] private Text m_NowText;
    [SerializeField] [Header("最大のroundの表記してあるテキスト")] private Text m_MaxText;
    private int m_RoundMax;
    private int m_NowRoundNum = 1;
    /// <summary>
    /// ラウンドの更新
    /// </summary>
    public void OnCountRound()
    {
        m_NowRoundNum++;
        m_NowText.text = m_NowRoundNum.ToString();
    }
    /// <summary>
    /// 最大ラウンドが終了したか
    /// </summary>
    /// <returns></returns>
    public bool IsMainEnd()
    {
        return m_NowRoundNum == m_RoundMax;
    }
    /// <summary>
    /// 初期化
    /// </summary>
    /// <param name="_RoundMax"></param>
    public void OnInit(int _RoundMax)
    {
        m_NowText.text = m_NowRoundNum.ToString();
        m_RoundMax = _RoundMax;
        m_MaxText.text = m_RoundMax.ToString();
    }
}
