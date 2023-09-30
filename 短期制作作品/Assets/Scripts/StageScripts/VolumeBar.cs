using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class VolumeBar : MonoBehaviour
{
    Color color;

    private bool lastVol = true;
    [SerializeField] private float animTime = 0.3f;
    private float alfa = 1.0f;
    [SerializeField] private bool animFlag = false;
    private bool changeVolOffFlag = true;

    private bool pauseFlag = false;
    private bool lastFasePoseFlag = false;

    // Start is called before the first frame update
    void Start()
    {
        color = this.GetComponent<SpriteRenderer>().color;
    }

    // Update is called once per frame
    void Update()
    {
        if (pauseFlag==true)
        {
            if (lastFasePoseFlag==false)
            {
                if (VolumeControlerScript.GetSetVolume == true)
                {
                    color.a = 1.0f;
                    alfa = 1.0f;
                }
                else
                {
                    color.a = 0.0f;
                    alfa = 0.0f;
                }
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
                    alfa -= Time.deltaTime / animTime;
                    if (alfa < 0.0f)
                    {
                        alfa = 0.0f;
                        animFlag = false;
                    }
                    color.a = alfa;
                }
                else
                {
                    alfa += Time.deltaTime / animTime;
                    if (alfa > 1.0f)
                    {
                        alfa = 1.0f;
                        animFlag = false;
                    }
                    color.a = alfa;
                }

            }
        }
        else
        {
            color.a = 0.0f;

        }
        this.GetComponent<SpriteRenderer>().color = color;

        lastVol = VolumeControlerScript.GetSetVolume;
        lastFasePoseFlag = pauseFlag;
    }

    public void SetPauseFlag()
    {
        pauseFlag = !pauseFlag;
    }
}
