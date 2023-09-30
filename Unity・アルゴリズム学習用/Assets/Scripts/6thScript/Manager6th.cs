using System.Collections;
using System.Collections.Generic;
using UnityEngine;

using UnityEngine.UI;

public class Manager6th : MonoBehaviour
{
    const float cellSize = 107.0f;

    class POS
    {
        public int x=0, y=0;
    }

    [SerializeField]POS playerPos = new POS();
    [SerializeField] POS player2Pos = new POS();
    [SerializeField] POS player3Pos = new POS();
    POS enemyPos = new POS();
    [SerializeField]int movePower = 0;
    Vector2 pos = new Vector2(0.0f, 0.0f);
    Vector2 pos2 = new Vector2(0.0f, 0.0f);
    Vector2 pos3 = new Vector2(0.0f, 0.0f);
    Vector2 posE = new Vector2(0.0f, 0.0f);
    [SerializeField]Vector2 clickPos;
    bool clickUpFlag = true;
    [SerializeField]POS clickedCell = new POS();
    int[,] map = new int[9, 9];
    int nowMovig = 0;

    // Start is called before the first frame update
    void Start()
    {
        playerPos.x = 4;
        playerPos.y = 4;
        player2Pos.x = 3;
        player2Pos.y = 4;
        player3Pos.x = 5;
        player3Pos.y = 4;
        enemyPos.x = 0;
        enemyPos.y = 0;
        for (int i=0;i<9;i++)
        {
            for(int j=0;j<9;j++)
            {
                if (Random.Range(0, 5) == 0)
                {
                    map[j, i] = 2;
                    GameObject.Find((j + 1) + "-" + (i + 1)).GetComponent<SpriteRenderer>().color = new Color(1.0f, 0.7098039f, 0.6588235f, 1.0f);
                }
                else
                {
                    map[j, i] = 1;
                    GameObject.Find((j + 1) + "-" + (i + 1)).GetComponent<SpriteRenderer>().color = new Color(1.0f, 1.0f, 1.0f, 1.0f);
                }
            }
        }
    }

