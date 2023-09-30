using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class StartText : MonoBehaviour
{
    private float alfa = 0.0f;
    private Color color;
    private bool StartFlag = false;
    private float time = 0.0f;

    private bool playFlag = false;
    void Start()
    {
        this.GetComponent<SpriteRenderer>().color = new Color(255, 255, 255, alfa);
    }

    // Update is called once per frame
    void Update()
    {
        if (playFlag==true)
        {
            if (StartFlag == false)
            {
                alfa = 1.0f;
                StartFlag = true;
            }
            if (StartFlag == true)
            {
                time += Time.deltaTime;
            }
            if (time > 2.0f)
            {
                alfa = 0.0f;
            }
        }
        else
        {
            alfa = 0.0f;
        }
        this.GetComponent<SpriteRenderer>().color = new Color(255, 255, 255, alfa);
    }

    public void SetActionFlag()
    {
        playFlag = !playFlag;
    }
}
