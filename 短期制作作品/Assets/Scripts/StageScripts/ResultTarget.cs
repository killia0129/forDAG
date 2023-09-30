using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ResultTarget : MonoBehaviour
{
    private Vector2 pos;

    private bool endFlag = false;

    void Start()
    {
        pos = transform.position;
    }


    void Update()
    {
        if (endFlag==true)
        {
            if (pos.y < 0.0f)
            {
                pos.y += 0.03f;
            }

            transform.position = pos;
        }
    }

    public Vector2 GetPos
    {
        get { return pos; }
    }

    public void SetEndFlag()
    {
        endFlag = !endFlag;
    }
}