    // Update is called once per frame
    void Update()
    {
        if(nowMovig==3)
        {
            int tmp = Random.Range(0, 3);
            while (true)
            {
                if (Random.Range(1, 3) % 2 == 0)
                {
                    if (enemyPos.x + tmp < 9)
                    {
                        enemyPos.x += tmp;
                    }
                    else
                    {
                        enemyPos.x -= tmp;
                    }
                }
                else
                {
                    if (enemyPos.x - tmp > 0)
                    {
                        enemyPos.x -= tmp;
                    }
                    else
                    {
                        enemyPos.x += tmp;
                    }
                }
                if (Random.Range(1, 3) % 2 == 0)
                {
                    if (enemyPos.y + (2 - tmp) < 9)
                    {
                        enemyPos.y += (2 - tmp);
                    }
                    else
                    {
                        enemyPos.y -= (2 - tmp);
                    }
                }
                else
                {
                    if (enemyPos.y - (2 - tmp) > 0)
                    {
                        enemyPos.y -= (2 - tmp);
                    }
                    else
                    {
                        enemyPos.y += (2 - tmp);
                    }
                }
                bool breakFlag = true;
                if(enemyPos.x==playerPos.x&& enemyPos.y == playerPos.y)
                {
                    breakFlag = false;
                }
                if (enemyPos.x == player2Pos.x && enemyPos.y == player2Pos.y)
                {
                    breakFlag = false;
                }
                if (enemyPos.x == player3Pos.x && enemyPos.y == player3Pos.y)
                {
                    breakFlag = false;
                }
                if(breakFlag==true)
                {
                    break;
                }
            }

            nowMovig = 0;
            //Debug.Log(enemyPos.x);
            //Debug.Log(enemyPos.y);
        }
        if(nowMovig==0)
        {
            GameObject.Find("Player").GetComponent<SpriteRenderer>().color = new Color(0.2588235f, 1.0f, 1.0f, 1.0f);
            GameObject.Find("2P").GetComponent<SpriteRenderer>().color = new Color(0.7843137f, 0.2352941f, 0.2078431f, 0.5f);
            GameObject.Find("3P").GetComponent<SpriteRenderer>().color = new Color(0.572549f, 0.9529412f, 0.6431373f, 0.5f);
            GameObject.Find("now").GetComponent<SpriteRenderer>().color = new Color(0.2588235f, 1.0f, 1.0f, 1.0f);
        }
        else if(nowMovig==1)
        {
            GameObject.Find("Player").GetComponent<SpriteRenderer>().color = new Color(0.2588235f, 1.0f, 1.0f, 0.5f);
            GameObject.Find("2P").GetComponent<SpriteRenderer>().color = new Color(0.7843137f, 0.2352941f, 0.2078431f, 1.0f);
            GameObject.Find("3P").GetComponent<SpriteRenderer>().color = new Color(0.572549f, 0.9529412f, 0.6431373f, 0.5f);
            GameObject.Find("now").GetComponent<SpriteRenderer>().color = new Color(0.7843137f, 0.2352941f, 0.2078431f, 1.0f);
        }
        else
        {
            GameObject.Find("Player").GetComponent<SpriteRenderer>().color = new Color(0.2588235f, 1.0f, 1.0f, 0.5f);
            GameObject.Find("2P").GetComponent<SpriteRenderer>().color = new Color(0.7843137f, 0.2352941f, 0.2078431f, 0.5f);
            GameObject.Find("3P").GetComponent<SpriteRenderer>().color = new Color(0.572549f, 0.9529412f, 0.6431373f, 1.0f);
            GameObject.Find("now").GetComponent<SpriteRenderer>().color = new Color(0.572549f, 0.9529412f, 0.6431373f, 1.0f);
        }


        if (clickUpFlag == true)
        {
            if (Input.GetMouseButtonDown(0) == true)
            {
                clickPos = Input.mousePosition;
                
                for(int i=0;i<9;i++)
                {
                    for(int j=0;j<9;j++)
                    {
                        if(clickPos.x>465.0f+(float)j*cellSize&& clickPos.x < 465.0f + (float)(j+1) * cellSize
                            &&clickPos.y< 1047.0f - (float)i *cellSize&&clickPos.y> 1047.0f - (float)(i+1)*cellSize)
                        {
                            clickedCell.x = j;
                            clickedCell.y = i;
                            break;
                        }
                    }
                }
                MovePlayer2();
                clickUpFlag = false;
                //Debug.Log(clickedCell.x);
                //Debug.Log(clickedCell.y);
                //Debug.Log(playerPos.x);
                //Debug.Log(playerPos.y);
            }
        }

        if(Input.GetMouseButtonDown(0)==false&&clickUpFlag==false)
        {
            clickUpFlag = true;
        }

        pos.x = (float)playerPos.x-4;
        pos.y = (float)(-1)*playerPos.y + 4;
        pos2.x = (float)player2Pos.x - 4;
        pos2.y = (float)(-1) * player2Pos.y + 4;
        pos3.x = (float)player3Pos.x - 4;
        pos3.y = (float)(-1) * player3Pos.y + 4;
        posE.x = (float)enemyPos.x - 4;
        posE.y = (float)(-1) * enemyPos.y + 4;
        AdjustPos();
        GameObject.Find("Player").transform.position = pos;
        GameObject.Find("2P").transform.position = pos2;
        GameObject.Find("3P").transform.position = pos3;
        GameObject.Find("Enemy").transform.position = posE;

    }

    void AdjustPos()
    {
        pos.x -= 0.076f;
        pos.y += 0.183f;
        pos2.x -= 0.076f;
        pos2.y += 0.183f;
        pos3.x -= 0.076f;
        pos3.y += 0.183f;
        posE.x -= 0.076f;
        posE.y += 0.183f;

    }

