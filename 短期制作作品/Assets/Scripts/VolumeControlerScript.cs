using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public static class VolumeControlerScript 
{
    private static bool soundFlag = true;

    public static bool GetSetVolume
    {
        get { return soundFlag; }
        set { soundFlag = value; }
    }
}
