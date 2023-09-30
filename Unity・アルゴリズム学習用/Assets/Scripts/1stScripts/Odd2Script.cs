using System.Collections;
using System.Collections.Generic;
using UnityEngine;

using UnityEngine.UI;

public class Odd2Script : MonoBehaviour
{
    [SerializeField] private GameObject textObj = null;
    private Text text;
    [SerializeField]private string[] printText = new string[10];
    private string allText;
    int lastNum;
    bool printFlag = false;

    // Update is called once per frame
    void Update()
    {
        text = textObj.GetComponent<Text>();
        if (!printFlag)
        {
            for (int i = 0; i < 20; i++)
            {

                for (int j = 1 + i; j < 201; j++)
                {
                    if (j % 2 == 1)
                    {
                        if (j == i + 1)
                        {
                            printText[i] = "  " + j + " ";
                            lastNum = j;
                        }
                        else
                        {
                            if (lastNum + 20 == j)
                            {
                                if (j < 10)
                                {
                                    printText[i] = printText[i] + "  " + j + " ";
                                }
                                else if (j < 100)
                                {
                                    printText[i] = printText[i] + " " + j + " ";
                                }
                                else
                                {
                                    printText[i] = printText[i] + j + " ";
                                }
                                lastNum = j;
                            }
                        }
                    }
                }
                allText = allText + printText[i] + "\n";

            }
            printFlag = true;
        }

        text.text = allText;
    }
}
