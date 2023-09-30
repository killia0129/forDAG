using System.Collections;
using System.Collections.Generic;
using UnityEngine;


using UnityEngine.UI;


public class Count : MonoBehaviour
{
    public GameObject scoreObj = null;
    private Vector2 pos;
    private Text countText;
    private int count;

    private bool startPlayFlag = false;
    private bool decidedPlayFlag = false;

    // Start is called before the first frame update
    void Start()
    {
        pos = transform.position;
    }

    // Update is called once per frame
    void Update()
    {
        countText = scoreObj.GetComponent<Text>();
        
        if (count < 0)
        {
            count = 0;
        }
        if (count >= 10)
        {
            countText.text = "" + count;
        }
        else
        {
            countText.text = "0" + count;
        }

        if (startPlayFlag==true)
        {
            pos.y -= 0.01f;
            if (pos.y < 4.25f)
            {
                pos.y = 4.25f;
            }
        }
        if (decidedPlayFlag==true)
        {

            if (pos.y < 6.0f)
            {
                pos.y += 0.01f;
            }
        }

        if (count <= 10)
        {
            countText.GetComponent<Text>().color = Color.red;
        }

        this.transform.position = pos;
    }

    public void SetStartFlag()
    {
        startPlayFlag = !startPlayFlag;
    }

    public void SetDecidedFlag()
    {
        decidedPlayFlag = !decidedPlayFlag;
    }

    public int SetTime
    {
        set { count = value; }
    }
}
