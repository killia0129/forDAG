using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ResultSE : MonoBehaviour
{
    [SerializeField] private int upperLimit;
    [SerializeField] private int LowerLimit;

    [SerializeField] AudioClip SE;
    AudioSource audio;
    ScoreText score;
    private bool playFlag = true;
    private bool endFaseFlag = false;

 

    // Start is called before the first frame update
    void Start()
    {
        audio = this.GetComponent<AudioSource>();
        GameObject objM = GameObject.Find("Score");
        score = objM.GetComponent<ScoreText>();
    }

    // Update is called once per frame
    void Update()
    {
        if (endFaseFlag==true)
        {

            if (VolumeControlerScript.GetSetVolume == true)
            {
                if (playFlag == true)
                {
                    if (score.GetScore < upperLimit && score.GetScore >= LowerLimit)
                    {
                        audio.PlayOneShot(SE);
                        playFlag = false;
                    }
                    
                }
            }
        }
    }

    public void SetEndFlag()
    {
        endFaseFlag = !endFaseFlag;
    }
}
