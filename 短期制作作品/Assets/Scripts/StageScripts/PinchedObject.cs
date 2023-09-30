using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PinchedObject : MonoBehaviour
{
    private int stageNum;

    private Vector2 pos;
    private Hand hand;
    private float rad = 0.0f;
    private float decidedPosX;
    private bool decidedFlag = false;

    [SerializeField] private Vector2 adjustPos;
    [SerializeField] private int attachedStageNum;

    private bool playFlag = false;

    void Start()
    {
        GameObject obj = GameObject.Find("hand");
        hand = obj.GetComponent<Hand>();
        pos = hand.GetPos;
        pos += adjustPos;

        stageNum = StageNumController.GetStageNum;
    }

    // Update is called once per frame
    void Update()
    {
        if (stageNum % 3 == attachedStageNum)
        {
            this.GetComponent<SpriteRenderer>().color = new Color(1.0f, 1.0f, 1.0f, 1.0f);

            if (hand.GetLeaveFlag == false)
            {
                pos = hand.GetPos;
                pos += adjustPos;
            }
            if (hand.GetLeaveFlag == true && decidedFlag == false)
            {
                decidedPosX = pos.x;
                decidedFlag = true;
            }
            if (playFlag==true)
            {
                if (pos.y < 10.0f)
                {
                    pos.y += 0.03f;
                }
                if(attachedStageNum==2)
                {
                    pos.x = decidedPosX + Mathf.Sin(rad * Mathf.PI) * 0.05f;
                    rad += Time.deltaTime * 50.0f;
                    if (rad > 2.0f)
                    {
                        rad = 0.0f;
                    }
                }
            }
            transform.position = pos;
        }
        else
        {
            this.GetComponent<SpriteRenderer>().color = new Color(1.0f, 1.0f, 1.0f, 0.0f);

        }
    }

    public void SetEndFlag()
    {
        playFlag = !playFlag;
    }
}
