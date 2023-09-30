using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ScoreBar : MonoBehaviour
{
    [SerializeField] private float m_BarSizeY;
    [SerializeField] [Header("スコアを表示する棒グラフのsprite")] private GameObject m_BarImg;
    [SerializeField] [Header("スコアの色の種類")] private List<Color> m_ColorList = new List<Color>();

    /// <summary>
    /// スコアをスコアの大きさ分長くして表示して色変えます
    /// </summary>
    /// <param name="score">これが大きいほど横長になる</param>
    /// <param name="color"></param>
    public void DisplayScore(float score,int colorNum)
    {
        GameObject imgObj = Instantiate(m_BarImg);
        imgObj.transform.SetParent(transform);
        imgObj.transform.localScale = new Vector3(score, m_BarSizeY);
        SpriteRenderer image = imgObj.GetComponent<SpriteRenderer>();
        image.color = m_ColorList[colorNum];
    }
}
