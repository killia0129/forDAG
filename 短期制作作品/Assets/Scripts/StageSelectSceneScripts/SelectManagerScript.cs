using System.Collections;
using System.Collections.Generic;
using UnityEngine;

using System.IO;
using UnityEngine.SceneManagement;

public class SelectManagerScript : MonoBehaviour
{
    [SerializeField]private int[] stageScore = new int[6];
    [SerializeField] private Vector2 clickPos;
    private FaseName lastFase = FaseName.ON_ACTION;

    [SerializeField]private bool faseChangeFlag = false;
    private FaseName nextFase;

    [SerializeField] private float waitInput = 0.3f;
    private bool animFlag = false;

    private int selectStage;

    private bool initFaseFlag = false;
    private bool setFlag = false;

    public enum FaseName
    {
        ON_ACTION,PAUSE,FADE,END
    }



    private FadeStageSelectScript fade;
    private KunshoStageSelect[] kunsho = new KunshoStageSelect[6];
    private Lv2StageUIScript[] lv2UI = new Lv2StageUIScript[3];
    private PauseFadeStageSelectScript pauseFade;
    private PauseFadeStageSelectScript pauseSquare;
    private PauseFadeStageSelectScript volumeMarkFade;
    private PauseFadeStageSelectScript volumeMarkOutlineFade;
    private PauseFadeStageSelectScript volumeBarOutlineUpper;
    private PauseFadeStageSelectScript volumeBarOutlineLower;
    private PlayPauseButtonStageSlelect playButton;
    private PlayPauseButtonStageSlelect pauseButton;
    private ShowHiscoreScript[] hiScore = new ShowHiscoreScript[6];
    private StageCoverStageSelectScript[] cover = new StageCoverStageSelectScript[5];
    private VolumeBarStageSelectScript volumeBar;
    private VolumeIconStageSelect volumeHi;
    private VolumeIconStageSelect volumeLow;
    private VolumeMarkStageSelectScript volumeMark;
    private VolumeMarkStageSelectScript volumeMarkOutline;


    [SerializeField]FaseName fase = FaseName.ON_ACTION;
    void Start()
    {
        string path = Application.dataPath + "/SaveData/SaveData.txt";
        using(StreamReader save=new StreamReader(path,System.Text.Encoding.GetEncoding("UTF-8")))
        {
            int i = 0;
            while(save.Peek()!=-1 || i < 6)
            {
                stageScore[i] = int.Parse(save.ReadLine());
                i++;
            }
        }

        GameObject obj = GameObject.Find("Fade");
        fade = obj.GetComponent<FadeStageSelectScript>();
        obj = GameObject.Find("kunsyou1");
        kunsho[0] = obj.GetComponent<KunshoStageSelect>();
        obj = GameObject.Find("kunsyou2");
        kunsho[1] = obj.GetComponent<KunshoStageSelect>();
        obj = GameObject.Find("kunsyou3");
        kunsho[2] = obj.GetComponent<KunshoStageSelect>();
        obj = GameObject.Find("kunsyou4");
        kunsho[3] = obj.GetComponent<KunshoStageSelect>();
        obj = GameObject.Find("kunsyou5");
        kunsho[4] = obj.GetComponent<KunshoStageSelect>();
        obj = GameObject.Find("kunsyou6");
        kunsho[5] = obj.GetComponent<KunshoStageSelect>();
        obj = GameObject.Find("Stage4UI");
        lv2UI[0] = obj.GetComponent<Lv2StageUIScript>();
        obj = GameObject.Find("Stage5UI");
        lv2UI[1] = obj.GetComponent<Lv2StageUIScript>();
        obj = GameObject.Find("Stage6UI");
        lv2UI[2] = obj.GetComponent<Lv2StageUIScript>();
        obj = GameObject.Find("PauseFade");
        pauseFade = obj.GetComponent<PauseFadeStageSelectScript>();
        obj = GameObject.Find("PauseSquare");
        pauseSquare = obj.GetComponent<PauseFadeStageSelectScript>();
        obj = GameObject.Find("VolumeMark");
        volumeMarkFade = obj.GetComponent<PauseFadeStageSelectScript>();
        volumeMark = obj.GetComponent<VolumeMarkStageSelectScript>();
        obj = GameObject.Find("VolumeMarkOutline");
        volumeMarkOutlineFade = obj.GetComponent<PauseFadeStageSelectScript>();
        volumeMarkOutline = obj.GetComponent<VolumeMarkStageSelectScript>();
        obj = GameObject.Find("VolumeBarOutlineUpper");
        volumeBarOutlineUpper = obj.GetComponent<PauseFadeStageSelectScript>();
        obj = GameObject.Find("VolumeBarOutlineLower");
        volumeBarOutlineLower = obj.GetComponent<PauseFadeStageSelectScript>();
        obj = GameObject.Find("Play");
        playButton = obj.GetComponent<PlayPauseButtonStageSlelect>();
        obj = GameObject.Find("Pause");
        pauseButton = obj.GetComponent<PlayPauseButtonStageSlelect>();
        obj = GameObject.Find("Stage1Score");
        hiScore[0] = obj.GetComponent<ShowHiscoreScript>();
        obj = GameObject.Find("Stage2Score");
        hiScore[1] = obj.GetComponent<ShowHiscoreScript>();
        obj = GameObject.Find("Stage3Score");
        hiScore[2] = obj.GetComponent<ShowHiscoreScript>();
        obj = GameObject.Find("Stage4Score");
        hiScore[3] = obj.GetComponent<ShowHiscoreScript>();
        obj = GameObject.Find("Stage5Score");
        hiScore[4] = obj.GetComponent<ShowHiscoreScript>();
        obj = GameObject.Find("Stage6Score");
        hiScore[5] = obj.GetComponent<ShowHiscoreScript>();
        obj = GameObject.Find("Stage2Cover");
        cover[0] = obj.GetComponent<StageCoverStageSelectScript>();
        obj = GameObject.Find("Stage3Cover");
        cover[1] = obj.GetComponent<StageCoverStageSelectScript>();
        obj = GameObject.Find("Stage4Cover");
        cover[2] = obj.GetComponent<StageCoverStageSelectScript>();
        obj = GameObject.Find("Stage5Cover");
        cover[3] = obj.GetComponent<StageCoverStageSelectScript>();
        obj = GameObject.Find("Stage6Cover");
        cover[4] = obj.GetComponent<StageCoverStageSelectScript>();
        obj = GameObject.Find("VolumeBar");
        volumeBar = obj.GetComponent<VolumeBarStageSelectScript>();
        obj = GameObject.Find("Volume_Hi");
        volumeHi = obj.GetComponent<VolumeIconStageSelect>();
        obj = GameObject.Find("Volume_Low");
        volumeLow = obj.GetComponent<VolumeIconStageSelect>();
    }

