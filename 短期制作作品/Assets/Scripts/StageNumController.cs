using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public static class StageNumController
{
    private static int stageNum = 1;

    public static int GetStageNum
    {
        get { return stageNum; }
    }

    public static int SetStageNum
    {
        set { stageNum = value; }
    }

}
