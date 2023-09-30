using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BackGrounds : MonoBehaviour
{
    [SerializeField] private int attachedStageNum = 0;
    private int stageNum;
    // Start is called before the first frame update
    void Start()
    {
        stageNum = StageNumController.GetStageNum;
    }

    // Update is called once per frame
    void Update()
    {
        if (stageNum % 3 == attachedStageNum % 3)
        {
            this.GetComponent<SpriteRenderer>().color = new Color(0.5660378f, 0.4992881f, 4992881f, 1.0f);
        }
        else
        {
            this.GetComponent<SpriteRenderer>().color = new Color(1.0f, 1.0f, 1.0f, 0.0f);
        }
    }
}
