using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class ScoreMask : MonoBehaviour
{
    [SerializeField] [Header("スコアゲージ用のマスク")] private GameObject m_ImgMask;
    [SerializeField] [Header("マスクの数")] private int m_MaskNum;


    private void Start()
    {
        SettingMask();
    }
    
    /// <summary>
    /// Maskを付くる
    /// </summary>
    private void SettingMask()
    {
        
        for (int i = 0; i < m_MaskNum; i++)
        {
            GameObject Img = Instantiate(m_ImgMask);

            Transform ImgT = Img.transform;
            ImgT.position = transform.position ;
            //親子付けしてキャンバスの下に置く
            ImgT.SetParent(transform);

        }
    }

   
}
