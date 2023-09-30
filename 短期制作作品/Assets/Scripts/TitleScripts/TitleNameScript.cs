using System.Collections;
using System.Collections.Generic;
using UnityEngine;


public class TitleNameScript : MonoBehaviour
{
    private Vector2 pos;
    private Vector2 defaultPos;
    private float rad;

    // Start is called before the first frame update
    void Start()
    {
        pos = transform.position;
        defaultPos = pos;
    }

    // Update is called once per frame
    void Update()
    {
        pos.x = Mathf.Sin(rad * Mathf.PI)*0.3f + defaultPos.x;
        pos.y = Mathf.Abs(Mathf.Sin(rad * Mathf.PI))*0.3f + defaultPos.y;

        rad += Time.deltaTime;
        if(rad>2.0f)
        {
            rad = 0.0f;
        }

        transform.position = pos;
    }
}
