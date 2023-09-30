using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Sad : MonoBehaviour
{
    Vector2 pos;
    private ScoreText score;

    private bool endFlag = false;
    // Start is called before the first frame update
    void Start()
    {
        GameObject objM = GameObject.Find("Score");
        score = objM.GetComponent<ScoreText>();
        pos = this.transform.position;
    }

    // Update is called once per frame
    void Update()
    {
        if (endFlag==true)
        {
            if (score.GetScore <= 30)
            {
                pos.y -= 0.02f;
                if (pos.y < 1.0f)
                {
                    pos.y = 1.0f;
                }
            }
        }

        this.transform.position = pos;
    }

    public void SetEndFlag()
    {
        endFlag = !endFlag;
    }
}
