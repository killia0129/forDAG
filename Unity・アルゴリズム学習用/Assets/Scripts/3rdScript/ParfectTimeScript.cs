using System.Collections;
using System.Collections.Generic;
using UnityEngine;

using UnityEngine.UI;

public class ParfectTimeScript : MonoBehaviour
{
    [SerializeField] private GameObject textObj = null;
    private Text text;
    int parfectTime;

    

    // Update is called once per frame
    void Update()
    {
        text = textObj.GetComponent<Text>();
        text.text = parfectTime + "•b";
    }

    public int SetParfectTime
    {
        set { parfectTime = value; }
    }
}
