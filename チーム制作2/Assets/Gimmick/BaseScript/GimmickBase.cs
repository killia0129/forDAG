using System.Collections;
using System.Collections.Generic;
using UnityEngine;

/// <summary>
/// 設置アイテムの親クラス
/// </summary>
public class GimmickBase : MonoBehaviour
{
    [SerializeField] protected BoxCollider2D m_Collider;
    [SerializeField] protected SpriteRenderer m_Sprite;
    protected GimmickPutState m_PutState = GimmickPutState.Select;
    private const float m_RotateAngle = 90.0f; //回転角
    private MainState MainState;
    protected bool m_IsOvarlap = false;
    protected bool m_IsSelfDestroy = false;
    protected bool m_IsPrepareDestroy = false;//破壊準備
    /*to do どのプレイヤーの所有物か決める変数を設定する。*/

    private void LateUpdate()
    {
        if (m_IsSelfDestroy)
        {
            Destroy(this.gameObject);
        }
    }
    /// <summary>
    /// ハンマーが置かれたら自滅準備
    /// </summary>
    /// <param name="_Hammer"></param>
    protected void TriggerEvenet(GameObject _Hammer)
    {
        if (_Hammer.CompareTag("hammer"))
        {
            //設置後の自分自身が設置後のハンマーに当たっているなら
            if (m_PutState == GimmickPutState.FinishPut &&
                _Hammer.GetComponent<Hammer>().GetPutState() == GimmickPutState.FinishPut)
            {
                PreparingSelfDestruction();//自滅準備 
            }
        }
    }
    /// <summary>
    /// 自滅準備
    /// 画像のアルファを下げて隠す
    /// 死ぬ予定フラグを立てる
    /// </summary>
    /// <returns></returns>
    protected void PreparingSelfDestruction()
    { 
        OnUpperOrHide(false);
        m_IsPrepareDestroy = true;
        m_Sprite.enabled = false;
    }
    /// 設置前
    protected virtual void SelectUpdate() { }
    //設置中。そもそも選ばれなかったら削除
    protected virtual void PutUpdate()
    {
        if (m_PutState == GimmickPutState.Select)
        {
            PreparingSelfDestruction();
        }
    }
    protected virtual void OtherSelectUpdate() {}
    protected virtual void OtherPutUpdate() { }
    protected virtual void PlayUpdate() {  }
    protected virtual void ResultUpdate() { }
    /// <summary>
    /// 自滅フラグを立たせる。
    /// </summary>
    public void SetSelfDestroy()
    {
        m_IsSelfDestroy = true;
    }
    /// <summary>
    /// z軸回転する
    /// </summary>
    /// <param name="_LRotate">反時計回りか</param>
    public void PitchRotate(bool _LRotate)
    {
        if (_LRotate)
        {
            transform.Rotate(new Vector3(0, 0, m_RotateAngle));
        }
        else
        {
            transform.Rotate(new Vector3(0, 0, -m_RotateAngle));
        }
    }
    /// <summary>
    /// 見せたり隠したりする 隠しているときは当たり判定も消える
    /// </summary>
    /// <param name="_upper">出現フラグ</param>
    public virtual void OnUpperOrHide(bool _upper)
    {
        Color color = m_Sprite.color;
        if (_upper && !m_IsPrepareDestroy) 
        {
            color.a = 100;
            m_Sprite.color = color;
            m_Collider.enabled = true;
        }
        else
        {
            color.a = 0;
            m_Sprite.color = color;
            m_Collider.enabled = false;
        }
    }
    /// <summary>
    /// 設置状況の更新
    /// </summary>
    public virtual void OnUpdatePutState()
    {
        switch(m_PutState)
        {
            case GimmickPutState.Select:
                m_PutState = GimmickPutState.Put;
                break;
            case GimmickPutState.Put:
                m_PutState = GimmickPutState.FinishPut;
                break;
        }
    }
    /// <summary>
    /// 設置状況の所得
    /// </summary>
    /// <returns></returns>
    public GimmickPutState GetPutState()
    {
        return m_PutState;
    }    /// <summary>
    /// メインの進捗状況によって更新内容を変える
    /// </summary>
    public void GimmickUpdate(MainState _MainState)
    {
        switch (_MainState)
        {
            case MainState.SelectGimmickPart:
                if (m_PutState == GimmickPutState.Select)
                {
                    //画面に表示されただけの状態
                    SelectUpdate();
                }
                else
                {
                    OtherSelectUpdate();
                }
                break;
            case MainState.PutGimmickPart:
                if (m_PutState == GimmickPutState.Put)
                {
                    //設置後のアプデ
                    OtherPutUpdate();
                }
                ///設置されることがないオブジェクトは破壊準備
                else if (m_PutState == GimmickPutState.Select) 
                {
                    PreparingSelfDestruction();
                }
                else if(m_PutState==GimmickPutState.FinishPut)
                {
                    PutUpdate();
                }
                break;
            case MainState.PlayPart:
                PlayUpdate();
                break;
            case MainState.ResultPart:
                ResultUpdate();
                break;
        }


        MainState = _MainState;
    }
    /// <summary>
    /// ギミック同士が重なり合っているかどうか
    /// </summary>
    /// <returns></returns>
    public bool GetOverLap()
    {
        return m_IsOvarlap;
    }
    /// <summary>
    /// 破壊されるかどうか渡す
    /// </summary>
    /// <returns></returns>
    public bool GetPrepareDestroyFlag()
    {
        return m_IsPrepareDestroy;
    }
}
