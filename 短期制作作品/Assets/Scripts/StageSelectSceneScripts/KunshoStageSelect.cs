using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class KunshoStageSelect : MonoBehaviour
{
    private Color color;

    private int score;
    // Start is called before the first frame update
    void Start()
    {
        color = new Color(1.0f, 1.0f, 1.0f, 0.0f);
    }

    // Update is called once per frame
    void Update()
    {
        if (score>=90)
        {
            color= new Color(1.0f, 1.0f, 1.0f, 1.0f);
        }
        else
        {
            color= new Color(1.0f, 1.0f, 1.0f, 0.0f);
        }
        this.GetComponent<SpriteRenderer>().color = color;
    }

    public int SetScore
    {
        set { score = value; }
    }
}