    class MoveController
    {
        public int xMove, yMove;
        public POS tmpPos;
        public bool xMovedFlag;
    }


    void MovePlayer2()
    {

        movePower = 0;
        int xMove = 0;
        int yMove = 0;
        

        POS tmpPos = new POS();
        POS targetPlayer = new POS();

        int minPower = 5;

        int xDis = 1;
        int yDis = 1;

        if (nowMovig == 0)
        {
            tmpPos.x = playerPos.x;
            tmpPos.y = playerPos.y;


            xMove = Mathf.Abs(clickedCell.x - playerPos.x);
            yMove = Mathf.Abs(clickedCell.y - playerPos.y);
            if (clickedCell.x - playerPos.x>0)
            {
                xDis = 1;
            }
            else
            {
                xDis = -1;
            }
            if (clickedCell.y - playerPos.y > 0)
            {
                yDis = 1;
            }
            else
            {
                yDis = -1;
            }
            targetPlayer = playerPos;
        }
        else if (nowMovig == 1)
        {
            tmpPos.x = player2Pos.x;
            tmpPos.y = player2Pos.y;


            xMove = Mathf.Abs(clickedCell.x - player2Pos.x);
            yMove = Mathf.Abs(clickedCell.y - player2Pos.y);

            if (clickedCell.x - player2Pos.x > 0)
            {
                xDis = 1;
            }
            else
            {
                xDis = -1;
            }
            if (clickedCell.y - player2Pos.y > 0)
            {
                yDis = 1;
            }
            else
            {
                yDis = -1;
            }

            targetPlayer = player2Pos;
        }
        else if (nowMovig == 2)
        {
            tmpPos.x = player3Pos.x;
            tmpPos.y = player3Pos.y;


            xMove = Mathf.Abs(clickedCell.x - player3Pos.x);
            yMove = Mathf.Abs(clickedCell.y - player3Pos.y);

            if (clickedCell.x - player3Pos.x > 0)
            {
                xDis = 1;
            }
            else
            {
                xDis = -1;
            }
            if (clickedCell.y - player3Pos.y > 0)
            {
                yDis = 1;
            }
            else
            {
                yDis = -1;
            }

            targetPlayer = player3Pos;
        }

        if(xMove==0)
        {
            minPower = 0;
            for(int i=0;i<yMove;i++)
            {
                tmpPos.y += yDis;
                minPower += map[tmpPos.x, tmpPos.y];
                if(tmpPos.x==enemyPos.x&&tmpPos.y==enemyPos.y)
                {
                    minPower += 5;
                }
            }
                
        }
        else if(xMove==1)
        {
            POS tmp = new POS();
            tmp.x = tmpPos.x;
            tmp.y = tmpPos.y;
            int min = 10;
            for(int i=0;i<yMove+1;i++)
            {
                tmp.x = tmpPos.x;
                tmp.y = tmpPos.y;
                int minTmp = 0;
                for(int j=0;j<yMove+1;j++)
                {
                    if(i==j)
                    {
                        tmp.x += xDis;
                        minTmp += map[tmp.x, tmp.y];
                    }
                    else
                    {

                    }
                }
            }
        }
    }

    //ì‚è’¼‚µ


    //void MovePlayer()
    //{

        

    //    movePower = 0;
    //    int xMove=0;
    //    int yMove=0;
    //    int canX=0;
    //    int canY=0;
    //    bool retryFlag = false;
    //    bool cantRetryFlag = false;

    //    POS tmpPos = new POS();
    //    POS targetPlayer = new POS();

    //    List<MoveController> moves = new List<MoveController>();

        

    //    if(nowMovig==0)
    //    {
    //        tmpPos.x = playerPos.x;
    //        tmpPos.y = playerPos.y;


    //        xMove = Mathf.Abs(clickedCell.x - playerPos.x);
    //        yMove = Mathf.Abs(clickedCell.y - playerPos.y);

    //        targetPlayer = playerPos;
    //    }
    //    else if(nowMovig==1)
    //    {
    //        tmpPos.x = player2Pos.x;
    //        tmpPos.y = player2Pos.y;


