using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Shuchu : MonoBehaviour
{
    private Color color;
    private float time = 1.0f;

    private bool isEnd = false;

    private bool zoomFlag = false;
    private bool shuchuFlag = false;
    // Start is called before the first frame update
    void Start()
    {
        color = this.GetComponent<SpriteRenderer>().color;
    }

    // Update is called once per frame
    void Update()
    {
        if (zoomFlag==true)
        {
            color.a = 1.0f;
        }
        else
        {
            color.a = 0.0f;
        }

        if (shuchuFlag==true)
        {
            color.a = time * 1.5f;
            time -= Time.deltaTime;
            if (time < 0.0f)
            {
                isEnd = true;
            }
        }

        this.GetComponent<SpriteRenderer>().color = color;
    }

    public bool IsEnd
    {
        get { return isEnd; }
    }

    public void SetZoomFlag()
    {
        zoomFlag = !zoomFlag;
    }

    public void SetShuchuFlag()
    {
        shuchuFlag = !shuchuFlag;
    }
}
