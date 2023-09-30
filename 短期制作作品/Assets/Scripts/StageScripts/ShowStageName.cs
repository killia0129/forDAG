using System.Collections;
using System.Collections.Generic;
using UnityEngine;

using UnityEngine.UI;
using Unity.IO;


public class ShowStageName : MonoBehaviour
{
    private int stageNum;

    private Color color;

    private Color textColor;
    [SerializeField] private GameObject showTextObj = null;

    private Text stageText;
    private bool showFlag = false;
    
    // Start is called before the first frame update
    void Start()
    {
        stageNum = StageNumController.GetStageNum;

        textColor = showTextObj.GetComponent<Text>().color;
    }

    // Update is called once per frame
    void Update()
    {
        stageText = showTextObj.GetComponent<Text>();
        stageText.text = "STAGE " + (stageNum + 1);

        if (showFlag==true)
        {
            color.a = 1.0f;
        }
        else
        {
            color.a = 0.0f;
        }

        showTextObj.GetComponent<Text>().color = color;
    }

    public void SetShowFlag()
    {
        showFlag = !showFlag;
    }
}