    //        xMove = Mathf.Abs(clickedCell.x - player2Pos.x);
    //        yMove = Mathf.Abs(clickedCell.y - player2Pos.y);

    //        targetPlayer = player2Pos;
    //    }
    //    else if(nowMovig==2)
    //    {
    //        tmpPos.x = player3Pos.x;
    //        tmpPos.y = player3Pos.y;


    //        xMove = Mathf.Abs(clickedCell.x - player3Pos.x);
    //        yMove = Mathf.Abs(clickedCell.y - player3Pos.y);

    //        targetPlayer = player3Pos;
    //    }

    //    void AddMove(bool _xMovedFlag)
    //    {
    //        MoveController move = new MoveController();
    //        move.xMove = xMove;
    //        move.yMove = yMove;
    //        move.tmpPos = tmpPos;
            
    //        move.xMovedFlag = _xMovedFlag;
    //        moves.Add(move);
    //    }

    //    void ReturnSet(MoveController move)
    //    {
    //        xMove = move.xMove;
    //        yMove = move.yMove;
    //        tmpPos.x = move.tmpPos.x;
    //        tmpPos.y = move.tmpPos.y;
    //    }

    //    canX = xMove;
    //    canY = yMove;
        
    //    if(xMove+yMove>4)
    //    {
    //        GameObject.Find("cantMove").GetComponent<Text>().color = new Color(0.0f, 0.0f, 0.0f, 1.0f);
    //        return;
    //    }
    //    else
    //    {
    //        GameObject.Find("cantMove").GetComponent<Text>().color = new Color(0.0f, 0.0f, 0.0f, 0.0f);
    //    }

    //    if(clickedCell.x==playerPos.x&&clickedCell.y==playerPos.y)
    //    {
    //        GameObject.Find("cantMove").GetComponent<Text>().color = new Color(0.0f, 0.0f, 0.0f, 1.0f);
    //        return;
    //    }
    //    else if(clickedCell.x == player2Pos.x && clickedCell.y == player2Pos.y)
    //    {
    //        GameObject.Find("cantMove").GetComponent<Text>().color = new Color(0.0f, 0.0f, 0.0f, 1.0f);
    //        return;
    //    }
    //    else if(clickedCell.x == player3Pos.x && clickedCell.y == player3Pos.y)
    //    {
    //        GameObject.Find("cantMove").GetComponent<Text>().color = new Color(0.0f, 0.0f, 0.0f, 1.0f);
    //        return;
    //    }
    //    else
    //    {
    //        GameObject.Find("cantMove").GetComponent<Text>().color = new Color(0.0f, 0.0f, 0.0f, 0.0f);
    //    }

    //    AddMove(true);

    //    while (true)
    //    {
    //        if(clickedCell.x> targetPlayer.x)
    //        {
    //            if(clickedCell.y> targetPlayer.y)
    //            {
    //                if(xMove>0&&yMove>0)
    //                {
    //                    if (map[tmpPos.x+1,tmpPos.y]>= map[tmpPos.x, tmpPos.y+1])
    //                    {
    //                        if(tmpPos.x==enemyPos.x&&tmpPos.y+1==enemyPos.y||retryFlag==true&&cantRetryFlag==false)
    //                        {
    //                            movePower += map[tmpPos.x + 1, tmpPos.y];
    //                            xMove--;
    //                            tmpPos.x++;

