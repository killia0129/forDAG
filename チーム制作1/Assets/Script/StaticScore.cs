using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class StaticScore : MonoBehaviour
{
    const int rankinguNum = 5;
    static float[] ranking_score = { 0, 0, 0, 0, 0 };
    static private int nowGameClearCountScore;
    static private float nowGameFastTime;
    [SerializeField] private GameObject resultScore;
    [SerializeField] private GameObject rankingNumber;

    // Start is called before the first frame update
    void Awake()
    {
    }

    // Update is called once per frame
    void Update()
    {
        ScoreUpdate();
    }

    public void ScoreCheck(int clearCount, float clearTimetotal)
    {
        nowGameClearCountScore = clearCount;
                nowGameFastTime = clearTimetotal/* / (float)clearCount*/;

        for(int i = 0; i < rankinguNum; i++)
        {
            if(nowGameFastTime < ranking_score[i] || ranking_score[i] == 0)
            {
                ranking_score[i] = nowGameFastTime;
            }
        }
    }

    private void ScoreUpdate()
    {
        if(resultScore && rankingNumber)
        {
            resultScore.GetComponent<TMPro.TMP_Text>().SetText("Score:�@" + nowGameClearCountScore.ToString("D3") + "�́@"
            + nowGameFastTime.ToString("N3") + "�b");

            rankingNumber.GetComponent<TMPro.TMP_Text>().SetText("1��:" + ranking_score[0].ToString("N3") + "�b " + "2��:" + ranking_score[1].ToString("N3") + "�b " +
                "3��:" + ranking_score[2].ToString("N3") + "�b " + "4��:" + ranking_score[3].ToString("N3") + "�b " + "5��:" + ranking_score[4].ToString("N3") + "�b ");
                    
        }
    }
}
