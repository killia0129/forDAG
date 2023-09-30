using System.Collections;
using System.Collections.Generic;
using UnityEngine;

using UnityEngine.UI;

public class MeiroScript : MonoBehaviour
{
    const int WALL = 1;
    const int ROAD = 0;
    const int WIDTH = 11;
    const int HEIGHT = 11;

    class POS
    {
        public int x, y;
    }

    enum DIRECTION
    {
        UP = 0, RIGHT = 1, DOWN = 2, LEFT = 3
    }

    enum FaseName
    {
        START, ON_ACTION, CLEAR
    }

    int[,] Map = new int[11, 11];

    List<POS> canStartPos = new List<POS>();

    [SerializeField]FaseName fase = FaseName.START;
    FaseName nextFase = FaseName.START;

    bool faseChangeFlag = false;
    [SerializeField]bool setMapFlag = false;


    bool keyUpFlag = true;

    POS start;
    POS goal;
    POS playerPos;

    // Start is called before the first frame update
    void Start()
    {

    }

    // Update is called once per frame
    void Update()
    {


        if (fase == FaseName.START)
        {
            if (setMapFlag == false)
            {
                GameObject obj;
                SetMap();
                Dig(1, 1);
                for (int x = 0; x < WIDTH; x++)
                {
                    for (int y = 0; y < HEIGHT; y++)
                    {
                        if (x == 0 || y == 0 || x == WIDTH - 1 || y == HEIGHT - 1)
                        {
                            Map[x, y] = WALL;
                        }
                        if (Map[x,y]==ROAD)
                        {
                            obj = GameObject.Find(x + "-" + y);
                            obj.GetComponent<SpriteRenderer>().color = new Color(0.9f, 0.9f, 0.9f, 1.0f);
                        }
                        else
                        {
                            obj = GameObject.Find(x + "-" + y);
                            obj.GetComponent<SpriteRenderer>().color = new Color(0.1f, 0.1f, 0.1f, 1.0f);
                        }
                    }

                }

                SetStartAndGoal();
                playerPos = start;
                GameObject objP = GameObject.Find("Player");
                GameObject objM = GameObject.Find(playerPos.x + "-" + playerPos.y);
                objP.transform.position = objM.transform.position;


                setMapFlag = true;
            }

            GameObject objS = GameObject.Find("Start");
            objS.GetComponent<Text>().color = new Color(0.0f, 0.0f, 0.0f, 1.0f);

            if (Input.GetKeyDown(KeyCode.Space)==true)
            {
                faseChangeFlag = true;
                nextFase = FaseName.ON_ACTION;
            }
        }
        else
        {
            GameObject objS = GameObject.Find("Start");
            objS.GetComponent<Text>().color = new Color(0.0f, 0.0f, 0.0f, 0.0f);
        }

        if(fase==FaseName.ON_ACTION)
        {
            

            if(keyUpFlag==true)
            {
                if(Input.GetKeyDown(KeyCode.UpArrow)==true)
                {
                    if (Map[playerPos.x,playerPos.y-1]==ROAD)
                    {
                        playerPos.y -= 1;
                    }
                }
                if (Input.GetKeyDown(KeyCode.DownArrow) == true)
                {
                    if (Map[playerPos.x, playerPos.y + 1] == ROAD)
                    {
                        playerPos.y += 1;
                    }
                }
                if (Input.GetKeyDown(KeyCode.RightArrow) == true)
                {
                    if (Map[playerPos.x + 1, playerPos.y] == ROAD)
                    {
                        playerPos.x += 1;
                    }
                }
                if (Input.GetKeyDown(KeyCode.LeftArrow) == true)
                {
                    if (Map[playerPos.x - 1, playerPos.y] == ROAD)
                    {
                        playerPos.x -= 1;
                    }
                }
            }

            if(playerPos.x==goal.x&& playerPos.y == goal.y)
            {
                faseChangeFlag = true;
                nextFase = FaseName.CLEAR;
            }
            GameObject objP = GameObject.Find("Player");
            GameObject objM = GameObject.Find(playerPos.x + "-" + playerPos.y);
            objP.transform.position = objM.transform.position;

        }

        if(fase==FaseName.CLEAR)
        {
            setMapFlag = false;

            GameObject obj = GameObject.Find("Clear");
            obj.GetComponent<Text>().color = new Color(0.0f, 0.0f, 0.0f, 1.0f);
            obj = GameObject.Find("Return");
            obj.GetComponent<Text>().color = new Color(0.0f, 0.0f, 0.0f, 1.0f);

            if (Input.GetKeyDown(KeyCode.Space) == true)
            {
                faseChangeFlag = true;
                nextFase = FaseName.START;
            }

        }
        else
        {
            GameObject obj = GameObject.Find("Clear");
            obj.GetComponent<Text>().color = new Color(0.0f, 0.0f, 0.0f, 0.0f);
            obj = GameObject.Find("Return");
            obj.GetComponent<Text>().color = new Color(0.0f, 0.0f, 0.0f, 0.0f);
        }
        

        if(faseChangeFlag==true)
        {
            fase = nextFase;
            faseChangeFlag = false;
        }
    }

