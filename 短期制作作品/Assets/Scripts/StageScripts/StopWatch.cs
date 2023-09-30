using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class StopWatch : MonoBehaviour
{
    Vector2 pos;

    private bool startFlag = false;
    private bool decidedFlag = false;
    // Start is called before the first frame update
    void Start()
    {
        pos = this.transform.position;
    }

    // Update is called once per frame
    void Update()
    {
        if (startFlag==true)
        {
            pos.y -= 0.01f;
            if (pos.y < 4.5f)
            {
                pos.y = 4.5f;
            }
        }
        if (decidedFlag==true)
        {

            if (pos.y < 6.0f)
            {
                pos.y += 0.01f;
            }
        }

        this.transform.position = pos;
    }

    public void SetStartFlag()
    {
        startFlag = !startFlag;
    }

    public void SetDecidedFlag()
    {
        decidedFlag = !decidedFlag;
    }
}
