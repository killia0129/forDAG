using System.Collections;
using System.Collections.Generic;
using UnityEngine;

using UnityEngine.UI;


public class Even1Script : MonoBehaviour
{
    [SerializeField] private GameObject textObj = null;
    private Text text;
    private string printText;


    // Update is called once per frame
    void Update()
    {
        text = textObj.GetComponent<Text>();

        for (int i = 1; i < 21; i++)
        {
            if (i % 2 == 0)
            {
                if (i == 2)
                {
                    printText = i + "\n";
                }
                else
                {
                    printText = printText + i + "\n";
                }
            }
            
        }
        text.text = printText;
    }
}