    void Dig(int x, int y)
    {
        while (true)
        {
            List<DIRECTION> direction = new List<DIRECTION>();
            if (Map[x, y - 1] == WALL && Map[x, y - 2] == WALL)
            {
                direction.Add(DIRECTION.UP);
            }
            if (Map[x, y + 1] == WALL && Map[x, y + 2] == WALL)
            {
                direction.Add(DIRECTION.DOWN);
            }
            if (Map[x - 1, y] == WALL && Map[x - 2, y] == WALL)
            {
                direction.Add(DIRECTION.LEFT);
            }
            if (Map[x + 1, y] == WALL && Map[x + 2, y] == WALL)
            {
                direction.Add(DIRECTION.RIGHT);
            }

            if (direction.Count == 0)
            {
                break;
            }

            SetRoad(x, y);

            int direIndex = Random.Range(0, direction.Count);

            switch (direction[direIndex])
            {
                case DIRECTION.UP:
                    SetRoad(x, y - 1);
                    SetRoad(x, y - 2);
                    break;

                case DIRECTION.DOWN:
                    SetRoad(x, y + 1);
                    SetRoad(x, y + 2);
                    break;

                case DIRECTION.LEFT:
                    SetRoad(x - 1, y);
                    SetRoad(x - 2, y);
                    break;

                case DIRECTION.RIGHT:

                    SetRoad(x + 1, y);
                    SetRoad(x + 2, y);
                    break;

                default:
                    break;
            }
        }

        POS pos = GetStartPos();

        if (pos != null)
        {
            Dig(pos.x, pos.y);
        }

    }

    void SetRoad(int x, int y)
    {
        Map[x, y] = ROAD;
        if (x % 2 == 1 && y % 2 == 1)
        {
            canStartPos.Add(new POS() { x = x, y = y });
        }
    }

    POS GetStartPos()
    {
        if (canStartPos.Count == 0)
        {
            return null;
        }
        int index = Random.Range(0, canStartPos.Count);
        POS returnPos = canStartPos[index];
        canStartPos.RemoveAt(index);

        return returnPos;
    }

    void SetMap()
    {
        for (int x = 0; x < WIDTH; x++)
        {
            for (int y = 0; y < HEIGHT; y++)
            {
                if (x == 0 || y == 0 || x == WIDTH - 1 || y == HEIGHT - 1)
                {
                    Map[x, y] = ROAD;
                   
                }
                else
                {
                    Map[x, y] = WALL;
                    
                }
            }

        }
    }

    void SetStartAndGoal()
    {
        List<POS> list = new List<POS>();
        for(int y=1; y<HEIGHT-1;y++)
        {
            for(int x=1;x<WIDTH-1;x++)
            {
                if (Map[x,y]==ROAD)
                {
                    int wallNum = 0;
                    if (Map[x - 1,y]==WALL)
                    {
                        wallNum++;
                    }
                    if (Map[x + 1, y] == WALL)
                    {
                        wallNum++;
                    }
                    if (Map[x, y - 1] == WALL)
                    {
                        wallNum++;
                    }
                    if (Map[x, y + 1] == WALL)
                    {
                        wallNum++;
                    }
                    if(wallNum==3)
                    {
                        POS newPos = new POS();
                        newPos.x = x;
                        newPos.y = y;
                        list.Add(newPos);
                    }
                }
            }
        }


        float maxDis = 0.0f;
        POS pos1 = new POS();
        POS pos2 = new POS();
        for (int i=0;i<list.Count;i++)
        {
            for(int j=i+1;j<list.Count;j++)
            {
                float dis;
                dis = Mathf.Sqrt(Mathf.Pow((float)(list[i].x - list[j].x), 2.0f) + Mathf.Pow((float)(list[i].y - list[j].y), 2.0f));
                if(dis>maxDis)
                {
                    maxDis = dis;
                    pos1 = list[i];
                    pos2 = list[j];
                }
            }
        }

        start = pos1;
        goal = pos2;


        GameObject obj = GameObject.Find(start.x + "-" + start.y);
        obj.GetComponent<SpriteRenderer>().color = new Color(1.0f, 0.0f, 0.0f, 1.0f);
        obj = GameObject.Find(goal.x + "-" + goal.y);
        obj.GetComponent<SpriteRenderer>().color = new Color(0.0f, 1.0f, 0.0f, 1.0f);
    }
}
