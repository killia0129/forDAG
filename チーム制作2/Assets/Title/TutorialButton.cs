using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TutorialButton : UIBase
{
    [SerializeField] [Header("チュートリアル再生するオブジェクトをください")] GameObject m_TutorialObj;
    GameObject Tutorial;
    override public void OnRun()
    {
        if (!Tutorial)
        {
            m_Audios.Play();
            Tutorial = Instantiate(m_TutorialObj);
        }
    }
}
