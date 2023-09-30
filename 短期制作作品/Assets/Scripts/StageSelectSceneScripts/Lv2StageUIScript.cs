using System.Collections;
using System.Collections.Generic;
using UnityEngine;

using UnityEngine.UI;

public class Lv2StageUIScript : MonoBehaviour
{
    //private bool setFlag = false;
    private int stageScore;

    // Update is called once per frame
    void Update()
    {
        //if (setFlag == false)
        {
            Text text = this.GetComponent<Text>();

            if (stageScore >= 70)
            {
                text.color = new Color(0.0f, 0.0f, 0.0f, 1.0f);
            }
            else
            {
                text.color = new Color(0.0f, 0.0f, 0.0f, 0.0f);
            }
        }
    }

    public int SetScore
    {
        set { stageScore = value; }
    }
}
