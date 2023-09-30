using System.Collections;
using System.Collections.Generic;
using UnityEngine;

using UnityEngine.UI;

public class SuccessScript : MonoBehaviour
{
    bool successFlag = false;

    // Update is called once per frame
    void Update()
    {
        if(successFlag==true)
        {
            this.GetComponent<Text>().color= new Color(0.0f, 0.0f, 0.0f, 1.0f);
        }
        else
        {
            this.GetComponent<Text>().color = new Color(0.0f, 0.0f, 0.0f, 0.0f);
        }
    }

    public bool SetSuccessFlag
    {
        set { successFlag = value; }
    }
}
