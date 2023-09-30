using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TargetMarker : MonoBehaviour
{
    private int stageNum;

    private Vector2 pos;
    private Hand hand;
    private Color color;
    private float alfa = 0.0f;
    private float waitTimer = 0.0f;
    private float handStopPosY = 0.0f;
    private float stopSetPosY = 0.0f;
    private float downSpeed = 0.0f;

    private bool isEnd = false;

    private bool startFlag = false;
    private bool playFlag = false;
    private bool decidedFlag = false;
    void Start()
    {
        stageNum = StageNumController.GetStageNum;

        GameObject obj = GameObject.Find("hand");
        hand = obj.GetComponent<Hand>();
        pos = hand.GetPos;
        AdjustPos();
        if (stageNum%3 == 0)
        {
            handStopPosY = 1.3f;
            stopSetPosY = -2.0f;
            downSpeed = 0.02f;
        }
        else if (stageNum % 3 == 1)
        {
            handStopPosY = 2.0f;
            stopSetPosY = -2.0f;
            downSpeed = 0.017f;
        }
        else if (stageNum % 3 == 2)
        {
            handStopPosY = 3.0f;
            stopSetPosY = -2.0f;
            downSpeed = 0.013f;
        }
        
        this.GetComponent<SpriteRenderer>().color = new Color(0, 255, 0, alfa);
    }

    // Update is called once per frame
    void Update()
    {
        if (startFlag==true)
        {
            if (hand.GetPos.y > handStopPosY && alfa == 0.0f)
            {
                pos.y -= downSpeed;
            }
            else if (hand.GetPos.y<=handStopPosY && alfa < 1.0f)
            {
                alfa += 0.025f;
                this.GetComponent<SpriteRenderer>().color = new Color(0, 255, 0, alfa);
            }
            else if (alfa >= 1.0f && pos.y > stopSetPosY)
            {
                pos.y -= 0.025f;
            }
            else
            {
                this.GetComponent<SpriteRenderer>().color = new Color(255, 0, 0, alfa);
                waitTimer += Time.deltaTime;
                if (waitTimer > 0.5f)
                {
                    isEnd = true;
                }
            }

            transform.position = pos;
        }
        if (playFlag==true)
        {
            pos = hand.GetPos;
            AdjustPos();

            transform.position = pos;
        }

        if (decidedFlag==true)
        {
            alfa = 0.0f;
            this.GetComponent<SpriteRenderer>().color = new Color(0, 255, 0, alfa);
        }
    }

    public Vector2 GetPos
    {
        get { return pos; }
    }

    private void AdjustPos()
    {
        if(stageNum==0||stageNum==3)
        {
            pos.x -= 0.8f;
            pos.y -= 3.3f;
        }
        else if(stageNum==1||stageNum==4)
        {
            pos.x -= 0.75f;
            pos.y -= 4.0f;
        }
        else if(stageNum==2||stageNum==5)
        {
            pos.x -= 1.0f;
            pos.y -= 5.0f;
        }
    }

    public bool IsEnd
    {
        get { return isEnd; }
    }

    public void SetStartFlag()
    {
        startFlag = !startFlag;
    }

    public void SetActionFlag()
    {
        playFlag = !playFlag;
    }

    public void SetDecidedFlag()
    {
        decidedFlag = !decidedFlag;
    }
}
