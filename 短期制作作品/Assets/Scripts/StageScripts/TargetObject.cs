using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TargetObject : MonoBehaviour
{
    private int stageNum;

    private Vector2 pos;

    private float rad = 0.0f;
    private float defaultPosX;

    [SerializeField]private int attachedStage;

    private bool endFlag = false;
    // Start is called before the first frame update
    void Start()
    {
        pos = transform.position;
        defaultPosX = pos.x;

        stageNum = StageNumController.GetStageNum;
    }

    // Update is called once per frame
    void Update()
    {
        if (stageNum % 3 == attachedStage)
        {
            this.GetComponent<SpriteRenderer>().color = new Color(1.0f, 1.0f, 1.0f, 1.0f);
            if (endFlag==true)
            {
                if (pos.y < 10.0f)
                {
                    pos.y += 0.03f;
                }
                if(attachedStage==2)
                {
                    pos.x = defaultPosX + Mathf.Sin(rad * Mathf.PI) * 0.05f;
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
        endFlag = !endFlag;
    }
}
