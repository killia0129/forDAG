using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Fade : MonoBehaviour
{
    private Color color = new Color(0.0f, 0.0f, 0.0f, 0.0f);
    private float alfa = 0.0f;
    

    private bool isEnd = false;

    private bool playFlag = false;
    void Start()
    {
        
        this.GetComponent<SpriteRenderer>().color = color;
    }


    void Update()
    {
        if (playFlag==true)
        {
            this.GetComponent<SpriteRenderer>().color = new Color(0.0f, 0.0f, 0.0f, alfa);
            alfa += Time.deltaTime;
            if (alfa > 1.0f)
            {
                isEnd = true;
            }
        }
    }

    public bool IsEnd
    {
        get { return isEnd; }
    }

    public void SetFadeFlag()
    {
        playFlag = !playFlag;
    }
}
