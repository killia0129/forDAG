using System.Collections;
using System.Collections.Generic;
using UnityEngine;

using UnityEngine.UI;
using System.IO;

public class ScoreText : MonoBehaviour
{
    private int stageNum;

    [SerializeField] GameObject scoreObj = null;
    private Vector2 pos;
    private Text scoreText;
    private bool saveFlag = false;
    [SerializeField]private float scoreG = 0.0f;
    private float dis;

    private bool hitFlag;
    private bool endFlag = false;

    private int waitFlame = 0;
    // Start is called before the first frame update
    void Start()
    {
        stageNum = StageNumController.GetStageNum;

        pos = transform.position;
    }

    // Update is called once per frame
    void Update()
    {
        float score = 0.0f;
        scoreText = scoreObj.GetComponent<Text>();
        if (dis < 2.0f)
        {
            score += (1 - (dis / 2.0f)) * 50.0f;
            if (hitFlag == true)
            {
                score += 50.0f;
            }
        }
        scoreText.text = (int)score + "/100";
        scoreG = score;

        if (endFlag==true)
        {
            if (pos.y < 3.0f)
            {
                pos.y += 0.03f;
            }
            transform.position = pos;

            if (saveFlag == false)
            {
                if (waitFlame == 1)
                {
                    int[] stageScore = new int[6];
                    string path = Application.dataPath + "/SaveData/SaveData.txt";
                    using (StreamReader save = new StreamReader(path, System.Text.Encoding.GetEncoding("UTF-8")))
                    {
                        int i = 0;
                        while (save.Peek() != -1 || i < 6)
                        {
                            stageScore[i] = int.Parse(save.ReadLine());
                            i++;
                        }
                    }
                    stageScore[stageNum] = (stageScore[stageNum] > (int)score) ? stageScore[0] : (int)score;
                    using (StreamWriter save = new StreamWriter(path, false, System.Text.Encoding.GetEncoding("UTF-8")))
                    {
                        save.Write(stageScore[0] + "\n" + stageScore[1] + "\n" + stageScore[2] + "\n" + stageScore[3] + "\n" + stageScore[4] + "\n" + stageScore[5]);
                    }

                    saveFlag = true;
                }
                waitFlame++;
            }
        }

    }

    public int GetScore
    {
        get 
        {
            if (saveFlag == true)
            {
                return (int)scoreG;
            }
            else
            {
                return 0;
            }

        }
    }

    public void SetEndFlag()
    {
        endFlag = !endFlag;
    }

    public float SetDis
    {
        set { dis = value; }
    }
    public bool SetHit
    {
        set { hitFlag = value; }
    }
}
