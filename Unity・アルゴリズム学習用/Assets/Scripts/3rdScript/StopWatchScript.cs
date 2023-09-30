using System.Collections;
using System.Collections.Generic;
using UnityEngine;

using UnityEngine.UI;

public class StopWatchScript : MonoBehaviour
{

    [SerializeField] private GameObject textObj = null;
    private Text text;
    float time;
    bool playFlag = false;
 

    // Update is called once per frame
    void Update()
    {
        text = textObj.GetComponent<Text>();

        
        text.text = time.ToString("F2") + "•b";
        if(time<10.0f)
        {
            text.text = "0" + text.text;
        }
        if(playFlag==true&&time>4.0f)
        {
            this.GetComponent<Text>().color = new Color(0.0f, 0.0f, 0.0f, 0.0f);
        }
        else
        {
            this.GetComponent<Text>().color = new Color(0.0f, 0.0f, 0.0f, 1.0f);
        }
    }

    public void SetActionFlag()
    {
        playFlag = !playFlag;
    }

    public float SetTime
    {
        set { time = value; }
    }
}