    //                            AddMove(true);
    //                        }
    //                        else
    //                        {
    //                            movePower += map[tmpPos.x, tmpPos.y + 1];
    //                            yMove--;
    //                            tmpPos.y++;
    //                            AddMove(false);
    //                        }
    //                        if(retryFlag==true&&cantRetryFlag==false)
    //                        {
    //                            cantRetryFlag = true;
    //                        }
    //                    }
    //                    else
    //                    {
    //                        if (tmpPos.x+1 == enemyPos.x && tmpPos.y == enemyPos.y||retryFlag==true&&cantRetryFlag==false)
    //                        {
    //                            movePower += map[tmpPos.x, tmpPos.y + 1];
    //                            yMove--;
    //                            tmpPos.y++;
    //                            AddMove(false);
    //                        }
    //                        else
    //                        {
    //                            movePower += map[tmpPos.x + 1, tmpPos.y];
    //                            xMove--;
    //                            tmpPos.x++;
    //                            AddMove(true);
    //                        }
    //                        if (retryFlag == true && cantRetryFlag == false)
    //                        {
    //                            cantRetryFlag = true;
    //                        }
    //                    }
    //                }
    //                else if (xMove > 0)
    //                {
    //                    if(tmpPos.x+1==enemyPos.x&& tmpPos.y == enemyPos.y)
    //                    {
    //                        if(retryFlag==false && cantRetryFlag == false)
    //                        {
    //                            if(canY>0)
    //                            {
    //                                foreach(MoveController ptr in moves)
    //                                {
    //                                    if(ptr.xMovedFlag==true)
    //                                    {
    //                                        ReturnSet(ptr);
    //                                        moves.Clear();
    //                                        retryFlag = true;
    //                                        break;
    //                                    }
    //                                }
    //                            }
    //                            else
    //                            {
    //                                GameObject.Find("cantMove").GetComponent<Text>().color = new Color(0.0f, 0.0f, 0.0f, 1.0f);
    //                                return;
    //                            }

    //                        }
    //                        else
    //                        {
    //                            GameObject.Find("cantMove").GetComponent<Text>().color = new Color(0.0f, 0.0f, 0.0f, 1.0f);
    //                            return;
    //                        }
    //                    }
    //                    else
    //                    {
    //                        movePower += map[tmpPos.x + 1, tmpPos.y];
    //                        xMove--;
    //                        tmpPos.x++;
    //                        AddMove(true);
    //                    }
                        
    //                }
    //                else if (yMove > 0)
    //                {
    //                    if (tmpPos.x == enemyPos.x && tmpPos.y + 1 == enemyPos.y)
    //                    {
    //                        if(retryFlag==false && cantRetryFlag == false)
    //                        {
    //                            if (canX > 0)
    //                            {
    //                                foreach (MoveController ptr in moves)
    //                                {
    //                                    if (ptr.xMovedFlag == false)
    //                                    {
    //                                        ReturnSet(ptr);
    //                                        moves.Clear();
    //                                        retryFlag = true;
    //                                        break;
    //                                    }
    //                                }
    //                            }
    //                            else
    //                            {
    //                                GameObject.Find("cantMove").GetComponent<Text>().color = new Color(0.0f, 0.0f, 0.0f, 1.0f);
    //                                return;
    //                            }
    //                        }
    //                        else
    //                        {
    //                            GameObject.Find("cantMove").GetComponent<Text>().color = new Color(0.0f, 0.0f, 0.0f, 1.0f);
    //                            return;
    //                        }
                            
    //                    }
    //                    else
    //                    {
    //                        movePower += map[tmpPos.x, tmpPos.y + 1];
    //                        yMove--;
    //                        tmpPos.y++;
    //                        AddMove(false);
    //                    }
                        
    //                }
    //                else
    //                {
    //                    break;
    //                }
    //            }
    //            else
    //            {
    //                if (xMove > 0 && yMove > 0)
    //                {
    //                    if (map[tmpPos.x + 1, tmpPos.y] >= map[tmpPos.x, tmpPos.y - 1]||retryFlag==true&&cantRetryFlag==false)
    //                    {
    //                        if(tmpPos.y-1==enemyPos.y&& tmpPos.x == enemyPos.x)
    //                        {
    //                            movePower += map[tmpPos.x + 1, tmpPos.y];
    //                            xMove--;
    //                            tmpPos.x++;
    //                            AddMove(true);
    //                        }
    //                        else
    //                        {
    //                            movePower += map[tmpPos.x, tmpPos.y - 1];
    //                            yMove--;
    //                            tmpPos.y--;
    //                            AddMove(false);
    //                        }
    //                        if (retryFlag == true && cantRetryFlag == false)
    //                        {
    //                            cantRetryFlag = true;
    //                        }

