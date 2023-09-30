using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Pointer : MonoBehaviour
{
    [SerializeField] [Header("移動限界")] private float LimmitX;
    [SerializeField] [Header("移動限界")] private float LimmitY;
    [SerializeField] [Header("gimmick管理場")] private GimmickSelectPart m_GimmickSelectPart;
    [SerializeField] [Header("カメラ")]　private Camera camera;
    [SerializeField] [Header("入力情報ゲッター")] private InputControllerBase InputGetter;
    [SerializeField] [Header("エフェクト")] private GameObject m_ClickEffect;
    [SerializeField] [Header("移動速度")] [Range(0.5f,1000.0f)] private float MoveSpeed;
    //操作用ポインタ
    Vector3 m_TruePointerPosition;
    AudioSource m_Audio;
    //仮操作用兼描画ポインタ
    Vector3 m_PointerPosition;

    bool m_IsPut;
    InputParameter m_InputParam;
    [SerializeField] SpriteRenderer m_Sprite;
    [SerializeField] SpriteRenderer m_FaiceSprite;

    private GameObject m_gimmickObj;

    // Start is called before the first frame update
    void Start()
    {
        m_TruePointerPosition = new Vector3(0, 0, 0);
        gameObject.transform.position = m_TruePointerPosition;
        m_IsPut = false;
        m_Audio = GetComponent<AudioSource>();
    }
    private void OnEnable()
    {
        m_IsPut = false;
        m_gimmickObj = null;
    }
    void Update()
    {
        m_InputParam = InputGetter.GetInputParam();
        //ポインタ操作
        var InputVec = new Vector3(m_InputParam.m_LStickHValue * 0.01f, m_InputParam.m_LStickVValue * 0.01f,0.0f);
        m_TruePointerPosition += InputVec * MoveSpeed * Time.deltaTime ;

        // //エリア指定して移動する
        m_TruePointerPosition = new Vector3(Mathf.Clamp(m_TruePointerPosition.x, -LimmitX, LimmitX), Mathf.Clamp(m_TruePointerPosition.y, -LimmitY, LimmitY), 0);
        transform.position = m_TruePointerPosition;
        //Debug.Log(m_TruePointerPosition);
    }
    private void Hide()
    {
        Color color = m_Sprite.color;
        color.a = 0;
        m_Sprite.color = color;
        m_FaiceSprite.color = color;
        m_Audio.Play();
        Instantiate(m_ClickEffect, transform.position,m_ClickEffect.transform.rotation);
    }

    /// <summary>
    ///選択時にプレイヤーの操作を管轄するクラスに呼ばれる 
    /// </summary>
    public void SelectMove()
    {
        Color color = m_Sprite.color;
        color.a = 255;
        m_Sprite.color = color;
        m_FaiceSprite.color = color;
        m_InputParam = InputGetter.GetInputParam();
        //レイを飛ばしてギミック選択
        Ray ray = Camera.main.ScreenPointToRay(camera.WorldToScreenPoint(m_TruePointerPosition));

        RaycastHit2D hit2d = Physics2D.Raycast((Vector2)ray.origin, (Vector2)ray.direction);

        if (hit2d)
        {
            if (m_InputParam.m_AButton)
            {

                //ギミックベースかどうかの判定
                var GimmickBase = hit2d.transform.gameObject.GetComponent<GimmickBase>();
                if (GimmickBase && !m_gimmickObj) 
                {
                    GimmickBase.OnUpdatePutState();
                    //真なら取得
                    m_gimmickObj = GimmickBase.gameObject;
                    GimmickBase.OnUpperOrHide(false);
                    Hide();
                }
            }

        }
    }
    //置く状態
    public void PutUpdate()
    {
        m_InputParam = InputGetter.GetInputParam();
        m_gimmickObj.GetComponent<GimmickBase>().OnUpperOrHide(true);
        Color color = m_Sprite.color;
        color.a = 255;
        m_Sprite.color = color;
        m_FaiceSprite.color = color;


        var TmpCursol = camera.WorldToScreenPoint(m_TruePointerPosition);
        m_PointerPosition = TmpCursol;
        //グリッド線の範囲内にマウスポインタが存在している場合
        //if (640 < TmpCursol.x && 1280 > TmpCursol.x)
        {
            var over = TmpCursol.x % 64;
            m_PointerPosition.x -= over;
            over = TmpCursol.y % 64;
            m_PointerPosition.y -= over;
            //ギミックの基本機能を所得
            GimmickBase gimmick = m_gimmickObj.GetComponent<GimmickBase>();
            //LRを押したら回転
            if (m_InputParam.m_LButton)
            {

                gimmick.PitchRotate(true);
            }
            if (m_InputParam.m_RButton)
            {
                gimmick.PitchRotate(false);
            }
            //Aボタンを押して何かとかぶっていないなら
            if (m_InputParam.m_AButton &&
                !gimmick.GetOverLap()&&
                gimmick.GetPutState()==GimmickPutState.Put) 
            {
                gimmick.OnUpdatePutState();
                m_GimmickSelectPart.OnRecieveGimmick(m_gimmickObj.GetComponent<GimmickBase>());
                Hide();
                gameObject.SetActive(false);

            }
            if(m_gimmickObj.GetComponent<GimmickBase>().GetOverLap())
            {
            }
        }
        if(!m_IsPut)
        {
            m_gimmickObj.transform.position = camera.ScreenToWorldPoint(m_PointerPosition);
        }

    }





    public GameObject GetSelectGimmick()
    {
        return m_gimmickObj;
    }

}