    // Update is called once per frame
    void Update()
    {
        if (fase == FaseName.ON_ACTION)
        {
            if(initFaseFlag==false)
            {
                ToggleActionFase();
                initFaseFlag = true;
            }
            
            if (Input.GetMouseButtonDown(0) == true)
            {
                clickPos = Input.mousePosition;
                if (clickPos.x >= 17.0f && clickPos.y <= 2240.0f && clickPos.x <= 390 && clickPos.y >= 1600.0f)
                {
                    selectStage = 1;
                    fase = FaseName.FADE;
                    ToggleActionFase();
                    ToggleFadeFase();
                }

                if (clickPos.x >= 530.0f && clickPos.y <= 2240.0f && clickPos.x <= 910.0f && clickPos.y >= 1600.0f)
                {
                    if (stageScore[0] >= 70)
                    {
                        selectStage = 2;

                        fase = FaseName.FADE;
                        ToggleActionFase();
                        ToggleFadeFase();
                    }
                }

                if (clickPos.x >= 1040.0f && clickPos.y <= 2240.0f && clickPos.x <= 1420.0f && clickPos.y >= 1600.0f)
                {
                    if (stageScore[1] >= 70)
                    {
                        selectStage = 3;

                        fase = FaseName.FADE;
                        ToggleActionFase();
                        ToggleFadeFase();
                    }
                }

                if (clickPos.x >= 17.0f && clickPos.y <= 955.0f && clickPos.x <= 390 && clickPos.y >= 325.0f)
                {
                    if (stageScore[2] >= 70)
                    {
                        selectStage = 4;
                        fase = FaseName.FADE;
                        ToggleActionFase();
                        ToggleFadeFase();
                    }
                }

                if (clickPos.x >= 530.0f && clickPos.y <= 955.0f && clickPos.x <= 910.0f && clickPos.y >= 325.0f)
                {
                    if (stageScore[3] >= 70)
                    {
                        selectStage = 5;
                        fase = FaseName.FADE;
                        ToggleActionFase();
                        ToggleFadeFase();
                    }
                }

                if (clickPos.x >= 1040.0f && clickPos.y <= 955.0f && clickPos.x <= 1420.0f && clickPos.y >= 325.0f)
                {
                    if (stageScore[4] >= 70)
                    {
                        selectStage = 6;
                        fase = FaseName.FADE;
                        ToggleActionFase();
                        ToggleFadeFase();
                    }
                }
                if (clickPos.x > 1250 && clickPos.y > 2370)
                {
                    if (faseChangeFlag == false)
                    {
                        lastFase = FaseName.ON_ACTION;
                    }
                    faseChangeFlag = true;
                    nextFase = FaseName.PAUSE;
                    ToggleActionFase();
                    TogglePauseFase();
                }
            }
        }

        if(fase==FaseName.PAUSE)
        {
            
            if (Input.GetMouseButtonDown(0) == true)
            {
                clickPos = Input.mousePosition;

                if (clickPos.x >= 330.0f && clickPos.y >= 1050.0f && clickPos.x <= 1100.0f && clickPos.y <= 1220.0f)
                {
                    if (animFlag == false)
                    {
                        animFlag = true;
                        VolumeControlerScript.GetSetVolume = !VolumeControlerScript.GetSetVolume;
                    }

                }
                else if (!(clickPos.x > 200.0f && clickPos.y > 900.0f && clickPos.x < 1230.0f && clickPos.y < 1660.0f))
                {
                    nextFase = lastFase;
                    faseChangeFlag = true;
                    TogglePauseFase();
                }

            }

 

            
        }

        if (fase == FaseName.FADE)
        {
            if (fade.IsEnd == true)
            {
                faseChangeFlag = true;
                nextFase = FaseName.END;

                ToggleFadeFase();
            }
        }

        if (fase==FaseName.END)
        {
            StageNumController.SetStageNum = selectStage - 1;
            SceneManager.LoadScene("Stage");
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


        if (faseChangeFlag==true)
        {
            fase = nextFase;
            faseChangeFlag = false;
        }

        if(setFlag==false)
        {
            for(int i=0;i<6;i++)
            {
                kunsho[i].SetScore = stageScore[i];
                hiScore[i].SetScore = stageScore[i];
            }
            for(int i=0;i<3;i++)
            {
                lv2UI[i].SetScore = stageScore[i+2];
            }
            for(int i=0;i<5;i++)
            {
                cover[i].SetScore = stageScore[i];
            }
        }
    }


    public FaseName GetSetFase
    {
        get { return fase; }
        set { fase = value; }
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

    private void TogglePauseFase()
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
