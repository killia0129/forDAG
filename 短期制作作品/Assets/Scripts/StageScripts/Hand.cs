using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Hand : MonoBehaviour
{
    private bool moveLeftFlag = true;
    private bool moveUpFlag = true;
    public Vector2 pos;
    private float horizontalSpeed = 0.1f;
    private float verticalSpeed = 0.1f;
    private int horizontalRandomRange = 21;
    private int verticalRandomRange = 21;
    private float handToMarkarDis = 3.3f;
    private bool leaveObjectFlag = false;
    private float stopPosY = 0.0f;

    private int stageNum;

    [SerializeField]private bool isEnd = false;
    [SerializeField] private bool startPlayFlag = false;
    [SerializeField] private bool onActionPlayFag = false;
    [SerializeField] private bool decidedPlayFlag = false;
    [SerializeField] private bool endPlayFlag = false;

    void Start()
    {
        stageNum = StageNumController.GetStageNum;

        
        pos = transform.position;
        if (stageNum == 0 || stageNum == 3)
        {
            handToMarkarDis = 3.3f;
            stopPosY = 1.3f;
        }
        else if (stageNum == 1 || stageNum == 4)
        {
            handToMarkarDis = 4.0f;
            pos.x += 1.0f;
            stopPosY = 2.0f;
        }
        else if (stageNum == 2 || stageNum == 5)
        {
            handToMarkarDis = 5.0f;
            stopPosY = 3.0f;
        }
        if(stageNum<=2)
        {
            horizontalSpeed = 0.03f;
            verticalSpeed = 0.01f;
            horizontalRandomRange = 101;
            verticalRandomRange = 101;
        }
        else
        {
            horizontalSpeed = 0.04f;
            verticalSpeed = 0.02f;
            horizontalRandomRange = 81;
            verticalRandomRange = 81;
        }
    }

    void Update()
    {
        if (startPlayFlag==true)
        {
            if (pos.y > stopPosY)
            {
                pos.y -= 0.03f;
            }
            transform.position = pos;
        }
        if (onActionPlayFag==true)
        {
            if (moveLeftFlag == true)
            {
                pos.x -= horizontalSpeed;
            }
            else
            {
                pos.x += horizontalSpeed;
            }

            if (moveUpFlag == true)
            {
                pos.y += verticalSpeed;
            }
            else
            {
                pos.y -= verticalSpeed;
            }

            int rndH = Random.Range(1, horizontalRandomRange);
            int rndV = Random.Range(1, verticalRandomRange);

            if (rndH == 1)
            {
                if (moveLeftFlag == true)
                {
                    moveLeftFlag = false;
                }
                else
                {
                    moveLeftFlag = true;
                }
            }

            if (rndV == 1)
            {
                if (moveUpFlag == true)
                {
                    moveUpFlag = false;
                }
                else
                {
                    moveUpFlag = true;
                }
            }

            if (pos.x < -1.7f)
            {
                moveLeftFlag = false;
            }
            if (pos.x > 3.0f)
            {
                moveLeftFlag = true;
            }

            if (pos.y > 3.0f)
            {
                moveUpFlag = false;
            }
            if (pos.y < 0.7f)
            {
                moveUpFlag = true;
            }


            transform.position = pos;
        }

        if (decidedPlayFlag==true)
        {
            if (leaveObjectFlag == false)
            {
                if (handToMarkarDis > 1.0f)
                {
                    pos.y -= 0.025f;
                    handToMarkarDis -= 0.025f;
                }
                if (handToMarkarDis <= 1.0f)
                {
                    leaveObjectFlag = true;
                }
            }
            else
            {
                pos.y += 0.03f;
                if (pos.y > 1.5f)
                {
                    isEnd = true;
                }
            }
            transform.position = pos;
        }

        if (endPlayFlag==true)
        {
            if (pos.y < 10.0f)
            {
                pos.y += 0.03f;
            }
            transform.position = pos;
        }
    }

    public Vector2 GetPos
    {
        get { return pos; }
    }

    public bool GetLeaveFlag
    {
        get { return leaveObjectFlag; }
    }

    public float GetHandToMarkDis
    {
        get { return handToMarkarDis; }
    }

    public bool IsEnd
    {
        get { return isEnd; }
    }

    public void SetStartFlag()
    {
        startPlayFlag = !startPlayFlag;
    }

    public void SetActionFlag()
    {
        onActionPlayFag = !onActionPlayFag;
    }

    public void SetDecidedFlag()
    {
        decidedPlayFlag = !decidedPlayFlag;
    }

    public void SetEndFlag()
    {
        endPlayFlag = !endPlayFlag;
    }
}
