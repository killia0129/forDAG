using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraManager : MonoBehaviour
{
    private Vector3 pos;
    private float size = 1.0f;
    [SerializeField] private float maxTime = 2.0f;
    private float time;

    [SerializeField]private bool isEnd = false;

    private bool playFlag = false;

    // Start is called before the first frame update
    void Start()
    {
        pos = new Vector3(0.0f, -2.0f, -10.0f);
    }

    // Update is called once per frame
    void Update()
    {
        if (playFlag==true)
        {
            size = 4.0f * (time / maxTime) + 1.0f;
            pos.y = 2.0f * (time / maxTime) - 2.0f;
            time += Time.deltaTime;

            if (time > maxTime)
            {
                pos = new Vector3(0.0f, 0.0f, -10.0f);
                size = 5.0f;
                isEnd = true;
            }
            this.transform.position = pos;
            this.GetComponent<Camera>().orthographicSize = size;
        }

    }

    public bool IsEnd
    {
        get{ return isEnd; }
    }

    public void SetPlayFlag()
    {
        playFlag = !playFlag;
    }
}
