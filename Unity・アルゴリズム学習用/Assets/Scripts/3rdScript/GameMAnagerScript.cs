using System.Collections;
using System.Collections.Generic;
using UnityEngine;

using System;

public class GameMAnagerScript : MonoBehaviour
{
    enum FASE
    {
        START,ON_ACTION,END,RESET
    }

    FASE fase = FASE.START;
    [SerializeField]float time = 0.0f;
    bool keyUpFlag = true;
    bool setTimeFlag = false;
    UnityEngine.KeyCode keycode;
    int parfectTime;
    FASE nextFase;
    bool faseChangeFlag;
    bool successFlag = false;

    ParfectTimeScript pTime;
    StopWatchScript stopWatch;
    SuccessScript success;

    // Start is called before the first frame update
    void Start()
    {
        GameObject obj = GameObject.Find("Time");
        pTime = obj.GetComponent<ParfectTimeScript>();
        obj = GameObject.Find("StopWatch");
        stopWatch = obj.GetComponent<StopWatchScript>();
        obj = GameObject.Find("Success");
        success = obj.GetComponent<SuccessScript>();
    }

    // Update is called once per frame
    void Update()
    {
        stopWatch.SetTime = time;
        pTime.SetParfectTime = parfectTime;
        success.SetSuccessFlag = successFlag;
        if(fase==FASE.START)
        {
            if(setTimeFlag==false)
            {
                parfectTime = UnityEngine.Random.Range(5, 15);
                setTimeFlag = true;
            }
            if(Input.anyKeyDown==true)
            {
                foreach (KeyCode code in Enum.GetValues(typeof(KeyCode)))
                {
                    if (Input.GetKeyDown(code)==true)
                    {
                        keycode = code;
                        keyUpFlag = false;
                        nextFase = FASE.ON_ACTION;
                        faseChangeFlag = true;
                        stopWatch.SetActionFlag();
                        break;
                    }
                }
            }
        }

        if(fase==FASE.ON_ACTION)
        {
            if(Input.GetKey(keycode)!=true)
            {
                keyUpFlag = true;
            }
            foreach (KeyCode code in Enum.GetValues(typeof(KeyCode)))
            {
                if (Input.GetKeyDown(code) == true)
                {
                    keycode = code;
                    keyUpFlag = false;
                    nextFase = FASE.END;
                    faseChangeFlag = true;
                    stopWatch.SetActionFlag();
                    break;
                }
            }
            time += Time.deltaTime;

        }

        if(fase==FASE.END)
        {
            if (Input.GetKey(keycode) != true)
            {
                keyUpFlag = true;
            }
            if ((int)time>parfectTime-1&& (int)time < parfectTime + 1)
            {
                successFlag = true;
            }
            foreach (KeyCode code in Enum.GetValues(typeof(KeyCode)))
            {
                if (Input.GetKeyDown(code) == true)
                {
                    keycode = code;
                    keyUpFlag = false;
                    nextFase = FASE.RESET;
                    faseChangeFlag = true;
                    break;
                }
            }
        }

        if(fase==FASE.RESET)
        {
            if (Input.GetKey(keycode) != true)
            {
                keyUpFlag = true;
            }
            if(keyUpFlag==true)
            {
                setTimeFlag = false;
                time = 0.0f;
                nextFase = FASE.START;
                faseChangeFlag = true;
                successFlag = false;
            }
        }

        if(faseChangeFlag==true)
        {
            fase = nextFase;
        }
    }
}
