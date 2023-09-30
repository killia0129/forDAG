using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ResultTargetMarker : MonoBehaviour
{
    private Vector2 pos;
    private ResultTarget target;

    private bool endFlag = false;
    private Vector2 dis;
    void Start()
    {
        pos = transform.position;
        
        GameObject objT = GameObject.Find("ResultTarget");
        target = objT.GetComponent<ResultTarget>();
    }

    // Update is called once per frame
    void Update()
    {
        if (endFlag==true)
        {
            pos = target.GetPos - dis;
            transform.position = pos;
        }
    }

    public void SetEndFlag()
    {
        endFlag = !endFlag;
    }

    public Vector2 SetDis
    {
        set { dis = value; }
    }
}
