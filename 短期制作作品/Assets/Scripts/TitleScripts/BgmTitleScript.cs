using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BgmTitleScript : MonoBehaviour
{
    private AudioSource audio = new AudioSource();
    private float volume;
    
    // Start is called before the first frame update
    void Start()
    {
        audio = this.GetComponent<AudioSource>();
        volume = audio.volume;
    }

    // Update is called once per frame
    void Update()
    {
        if(VolumeControlerScript.GetSetVolume==true)
        {
            volume = 0.1f;
        }
        else
        {
            volume = 0.0f;
        }
        audio.volume = volume;

    }
}
