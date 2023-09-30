using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class StageCoverStageSelectScript : MonoBehaviour
{
    private bool setFlag = false;
    [SerializeField] private int attachedStage;


    [SerializeField]private int score;
   

    // Update is called once per frameW
    void Update()
    {
        //Debug.Log(manager.GetS1Score);
        //if (setFlag == false)
        {
            if(attachedStage<3)
            {
                if (score >= 70)
                {
                    this.GetComponent<SpriteRenderer>().color = new Color(0.8584906f, 0.8584906f, 0.8584906f, 0.0f);
                }
                else
                {
                    this.GetComponent<SpriteRenderer>().color = new Color(0.8584906f, 0.8584906f, 0.8584906f, 1.0f);
                }
            }
            else
            {
                if (score >= 70)
                {
                    this.GetComponent<SpriteRenderer>().color = new Color(0.2588235f, 1.0f, 1.0f, 0.0f);
                }
                else
                {
                    this.GetComponent<SpriteRenderer>().color = new Color(0.2588235f, 1.0f, 1.0f, 1.0f);
                }
            }
           // setFlag = true;
        }

    }

    public int SetScore
    {
        set { score = value; }
    }
}
