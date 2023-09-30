using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class VolumeMarkTitleScript : MonoBehaviour
{
    private bool lastVol = true;
    [SerializeField] private float animTime = 0.3f;
    [SerializeField] private bool animFlag = false;
    private bool changeVolOffFlag = true;

    private Vector2 pos;

    private float posX;

    private bool playFlag = false;
    private bool pauseFlag = false;
    private bool lastPlayFlag = false;
    // Start is called before the first frame update
    void Start()
    {
        pos = this.transform.position;

        if (VolumeControlerScript.GetSetVolume == false)
        {
            pos.x = -1.25f;
            this.transform.position = pos;
        }
        posX = pos.x;
    }

    // Update is called once per frame
    void Update()
    {
        if (pauseFlag==true)
        {
            if (lastPlayFlag==true)
            {
                pos = this.transform.position;
            }
            if (VolumeControlerScript.GetSetVolume != lastVol)
            {

                if (animFlag == false)
                {
                    if (lastVol == true)
                    {
                        changeVolOffFlag = true;
                    }
                    else
                    {
                        changeVolOffFlag = false;
                    }
                }
                animFlag = true;
            }

            if (animFlag == true)
            {
                if (changeVolOffFlag == true)
                {
                    posX -= 2.5f / animTime;
                    if(posX<-1.25f)
                    {
                        posX = -1.25f;
                        animFlag = false;
                    }
                }
                else
                {
                    posX += 2.5f / animTime;
                    if (posX > 1.25f)
                    {
                        posX = 1.25f;
                        animFlag = false;
                    }
                }

            }
        }

        pos.x = posX;
        this.transform.position = pos;

        lastPlayFlag = playFlag;
        lastVol = VolumeControlerScript.GetSetVolume;
    }

    public void SetActionFlag()
    {
        playFlag = !playFlag;
    }

    public void SetPauseFlag()
    {
        pauseFlag = !pauseFlag;
    }
}
