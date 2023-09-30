using System.Collections;
using System.Collections.Generic;
using UnityEngine;

using UnityEngine.UI;

public class PrimeNumberScript : MonoBehaviour
{
    [SerializeField] private GameObject textObj = null;
    private Text text;

    List<int> primeNums = new List<int>();
    bool flag = false;
    int pageNum = 0;
    int size = 0;
    int maxPageNum = 0;
    string printText;

    // Start is called before the first frame update
    void Start()
    {
        for(int i=2;i<5001;i++)
        {
            for(int j=2;j<i;j++)
            {
                if(i%j==0)
                {
                    flag = true;
                    break;
                }
            }
            if(flag==false)
            {
                primeNums.Add(i);
            }
            else
            {
                flag = false;
            }
        }
        size = primeNums.Count;
        maxPageNum = size / (5 * 10) + 1;
    }

    // Update is called once per frame
    void Update()
    {
        text = textObj.GetComponent<Text>();

        int endPage;
        if(50 * (pageNum + 1)>size)
        {
            endPage = size;
        }
        else
        {
            endPage = 50 * (pageNum + 1);
        }
        for(int i=(50*pageNum); i<endPage; i++)
        {
            printText = printText + primeNums[i] + " ";
            if(i%5==4)
            {
                printText = printText + "\n";
            }
        }

        if(Input.GetKeyUp(KeyCode.RightArrow)==true)
        {
            if(pageNum!=maxPageNum-1)
            {
                pageNum++;
            }
        }
        if (Input.GetKeyUp(KeyCode.LeftArrow) == true)
        {
            if (pageNum != 0)
            {
                pageNum--;
            }
        }

        text.text = printText;
        printText = "";
    }
}
