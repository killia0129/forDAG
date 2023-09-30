using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FadeTitleScript : MonoBehaviour
{
    private Color color = new Color(0.0f, 0.0f, 0.0f, 0.0f);
    private float alfa = 0.0f;

    private bool fadeFlag = false;
    [SerializeField]private bool isEnd = false;
    void Start()
    {
        this.GetComponent<SpriteRenderer>().color = color;
    }

    
    void Update()
    {
        if(fadeFlag==true)
        {
            this.GetComponent<SpriteRenderer>().color = new Color(0.0f, 0.0f, 0.0f, alfa);
            alfa += Time.deltaTime;
            if(alfa>1.0f)
            {
                isEnd = true;
            }
        }
    }

    public void SetFadeFlag()
    {
        fadeFlag = !fadeFlag;
    }

    public bool IsEnd
    {
        get { return isEnd; }
    }
}
