using System.Collections;
using System.Collections.Generic;
using UnityEngine;

using UnityEngine.SceneManagement;

public class ManagerScript : MonoBehaviour
{
    private int stageNum;

    [SerializeField] private Vector2 clickPos;
    private TargetMarker target;              
    [SerializeField] private Vector2 decidedTargetPos;
    private Vector2 midToMarkerDis;
    private Vector2 midPos = new Vector2(0.0f, -2.0f);
    private float dis;
    private bool hit = false;

    private FaseName lastFase = FaseName.ON_ACTION;


    private bool faseChangeFlag = false;
    private FaseName nextFase;

    [SerializeField] private float waitInput = 0.3f;
    private bool animFlag = false;

    private ResultTarget targetR;             
    [SerializeField] private float showTime = 1.0f;

    [SerializeField] private float timer = 30.0f;
    private bool timeOutFlag = false;
    public enum FaseName
    {
        START, ON_ACTION, DECIDED_MARKER, END, PAUSE, FADE, RETURN, SHOW, ZOOMOUT, SHUCHU
    }

    [SerializeField] private FaseName fase = FaseName.SHOW;


    private CameraManager camera;
    private Shuchu shuchu;
    private Hand hand;
    private Fade fade;
    private Count count;
    private Particle particle;
    private PinchedObject star;
    private PinchedObject ICCard;
    private PinchedObject katsura;
    private PinchedObject katsuraBack;
    private PlayPauseButton playButton;
    private PlayPauseButton pauseButton;
    private PauseFade pauseFade;
    private PauseFade pauseSquare;
    private PauseFade volumeMarkFade;
    private PauseFade volumeMarkOutlineFade;
    private PauseFade volumeBarUpper;
    private PauseFade volumeBarLower;
    private ResultSE parfectSE;
    private ResultSE niceSE;
    private ResultTarget resultTarget;
    private ResultTarget resultTargetBigger;
    private ResultTargetMarker resultTargetMarker;
    private Sad sad;
    private ScoreText scoreText;
    private Show show;
    private ShowStageName showStage;
    private StartText startText;
    private StopWatch stopWatch;
    private TargetMarker targetMarker;
    private TargetObject tree;
    private TargetObject kaisatsu;
    private TargetObject man;
    private TargetObject fire1;
    private TargetObject fire2;
    private TargetObject fire3;
    private VolumeBar volumeBar;
    private VolumeIcon volumeHi;
    private VolumeIcon volumeLow;
    private VolumeMark volumeMark;
    private VolumeMark volumeMarkOutline;

    private bool toggleShowFlag = false;


