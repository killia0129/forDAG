using System.Collections;
using System.Collections.Generic;
using UnityEngine;

using UnityEngine.UI;

public class Manager5th : MonoBehaviour
{
    class Cell
    {
        public int x, y;
    }

    enum FASE
    {
        ON_ACTION,CLEAR
    }

    int[,] nums = new int[3, 3];
    int[,] fontSize = new int[3, 3];
    Cell clickedCell = new Cell();

    [SerializeField]FASE fase = FASE.ON_ACTION;

    [SerializeField]Vector2 clickPos;
    bool clickUpFlag = true;
    bool clickFlag = false;
    string text;

    [SerializeField]InputField input;

    // Start is called before the first frame update
    void Start()
    {
        input = input.GetComponent<InputField>();
    }

    // Update is called once per frame
    void Update()
    {
        if(fase==FASE.ON_ACTION)
        {
            if(clickUpFlag==true)
            {
                if(Input.GetMouseButtonDown(0)==true)
                {
                    clickPos = Input.mousePosition;


                    if(clickPos.x>640.0f&&clickPos.y>650.0f&& clickPos.x < 845.0f && clickPos.y < 860.0f)
                    {
                        clickedCell.x = 0;
                        clickedCell.y = 0;
                        clickFlag = true;
                    }
                    if (clickPos.x > 845.0f && clickPos.y > 650.0f && clickPos.x < 1050.0f && clickPos.y < 860.0f)
                    {
                        clickedCell.x = 1;
                        clickedCell.y = 0;
                        clickFlag = true;
                    }
                    if (clickPos.x > 1050.0f && clickPos.y > 650.0f && clickPos.x < 1255.0f && clickPos.y < 860.0f)
                    {
                        clickedCell.x = 2;
                        clickedCell.y = 0;
                        clickFlag = true;
                    }


                    if (clickPos.x > 640.0f && clickPos.y > 440.0f && clickPos.x < 845.0f && clickPos.y < 650.0f)
                    {
                        clickedCell.x = 0;
                        clickedCell.y = 1;
                        clickFlag = true;
                    }
                    if (clickPos.x > 845.0f && clickPos.y > 440.0f && clickPos.x < 1050.0f && clickPos.y < 650.0f)
                    {
                        clickedCell.x = 1;
                        clickedCell.y = 1;
                        clickFlag = true;
                    }
                    if (clickPos.x > 1050.0f && clickPos.y > 440.0f && clickPos.x < 1255.0f && clickPos.y < 650.0f)
                    {
                        clickedCell.x = 2;
                        clickedCell.y = 1;
                        clickFlag = true;
                    }


                    if (clickPos.x > 640.0f && clickPos.y > 230.0f && clickPos.x < 845.0f && clickPos.y < 440.0f)
                    {
                        clickedCell.x = 0;
                        clickedCell.y = 2;
                        clickFlag = true;
                    }
                    if (clickPos.x > 845.0f && clickPos.y > 230.0f && clickPos.x < 1050.0f && clickPos.y < 440.0f)
                    {
                        clickedCell.x = 1;
                        clickedCell.y = 2;
                        clickFlag = true;
                    }
                    if (clickPos.x > 1050.0f && clickPos.y > 230.0f && clickPos.x < 1255.0f && clickPos.y < 440.0f)
                    {
                        clickedCell.x = 2;
                        clickedCell.y = 2;
                        clickFlag = true;
                    }
                }
            }

            if(Input.GetMouseButtonDown(0)==false)
            {
                clickUpFlag = true;
            }

            if(clickFlag==true)
            {

                int checkSame = 0;

                for(int i=0;i<3;i++)
                {
                    for(int j=0;j<3;j++)
                    {
                        if(int.Parse(text) == nums[j, i])
                        {
                            checkSame++;
                        }
                    }
                }

                if (checkSame == 0)
                {
                    nums[clickedCell.x, clickedCell.y] = int.Parse(text);
                    GameObject obj = GameObject.Find("" + clickedCell.x + "-" + clickedCell.y);
                    obj.GetComponent<Text>().text = text;

                    if (nums[clickedCell.x, clickedCell.y] > 10000)
                    {
                        fontSize[clickedCell.x, clickedCell.y] = 25;
                    }
                    else if (nums[clickedCell.x, clickedCell.y] > 100)
                    {
                        fontSize[clickedCell.x, clickedCell.y] = 50;
                    }
                    else
                    {
                        fontSize[clickedCell.x, clickedCell.y] = 100;
                    }

                    obj.GetComponent<Text>().fontSize = fontSize[clickedCell.x, clickedCell.y];
                }

                clickFlag = false;
            }

            int sum = nums[0, 0] + nums[1, 0] + nums[2, 0];
            int sameLine = 0;

            for (int i=0;i<3;i++)
            {
                int line = 0;
                for(int j=0;j<3;j++)
                {
                    line += nums[j, i];
                }
                if(line==sum)
                {
                    sameLine++;
                }
            }
            if(sameLine==3)
            {
                for (int i = 0; i < 3; i++)
                {
                    int line = 0;
                    for (int j = 0; j < 3; j++)
                    {
                        line += nums[i, j];
                    }
                    if (line == sum)
                    {
                        sameLine++;
                    }
                }
            }
            if(sameLine==6)
            {
                if (nums[0,0]+ nums[1, 1] + nums[2, 2]==sum)
                {
                    sameLine++;
                }
                if (nums[2, 0] + nums[1, 1] + nums[0, 2] == sum)
                {
                    sameLine++;
                }
            }

            if(sameLine==8&&sum!=0)
            {
                clickUpFlag = false;
                fase = FASE.CLEAR;
            }
        }

        if(fase==FASE.CLEAR)
        {
            GameObject.Find("Clear").GetComponent<Text>().color = new Color(0.0f, 0.0f, 0.0f, 1.0f);
            GameObject.Find("ClickToReturn").GetComponent<Text>().color = new Color(0.0f, 0.0f, 0.0f, 1.0f);
            if (clickUpFlag == true)
            {
                if (Input.GetMouseButtonDown(0) == true)
                {
                    for (int i = 0; i < 3; i++)
                    {
                        for (int j = 0; j < 3; j++)
                        {
                            nums[j, i] = 0;
                            fontSize[j, i] = 100;
                            GameObject.Find(j + "-" + i).GetComponent<Text>().text = "";
                        }
                    }
                    clickUpFlag = true;
                    clickFlag = false;
                    fase = FASE.ON_ACTION;
                }
            }
            if (Input.GetMouseButtonDown(0) == false)
            {
                clickUpFlag = true;
            }
        }
        else
        {
            GameObject.Find("Clear").GetComponent<Text>().color = new Color(0.0f, 0.0f, 0.0f, 0.0f);
            GameObject.Find("ClickToReturn").GetComponent<Text>().color = new Color(0.0f, 0.0f, 0.0f, 0.0f);
        }
    }

    public void SetText()
    {
        text = input.text;
    }
}
