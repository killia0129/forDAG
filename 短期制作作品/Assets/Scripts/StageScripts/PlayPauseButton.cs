using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayPauseButton : MonoBehaviour
{
    private Color color;    [SerializeField]private float defaultAlfa;
    [SerializeField]private bool pauseFlag = false;
    [SerializeField] private bool showFlag = false;

    // Start is called before the first frame update
    void Start()
    {
        this.GetComponent<SpriteRenderer>().color = new Color(1.0f, 1.0f, 1.0f, defaultAlfa);
        color = this.GetComponent<SpriteRenderer>().color;
    }

    // Update is called once per frame
    void Update()
    {
        if(defaultAlfa==0.0f)
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
            if (pauseFlag==true || showFlag==true)
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

    public void SetShowFlag()
    {
        showFlag = !showFlag;
    }

    public void SetPauseFlag()
    {
        pauseFlag = !pauseFlag;
    }
}