    void Start()
    {
        stageNum = StageNumController.GetStageNum;
        GameObject obj = GameObject.Find("TargetMarker");
        target = obj.GetComponent<TargetMarker>();
        obj = GameObject.Find("ResultTarget");
        targetR = obj.GetComponent<ResultTarget>();
        if(stageNum==0||stageNum==3)
        {
            midPos = new Vector2(0.0f, -2.0f);
        }
        else if(stageNum == 1 || stageNum == 4)
        {
            midPos = new Vector2(1.0f, -2.0f);
        }
        else if(stageNum == 2 || stageNum == 5)
        {
            midPos = new Vector2(0.0f, -2.0f);
        }

        obj = GameObject.Find("MainCamera");
        camera = obj.GetComponent<CameraManager>();
        obj = GameObject.Find("Shuchu");
        shuchu = obj.GetComponent<Shuchu>();
        obj = GameObject.Find("hand");
        hand = obj.GetComponent<Hand>();
        obj = GameObject.Find("Fade");
        fade = obj.GetComponent<Fade>();
        obj = GameObject.Find("Count");
        count = obj.GetComponent<Count>();
        obj = GameObject.Find("ParticleSystem");
        particle = obj.GetComponent<Particle>();
        obj = GameObject.Find("StarOnly");
        star = obj.GetComponent<PinchedObject>();
        obj = GameObject.Find("ICCard");
        ICCard = obj.GetComponent<PinchedObject>();
        obj = GameObject.Find("katsura_main");
        katsura = obj.GetComponent<PinchedObject>();
        obj = GameObject.Find("katsura_back");
        katsuraBack = obj.GetComponent<PinchedObject>();
        obj = GameObject.Find("Play");
        playButton = obj.GetComponent<PlayPauseButton>();
        obj = GameObject.Find("Pause");
        pauseButton = obj.GetComponent<PlayPauseButton>();
        obj = GameObject.Find("PauseFade");
        pauseFade = obj.GetComponent<PauseFade>();
        obj = GameObject.Find("PauseSquare");
        pauseSquare = obj.GetComponent<PauseFade>();
        obj = GameObject.Find("VolumeMark");
        volumeMarkFade = obj.GetComponent<PauseFade>();
        obj = GameObject.Find("VolumeMarkOutline");
        volumeMarkOutlineFade = obj.GetComponent<PauseFade>();
        obj = GameObject.Find("VolumeBarOutlineUpper");
        volumeBarUpper = obj.GetComponent<PauseFade>();
        obj = GameObject.Find("VolumeBarOutlineLower");
        volumeBarLower = obj.GetComponent<PauseFade>();
        obj = GameObject.Find("ParfectSE");
        parfectSE = obj.GetComponent<ResultSE>();
        obj = GameObject.Find("NiceSE");
        niceSE = obj.GetComponent<ResultSE>();
        obj = GameObject.Find("ResultTarget");
        resultTarget = obj.GetComponent<ResultTarget>();
        obj = GameObject.Find("ResultTargetBigger");
        resultTargetBigger = obj.GetComponent<ResultTarget>();
        obj = GameObject.Find("ResultTargetMark");
        resultTargetMarker = obj.GetComponent<ResultTargetMarker>();
        obj = GameObject.Find("sad");
        sad = obj.GetComponent<Sad>();
        obj = GameObject.Find("Score");
        scoreText = obj.GetComponent<ScoreText>();
        obj = GameObject.Find("ShowBack");
        show = obj.GetComponent<Show>();
        obj = GameObject.Find("StageName");
        showStage = obj.GetComponent<ShowStageName>();
        obj = GameObject.Find("Start");
        startText = obj.GetComponent<StartText>();
        obj = GameObject.Find("stopwatch");
        stopWatch = obj.GetComponent<StopWatch>();
        obj = GameObject.Find("TargetMarker");
        targetMarker = obj.GetComponent<TargetMarker>();
        obj = GameObject.Find("TreeOnly");
        tree = obj.GetComponent<TargetObject>();
        obj = GameObject.Find("kaisatsu");
        kaisatsu = obj.GetComponent<TargetObject>();
        obj = GameObject.Find("hair_usuge_young");
        man = obj.GetComponent<TargetObject>();
        obj = GameObject.Find("Fire1");
        fire1 = obj.GetComponent<TargetObject>();
        obj = GameObject.Find("Fire2");
        fire2 = obj.GetComponent<TargetObject>();
        obj = GameObject.Find("Fire3");
        fire3 = obj.GetComponent<TargetObject>();
        obj = GameObject.Find("VolumeBar");
        volumeBar = obj.GetComponent<VolumeBar>();
        obj = GameObject.Find("Volume_Hi");
        volumeHi = obj.GetComponent<VolumeIcon>();
        obj = GameObject.Find("Volume_Low");
        volumeLow = obj.GetComponent<VolumeIcon>();
        obj = GameObject.Find("VolumeMark");
        volumeMark = obj.GetComponent<VolumeMark>();
        obj = GameObject.Find("VolumeMarkOutline");
        volumeMarkOutline = obj.GetComponent<VolumeMark>();
    }

