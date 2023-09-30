using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayPauseButtonTitle : MonoBehaviour
{
    private Color color;
    private TitleManagerScript manager;
    private float defaultAlfa;

    private bool pauseFlag = false;

    // Start is called before the first frame update
    void Start()
    {
        color = this.GetComponent<SpriteRenderer>().color;
        defaultAlfa = color.a;
        GameObject objM = GameObject.Find("TitleManager");
        manager = objM.GetComponent<TitleManagerScript>();
    }

    // Update is called once per frame
    void Update()
    {
        if (defaultAlfa == 0.0f)
        {
            if (pauseFlag==true)
            {
                color.a = 1.0f;
                this.GetComponent<SpriteRenderer>().color = color;
            }
            else
            {
                color.a = 0.0f;
                this.GetComponent<SpriteRenderer>().color = color;
            }
        }
        else
        {
            if (pauseFlag==true)
            {
                color.a = 0.0f;
                this.GetComponent<SpriteRenderer>().color = color;
            }
            else
            {
                color.a = 1.0f;
                this.GetComponent<SpriteRenderer>().color = color;
            }
        }
    }

    public void SetPauseFase()
    {
        pauseFlag = !pauseFlag;
    }
}
