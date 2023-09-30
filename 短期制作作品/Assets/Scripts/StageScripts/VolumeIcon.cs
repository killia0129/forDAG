using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class VolumeIcon : MonoBehaviour
{
    private Color color;
    [SerializeField]private bool isHi;


    private bool pauseFlag = false;
    // Start is called before the first frame update
    void Start()
    {
        color = this.GetComponent<SpriteRenderer>().color;
    }

    // Update is called once per frame
    void Update()
    {
        if(isHi==true)
        {
            if (pauseFlag==true)
            {
                if (VolumeControlerScript.GetSetVolume == true)
                {
                    color.a = 1.0f;
                    this.GetComponent<SpriteRenderer>().color = color;
                }
                else
                {
                    color.a = 0.0f;
                    this.GetComponent<SpriteRenderer>().color = color;
                }
            }
            else
            {
                color.a = 0.0f;
                this.GetComponent<SpriteRenderer>().color = color;
            }
        }
        else
        {
            if (pauseFlag == true)
            {
                if (VolumeControlerScript.GetSetVolume == true)
                {
                    color.a = 0.0f;
                    this.GetComponent<SpriteRenderer>().color = color;
                }
                else
                {
                    color.a = 1.0f;
                    this.GetComponent<SpriteRenderer>().color = color;
                }
            }
            else
            {
                color.a = 0.0f;
                this.GetComponent<SpriteRenderer>().color = color;
            }
        }
    }

    public void SetPauseFlag()
    {
        pauseFlag = !pauseFlag;
    }
}