    void Update()
    {
        if(toggleShowFlag==false)
        {
            ToggleShowScene();
            toggleShowFlag = true;
        }
        if (fase == FaseName.SHOW)
        {
            showTime -= Time.deltaTime;
            if (showTime < 0.0f)
            {
                nextFase = FaseName.ZOOMOUT;
                faseChangeFlag = true;

                ToggleZoomScene();
                ToggleShowScene();
            }
        }
        if(fase==FaseName.ZOOMOUT)
        {
            
            if (camera.IsEnd == true)
            {
                faseChangeFlag = true;
                nextFase = FaseName.SHUCHU;

                ToggleZoomScene();
                ToggleShuchuScene();
            }

        }
        if(fase==FaseName.SHUCHU)
        {
            if(shuchu.IsEnd==true)
            {
                faseChangeFlag = true;
                nextFase = FaseName.START;

                ToggleShuchuScene();
                ToggleStartScene();
            }
        }

        if (fase == FaseName.START)
        {
            if (Input.GetMouseButtonDown(0))
            {
                clickPos = Input.mousePosition;
                if (clickPos.x > 1250.0f && clickPos.y > 2370.0f)
                {
                    nextFase = FaseName.PAUSE;
                    lastFase = FaseName.START;
                    faseChangeFlag = true;

                    ToggleStartScene();
                    TogglePauseScene();
                }
            }
            if(target.IsEnd==true)
            {
                faseChangeFlag = true;
                nextFase = FaseName.ON_ACTION;

                ToggleStartScene();
                ToggleActionScene();
            }
        }
        if (fase == FaseName.ON_ACTION)
        {
            timer -= Time.deltaTime;
            if (Input.GetMouseButtonDown(0))
            {
                clickPos = Input.mousePosition;
                if (!(clickPos.x > 1250.0f && clickPos.y > 2370.0f))
                {
                    nextFase = FaseName.DECIDED_MARKER;
                    faseChangeFlag = true;

                    ToggleActionScene();
                    ToggleDecidedScene();
                }
                else
                {
                    nextFase = FaseName.PAUSE;
                    lastFase = FaseName.ON_ACTION;
                    faseChangeFlag = true;

                    ToggleActionScene();
                    TogglePauseScene();
                }
            }
            if (timer <= 0.0f)
            {
                nextFase = FaseName.DECIDED_MARKER;
                faseChangeFlag = true;
                timeOutFlag = true;

                ToggleActionScene();
                ToggleDecidedScene();
            }
        }
        if (fase == FaseName.DECIDED_MARKER)
        {
            decidedTargetPos = target.GetPos;
            midToMarkerDis = midPos - decidedTargetPos;
            midToMarkerDis.y *= 1.2f / 0.5f;
            midToMarkerDis *= 1.0f / 1.2f;
            dis = Mathf.Sqrt(Mathf.Pow(midToMarkerDis.x, 2.0f) + Mathf.Pow(midToMarkerDis.y, 2.0f));
            if (stageNum == 0 || stageNum == 3)
            {
                if (Mathf.Asin(midToMarkerDis.y / dis) >= Mathf.Sin(0.25f * Mathf.PI)
                    && (Mathf.Acos(midToMarkerDis.y / dis) >= -Mathf.Sin(0.25f * Mathf.PI)
                    && Mathf.Acos(midToMarkerDis.y / dis) <= Mathf.Sin(0.25f * Mathf.PI)))
                {
                    hit = true;
                }
            }
            if(stageNum==1||stageNum==4)
            {
                if (midToMarkerDis.y >= 0.0f && midToMarkerDis.y <= 2.0f && dis <= 2.0f)
                {
                    hit = true;
                }
            }
            if(stageNum==2||stageNum==5)
            {
                if (midToMarkerDis.y <= 2.0f && midToMarkerDis.y >= 0.0f && dis < 2.0f)
                {
                    hit = true;
                }
            }

            if (Input.GetMouseButton(0))
            {
                clickPos = Input.mousePosition;
                if (clickPos.x > 1250.0f && clickPos.y > 2370.0f)
                {
                    nextFase = FaseName.PAUSE;
                    lastFase = FaseName.DECIDED_MARKER;
                    faseChangeFlag = true;

                    ToggleDecidedScene();
                    TogglePauseScene();
                }
            }

            if(hand.IsEnd==true)
            {
                nextFase = FaseName.END;
                faseChangeFlag = true;

                ToggleDecidedScene();
                ToggleEndScene();
            }
        }
        if (fase == FaseName.END)
        {
            
            resultTargetMarker.SetDis = midToMarkerDis;
            scoreText.SetDis = dis;
            if (Input.GetMouseButtonDown(0) == true)
            {
                clickPos = Input.mousePosition;
                if (clickPos.x > 1250.0f && clickPos.y > 2370.0f)
                {
                    nextFase = FaseName.PAUSE;
                    lastFase = FaseName.END;
                    faseChangeFlag = true;

                    ToggleEndScene();
                    TogglePauseScene();
                }
            }

            if (targetR.GetPos.y >= 0.0f)
            {
                if (Input.GetMouseButtonDown(0) == true)
                {
                    clickPos = Input.mousePosition;
                    if (!(clickPos.x > 1250.0f && clickPos.y > 2370.0f))
                    {
                        nextFase = FaseName.FADE;
                        faseChangeFlag = true;

                        ToggleEndScene();
                        ToggleFadeScene();
                    }
                    
                }
            }
        }

        if (fase == FaseName.PAUSE)
        {
            if (Input.GetMouseButtonDown(0) == true)
            {
                Vector2 moucePos = Input.mousePosition;

                if (moucePos.x >= 330.0f && moucePos.y >= 1050.0f && moucePos.x <= 1100.0f && moucePos.y <= 1220.0f)
                {
                    if (animFlag == false)
                    {
                        animFlag = true;
                        VolumeControlerScript.GetSetVolume = !VolumeControlerScript.GetSetVolume;
                    }

                }
                else if (!(moucePos.x > 200.0f && moucePos.y > 900.0f && moucePos.x < 1230.0f && moucePos.y < 1660.0f))
                {
                    nextFase = lastFase;
                    faseChangeFlag = true;

                    switch(lastFase)
                    {
                        case FaseName.START:
                            ToggleStartScene();
                            break;

                        case FaseName.ON_ACTION:
                            ToggleActionScene();
                            break;

                        case FaseName.DECIDED_MARKER:
                            ToggleDecidedScene();
                            break;

                        case FaseName.END:
                            ToggleEndScene();
                            break;

                        default:
                            break;
                    }
                    TogglePauseScene();
                }
            }

            if (animFlag == true)
            {
                waitInput -= Time.deltaTime / 3.0f * 10.0f;
                if (waitInput <= 0.0f)
                {
                    waitInput = 3.0f;
                    animFlag = false;
                }
            }
        }

        if(fase==FaseName.FADE)
        {
            if(fade.IsEnd==true)
            {
                faseChangeFlag = true;
                nextFase = FaseName.RETURN;

                ToggleFadeScene();
            }
        }

        if (fase == FaseName.RETURN)
        {
            SceneManager.LoadScene("StageSelectScene");
        }

        if (faseChangeFlag == true)
        {
            if (Input.GetMouseButtonUp(0) == true 
                || nextFase == FaseName.ZOOMOUT 
                || timeOutFlag == true
                || nextFase == FaseName.START
                || nextFase == FaseName.SHUCHU
                || nextFase == FaseName.END 
                || nextFase == FaseName.ON_ACTION 
                || nextFase == FaseName.RETURN)
            {
                if(fase==FaseName.PAUSE)
                {
                    if(Input.GetMouseButtonUp(0) == true)
                    {
                        fase = nextFase;
                        faseChangeFlag = false;
                    }
                }
                else
                {
                    fase = nextFase;
                    faseChangeFlag = false;
                }
                
            }
            if (timeOutFlag == true)
            {
                timeOutFlag = false;
            }
        }

        scoreText.SetHit = hit;
        count.SetTime = (int)timer;
    }

    
    private void ToggleShowScene()
    {
        playButton.SetShowFlag();
        pauseButton.SetShowFlag();
        show.SetShowFlag();
        showStage.SetShowFlag();
    }

