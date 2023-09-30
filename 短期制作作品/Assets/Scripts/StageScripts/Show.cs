using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Show : MonoBehaviour
{
    private Color color;

    private bool showFlag = false;
    // Start is called before the first frame update
    void Start()
    {
        color = this.GetComponent<SpriteRenderer>().color;
        
    }

    // Update is called once per frame
    void Update()
    {
        if (showFlag==true)
        {
            color.a = 1.0f;
        }
        else
        {
            color.a = 0.0f;
        }
        this.GetComponent<SpriteRenderer>().color = color;
    }

    public void SetShowFlag()
    {
        showFlag = !showFlag;
    }
}
