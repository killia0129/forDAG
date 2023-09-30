using System.Collections;
using System.Collections.Generic;
using UnityEngine;


using UnityEngine.SceneManagement;

public class TitleManagerScript : MonoBehaviour
{
    public enum FaseName
    {
        ON_ACTION,PAUSE,FADE,END
    }

    [SerializeField]private FaseName fase = FaseName.ON_ACTION;
    private Vector2 moucePos;
    private FaseName lastFase = FaseName.ON_ACTION;

    [SerializeField] Vector2 debugMoucePos;

    private bool faseChangeFlag = false;
    private FaseName nextFase;

    [SerializeField]private float waitInput = 0.3f;
    private bool animFlag = false;

    private bool initFaseFlag = false;


    private FadeTitleScript fade;
    private PauseFadeTitleScript pauseFade;
    private PauseFadeTitleScript pauseSquare;
    private PauseFadeTitleScript volumeMarkFade;
    private PauseFadeTitleScript volumeMarkOutlineFade;
    private PauseFadeTitleScript volumeBarOutlineUpper;
    private PauseFadeTitleScript volumeBarOutlineLower;
    private PlayPauseButtonTitle playButton;
    private PlayPauseButtonTitle pauseButton;
    private VolumeBarTitleScript volumeBar;
    private VolumeIconTitle volumeHi;
    private VolumeIconTitle volumeLow;
    private VolumeMarkTitleScript volumeMark;
    private VolumeMarkTitleScript volumeMarkOutline;


    // Start is called before the first frame update
    void Start()
    {
        GameObject obj = GameObject.Find("Fade");
        fade = obj.GetComponent<FadeTitleScript>();
        obj = GameObject.Find("PauseFade");
        pauseFade = obj.GetComponent<PauseFadeTitleScript>();
        obj = GameObject.Find("PauseSquare");
        pauseSquare = obj.GetComponent<PauseFadeTitleScript>();
        obj = GameObject.Find("VolumeMark");
        volumeMarkFade = obj.GetComponent<PauseFadeTitleScript>();
        volumeMark = obj.GetComponent<VolumeMarkTitleScript>();
        obj = GameObject.Find("VolumeMarkOutline");
        volumeMarkOutlineFade = obj.GetComponent<PauseFadeTitleScript>();
        volumeMarkOutline = obj.GetComponent<VolumeMarkTitleScript>();
        obj = GameObject.Find("VolumeBarOutlineUpper");
        volumeBarOutlineUpper = obj.GetComponent<PauseFadeTitleScript>();
        obj = GameObject.Find("VolumeBarOutlineLower");
        volumeBarOutlineLower = obj.GetComponent<PauseFadeTitleScript>();
        obj = GameObject.Find("Play");
        playButton = obj.GetComponent<PlayPauseButtonTitle>();
        obj = GameObject.Find("Pause");
        pauseButton = obj.GetComponent<PlayPauseButtonTitle>();
        obj = GameObject.Find("VolumeBar");
        volumeBar = obj.GetComponent<VolumeBarTitleScript>();
        obj = GameObject.Find("Volume_Hi");
        volumeHi = obj.GetComponent<VolumeIconTitle>();
        obj = GameObject.Find("Volume_Low");
        volumeLow = obj.GetComponent<VolumeIconTitle>();
    }

    // Update is called once per frame
    void Update()
    {
        debugMoucePos = Input.mousePosition;

        if(initFaseFlag==false)
        {
            ToggleActionFase();
            initFaseFlag = true;
        }
        if(fase==FaseName.ON_ACTION)
        {
            if(Input.GetMouseButtonDown(0)==true)
            {
                moucePos = Input.mousePosition;
                if(moucePos.x>1250&&moucePos.y>2370)
                {
                    if(faseChangeFlag==false)
                    {
                        lastFase = FaseName.ON_ACTION;
                    }
                    faseChangeFlag = true;
                    nextFase = FaseName.PAUSE;

                    ToggleActionFase();
                    TogglePauseFlag();
                }
                else
                {
                    faseChangeFlag = true;
                    nextFase = FaseName.FADE;

                    ToggleActionFase();
                    ToggleFadeFase();
                }
            }
        }

        if(fase==FaseName.FADE)
        {
            if(fade.IsEnd==true)
            {
                nextFase = FaseName.END;
                faseChangeFlag = true;
            }
        }

        if(fase==FaseName.END)
        {
            SceneManager.LoadScene("StageSelectScene");
        }

        if(fase==FaseName.PAUSE)
        {
            if(Input.GetMouseButtonDown(0)==true)
            {
                moucePos = Input.mousePosition;

                if(moucePos.x>=330.0f&&moucePos.y>=1050.0f&&moucePos.x<=1100.0f&&moucePos.y<=1220.0f)
                {
                    if(animFlag == false)
                    {
                        animFlag = true;
                        VolumeControlerScript.GetSetVolume = !VolumeControlerScript.GetSetVolume;
                    }
                    
                }
                else if(!(moucePos.x>200.0f&&moucePos.y>900.0f&&moucePos.x<1230.0f&&moucePos.y<1660.0f))
                {
                    nextFase = lastFase;
                    faseChangeFlag = true;

                    ToggleActionFase();
                    TogglePauseFlag();
                }
            }

            if(animFlag==true)
            {
                waitInput -= Time.deltaTime / 3.0f * 10.0f;
                if (waitInput <= 0.0f)
                {
                    waitInput = 3.0f;
                    animFlag = false;
                }
            }
        }

        if(faseChangeFlag==true)
        {
            if(Input.GetMouseButtonUp(0)==true||nextFase==FaseName.END)
            {
                fase = nextFase;
                faseChangeFlag = false;
            }
        }
    }

    private void ToggleActionFase()
    {
        volumeBar.SetActionFlag();
        volumeMark.SetActionFlag();
        volumeMarkOutline.SetActionFlag();
    }

    private void ToggleFadeFase()
    {
        fade.SetFadeFlag();
    }

    private void TogglePauseFlag()
    {
        pauseFade.SetPauseFase();
        pauseSquare.SetPauseFase();
        volumeMarkFade.SetPauseFase();
        volumeMarkOutlineFade.SetPauseFase();
        volumeBarOutlineUpper.SetPauseFase();
        volumeBarOutlineLower.SetPauseFase();
        playButton.SetPauseFase();
        pauseButton.SetPauseFase();
        volumeBar.SetPauseFlag();
        volumeHi.SetPauseFlag();
        volumeLow.SetPauseFlag();
        volumeMark.SetPauseFlag();
        volumeMarkOutline.SetPauseFlag();
    }
}