    private void ToggleZoomScene()
    {
        camera.SetPlayFlag();
        shuchu.SetZoomFlag();

    }
    private void ToggleShuchuScene()
    {
        shuchu.SetShuchuFlag();
    }

    private void ToggleStartScene()
    {
        count.SetStartFlag();
        hand.SetStartFlag();
        stopWatch.SetStartFlag();
        targetMarker.SetStartFlag();
    }

    private void ToggleActionScene()
    {
        hand.SetActionFlag();
        startText.SetActionFlag();
        targetMarker.SetActionFlag();
        volumeMark.SetActionFlag();
        volumeMarkOutline.SetActionFlag();
    }

    private void ToggleDecidedScene()
    {
        count.SetDecidedFlag();
        hand.SetDecidedFlag();
        stopWatch.SetDecidedFlag();
        targetMarker.SetDecidedFlag();
    }

    private void ToggleEndScene()
    {
        hand.SetEndFlag();
        particle.SetEndFlag();
        star.SetEndFlag();
        ICCard.SetEndFlag();
        katsura.SetEndFlag();
        katsuraBack.SetEndFlag();
        parfectSE.SetEndFlag();
        niceSE.SetEndFlag();
        resultTarget.SetEndFlag();
        resultTargetBigger.SetEndFlag();
        resultTargetMarker.SetEndFlag();
        sad.SetEndFlag();
        scoreText.SetEndFlag();
        tree.SetEndFlag();
        kaisatsu.SetEndFlag();
        man.SetEndFlag();
        fire1.SetEndFlag();
        fire2.SetEndFlag();
        fire3.SetEndFlag();
    }

    private void ToggleFadeScene()
    {
        fade.SetFadeFlag();
    }

    private void TogglePauseScene()
    {
        playButton.SetPauseFlag();
        pauseButton.SetPauseFlag();
        pauseFade.SetPauseFlag();
        pauseSquare.SetPauseFlag();
        volumeMarkFade.SetPauseFlag();
        volumeMarkOutlineFade.SetPauseFlag();
        volumeBarUpper.SetPauseFlag();
        volumeBarLower.SetPauseFlag();
        volumeBar.SetPauseFlag();
        volumeHi.SetPauseFlag();
        volumeLow.SetPauseFlag();
        volumeMark.SetPauseFlag();
        volumeMark.SetPauseFlag();
    }
}