    //                    }
    //                    else
    //                    {
    //                        if (tmpPos.y == enemyPos.y && tmpPos.x + 1 == enemyPos.x || retryFlag == true && cantRetryFlag == false)
    //                        {
    //                            movePower += map[tmpPos.x, tmpPos.y - 1];
    //                            yMove--;
    //                            tmpPos.y--;
    //                            AddMove(false);
    //                        }
    //                        else
    //                        {
    //                            movePower += map[tmpPos.x + 1, tmpPos.y];
    //                            xMove--;
    //                            tmpPos.x++;
    //                            AddMove(true);
    //                        }
    //                        if (retryFlag == true && cantRetryFlag == false)
    //                        {
    //                            cantRetryFlag = true;
    //                        }
    //                    }
    //                }
    //                else if (xMove > 0)
    //                {
    //                    if (tmpPos.x + 1 == enemyPos.x && tmpPos.y == enemyPos.y)
    //                    {
    //                        if (retryFlag == false && cantRetryFlag == false)
    //                        {
    //                            if (canX > 0)
    //                            {
    //                                foreach (MoveController ptr in moves)
    //                                {
    //                                    if (ptr.xMovedFlag == false)
    //                                    {
    //                                        ReturnSet(ptr);
    //                                        moves.Clear();
    //                                        retryFlag = true;
    //                                        break;
    //                                    }
    //                                }
    //                            }
    //                            else
    //                            {
    //                                GameObject.Find("cantMove").GetComponent<Text>().color = new Color(0.0f, 0.0f, 0.0f, 1.0f);
    //                                return;
    //                            }
    //                        }
    //                    }
    //                    else
    //                    {
    //                        movePower += map[tmpPos.x + 1, tmpPos.y];
    //                        xMove--;
    //                        tmpPos.x++;
    //                        AddMove(true);
    //                    }
                        
    //                }
    //                else if (yMove > 0)
    //                {
    //                    if (tmpPos.x == enemyPos.x && tmpPos.y - 1 == enemyPos.y)
    //                    {
    //                        if (retryFlag == false && cantRetryFlag == false)
    //                        {
    //                            if (canY > 0)
    //                            {
    //                                foreach (MoveController ptr in moves)
    //                                {
    //                                    if (ptr.xMovedFlag == true)
    //                                    {
    //                                        ReturnSet(ptr);
    //                                        moves.Clear();
    //                                        retryFlag = true;
    //                                        break;
    //                                    }
    //                                }
    //                            }
    //                            else
    //                            {
    //                                GameObject.Find("cantMove").GetComponent<Text>().color = new Color(0.0f, 0.0f, 0.0f, 1.0f);
    //                                return;
    //                            }
    //                        }
    //                        else
    //                        {
    //                            movePower += map[tmpPos.x, tmpPos.y - 1];
    //                            yMove--;
    //                            tmpPos.y--;
    //                            AddMove(false);
    //                        }
                            
    //                    }
    //                }
    //                else
    //                {
    //                    break;
    //                }
    //            }
    //        }
    //        else
    //        {
    //            if (clickedCell.y > targetPlayer.y)
    //            {
    //                if (xMove > 0 && yMove > 0)
    //                {
    //                    if (map[tmpPos.x - 1, tmpPos.y] >= map[tmpPos.x, tmpPos.y + 1]||retryFlag==true&&cantRetryFlag==false)
    //                    {
    //                        if (tmpPos.x == enemyPos.x && tmpPos.y + 1 == enemyPos.y)
    //                        {
    //                            movePower += map[tmpPos.x - 1, tmpPos.y];
    //                            xMove--;
    //                            tmpPos.x--;
    //                            AddMove(true);
    //                        }
    //                        else
    //                        {
    //                            movePower += map[tmpPos.x, tmpPos.y + 1];
    //                            yMove--;
    //                            tmpPos.y++;
    //                            AddMove(false);
    //                        }
    //                        if(retryFlag == true && cantRetryFlag == false)
    //                        {
    //                            cantRetryFlag = true;
    //                        }
                            
