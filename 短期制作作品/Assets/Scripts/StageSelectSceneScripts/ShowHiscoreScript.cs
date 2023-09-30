using System.Collections;
using System.Collections.Generic;
using UnityEngine;

using UnityEngine.UI;
using Unity.IO;

public class ShowHiscoreScript : MonoBehaviour
{
    [SerializeField] private Text text;
    [SerializeField] private GameObject score;
    private int numScore;
    

    // Update is called once per frame
    void Update()
    {
        text = score.GetComponent<Text>();
        text.text = numScore + "/100";
        if(numScore>=0)
        {
            score.GetComponent<Text>().color = new Color(0.0f, 0.0f, 0.0f, 1.0f);
        }
        else
        {
            score.GetComponent<Text>().color = new Color(0.0f, 0.0f, 0.0f, 0.0f);
        }
    }

    public int SetScore
    {
        set { numScore = value; }
    }
}
