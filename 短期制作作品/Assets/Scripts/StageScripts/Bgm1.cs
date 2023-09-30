using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Bgm1 : MonoBehaviour
{
    private AudioSource audio = new AudioSource();
    private float volume;
    private float defaultVolume;
    private int stageNum;
    [SerializeField]private int BGMNum;

    // Start is called before the first frame update
    void Start()
    {
        audio = this.GetComponent<AudioSource>();
        volume = audio.volume;
        defaultVolume = volume;
        stageNum = StageNumController.GetStageNum;
    }

    // Update is called once per frame
    void Update()
    {
        if (stageNum == BGMNum || stageNum == BGMNum + 3)
        {
            if (VolumeControlerScript.GetSetVolume == true)
            {
                volume = defaultVolume;
            }
            else
            {
                volume = 0.0f;
            }
        }
        else
        {
            volume = 0.0f;
        }
        audio.volume = volume;

    }
}