    //                    }
    //                    else
    //                    {
    //                        if (tmpPos.x - 1 == enemyPos.x && tmpPos.y == enemyPos.y||retryFlag==true&&cantRetryFlag==false)
    //                        {
    //                            movePower += map[tmpPos.x, tmpPos.y + 1];
    //                            yMove--;
    //                            tmpPos.y++;
    //                            AddMove(false);
    //                        }
    //                        else
    //                        {
    //                            movePower += map[tmpPos.x - 1, tmpPos.y];
    //                            xMove--;
    //                            tmpPos.x--;
    //                            AddMove(true);
    //                        }
    //                        if(retryFlag == true && cantRetryFlag == false)
    //                        {
    //                            cantRetryFlag = true;
    //                        }
                            
    //                    }
    //                }
    //                else if (xMove > 0)
    //                {
    //                    if(tmpPos.x - 1 == enemyPos.x && tmpPos.y == enemyPos.y)
    //                    {
    //                        if (retryFlag == false && cantRetryFlag == false)
    //                        {
    //                            if (canX > 0)
    //                            {
    //                                foreach (MoveController ptr in moves)
    //                                {
    //                                    if (ptr.xMovedFlag == false)
    //                                    {
    //                                        ReturnSet(ptr);
    //                                        moves.Clear();
    //                                        retryFlag = true;
    //                                        break;
    //                                    }
    //                                }
    //                            }
    //                            else
    //                            {
    //                                GameObject.Find("cantMove").GetComponent<Text>().color = new Color(0.0f, 0.0f, 0.0f, 1.0f);
    //                                return;
    //                            }
    //                        }
    //                    }
    //                    else
    //                    {
    //                        movePower += map[tmpPos.x - 1, tmpPos.y];
    //                        xMove--;
    //                        tmpPos.x--;
    //                        AddMove(true);
    //                    }
                        
    //                }
    //                else if (yMove > 0)
    //                {
    //                    if(tmpPos.x == enemyPos.x && tmpPos.y + 1 == enemyPos.y)
    //                    {
    //                        if (retryFlag == false && cantRetryFlag == false)
    //                        {
    //                            if (canX > 0)
    //                            {
    //                                foreach (MoveController ptr in moves)
    //                                {
    //                                    if (ptr.xMovedFlag == true)
    //                                    {
    //                                        ReturnSet(ptr);
    //                                        moves.Clear();
    //                                        retryFlag = true;
    //                                        break;
    //                                    }
    //                                }
    //                            }
    //                            else
    //                            {
    //                                GameObject.Find("cantMove").GetComponent<Text>().color = new Color(0.0f, 0.0f, 0.0f, 1.0f);
    //                                return;
    //                            }
    //                        }
    //                    }
    //                    else
    //                    {
    //                        movePower += map[tmpPos.x, tmpPos.y + 1];
    //                        yMove--;
    //                        tmpPos.y++;
    //                        AddMove(false);
    //                    }
                        
    //                }
    //                else
    //                {
    //                    break;
    //                }
    //            }
    //            else
    //            {
    //                if (xMove > 0 && yMove > 0)
    //                {
    //                    if (map[tmpPos.x - 1, tmpPos.y] >= map[tmpPos.x, tmpPos.y - 1]||retryFlag==true&&cantRetryFlag==false)
    //                    {
    //                        if(tmpPos.x == enemyPos.x && tmpPos.y - 1 == enemyPos.y)
    //                        {
    //                            movePower += map[tmpPos.x - 1, tmpPos.y];
    //                            xMove--;
    //                            tmpPos.x--;
    //                            AddMove(true);
    //                        }
    //                        else
    //                        {
    //                            movePower += map[tmpPos.x, tmpPos.y - 1];
    //                            yMove--;
    //                            tmpPos.y--;
    //                            AddMove(false);
    //                        }
    //                        if(retryFlag == true && cantRetryFlag == false)
    //                        {
    //                            cantRetryFlag = true;
    //                        }
                            
    //                    }
    //                    else
    //                    {
    //                        if (tmpPos.x - 1 == enemyPos.x && tmpPos.y == enemyPos.y)
    //                        {
    //                            movePower += map[tmpPos.x, tmpPos.y - 1];
    //                            yMove--;
    //                            tmpPos.y--;
    //                            AddMove(false);
    //                        }
    //                        else
    //                        {
    //                            movePower += map[tmpPos.x - 1, tmpPos.y];
    //                            xMove--;
    //                            tmpPos.x--;
    //                            AddMove(true);
    //                        }
                            
    //                    }
    //                }
    //                else if (xMove > 0)
    //                {
    //                    if (tmpPos.x - 1 == enemyPos.x && tmpPos.y == enemyPos.y)
    //                    {
    //                        if (retryFlag == false && cantRetryFlag == false)
    //                        {
    //                            if (canX > 0)
    //                            {
    //                                foreach (MoveController ptr in moves)
    //                                {
    //                                    if (ptr.xMovedFlag == true)
    //                                    {
    //                                        ReturnSet(ptr);
    //                                        moves.Clear();
    //                                        retryFlag = true;
    //                                        break;
    //                                    }
    //                                }
    //                            }
    //                            else
    //                            {
    //                                GameObject.Find("cantMove").GetComponent<Text>().color = new Color(0.0f, 0.0f, 0.0f, 1.0f);
    //                                return;
    //                            }
    //                        }
    //                        else
    //                        {
    //                            GameObject.Find("cantMove").GetComponent<Text>().color = new Color(0.0f, 0.0f, 0.0f, 1.0f);
    //                            return;
    //                        }
    //                    }
    //                    else
    //                    {
    //                        movePower += map[tmpPos.x - 1, tmpPos.y];
    //                        xMove--;
    //                        tmpPos.x--;
    //                        AddMove(true);
    //                    }
                        
    //                }
    //                else if (yMove > 0)
    //                {
    //                    if(tmpPos.x == enemyPos.x && tmpPos.y - 1 == enemyPos.y)
    //                    {
    //                        if (retryFlag == false && cantRetryFlag == false)
    //                        {
    //                            if (canY > 0)
    //                            {
    //                                foreach (MoveController ptr in moves)
    //                                {
    //                                    if (ptr.xMovedFlag == false)
    //                                    {
    //                                        ReturnSet(ptr);
    //                                        moves.Clear();
    //                                        retryFlag = true;
    //                                        break;
    //                                    }
    //                                }
    //                            }
    //                            else
    //                            {
    //                                GameObject.Find("cantMove").GetComponent<Text>().color = new Color(0.0f, 0.0f, 0.0f, 1.0f);
    //                                return;
    //                            }
    //                        }
    //                    }
    //                    else
    //                    {
    //                        movePower += map[tmpPos.x, tmpPos.y - 1];
    //                        yMove--;
    //                        tmpPos.y--;
    //                        AddMove(false);
    //                    }
                        
    //                }
    //                else
    //                {
    //                    break;
    //                }
    //            }
    //        }
    //    }

    //    if (movePower <= 4)
    //    {
    //        targetPlayer.x = clickedCell.x;
    //        targetPlayer.y = clickedCell.y;
    //        GameObject.Find("cantMove").GetComponent<Text>().color = new Color(0.0f, 0.0f, 0.0f, 0.0f);
    //        nowMovig++;
    //    }
    //    else
    //    {
    //        GameObject.Find("cantMove").GetComponent<Text>().color = new Color(0.0f, 0.0f, 0.0f, 1.0f);
    //        return;
    //    }
    //}
}
