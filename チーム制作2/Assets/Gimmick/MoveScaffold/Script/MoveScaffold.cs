using System.Collections;
using System.Collections.Generic;
using UnityEngine;

/// <summary>
/// 移動床
/// </summary>
public class MoveScaffold : MonoBehaviour
{
    [SerializeField] [Header("終着点で止まってから何秒経って動くか")] private float m_StopTime;
    [SerializeField] [Header("移動時間")] private float m_MoveTime;
    [SerializeField] [Header("移動係数")] private float m_MoveCoefficient;
    [SerializeField] private MoveScaffoldState m_MoveScaffoldState = MoveScaffoldState.PlayerWait;
    private float m_RemainingMoveTime = 0;
    private bool m_IsStartCorutine = false;
    private IEnumerator m_StopCoroutine;
    /// <summary>
    /// 停止状態になってからStopTimeまで待って戻るコルーチン
    /// </summary>
    IEnumerator Stop()
    {
        m_IsStartCorutine = true;
        m_MoveScaffoldState = MoveScaffoldState.Stop;
        yield return new WaitForSeconds(m_StopTime);
        m_MoveScaffoldState = MoveScaffoldState.Return;
        m_IsStartCorutine = false;
        m_RemainingMoveTime = 0;
        yield break;
    }
    /// <summary>
    /// 移動するよ　移動時間過ぎたら止まるよ
    /// </summary>
    private void Move(Vector3 moveVec)
    {
        if (m_MoveScaffoldState == MoveScaffoldState.Move ||
            m_MoveScaffoldState == MoveScaffoldState.Return)
        {
            transform.position += moveVec * m_MoveCoefficient * Time.deltaTime;
            m_RemainingMoveTime -= Time.deltaTime;

            //時間経過したら
            if (m_RemainingMoveTime < 0)
            {
                switch (m_MoveScaffoldState)
                {
                    case MoveScaffoldState.Move:
                        m_MoveScaffoldState = MoveScaffoldState.Stop;
                        break;

                    case MoveScaffoldState.Return:
                        m_MoveScaffoldState = MoveScaffoldState.PlayerWait;
                        break;
                }
            }
        }
    }
    private void OnCollisionEnter2D(Collision2D collision)
    {
        if (collision.gameObject.tag == "player")
        {
            if (m_MoveScaffoldState == MoveScaffoldState.PlayerWait)
            {
                m_MoveScaffoldState = MoveScaffoldState.Move;
            }
        }
    }

    /// <summary>
    /// ラウンドが終わったら戻してね
    /// </summary>
    /// <param name="_startPos"></param>
    public void Played(Vector3 _startPos)
    {
        transform.position = _startPos;
        m_MoveScaffoldState = MoveScaffoldState.PlayerWait;
        m_StopCoroutine = null;
        m_RemainingMoveTime = m_MoveTime;
    }
    public void Standby()
    {
        m_StopCoroutine = Stop();
    }
    /// <summary>
    /// 足場の状態によってやることが変わる
    /// </summary>
    public void Run(Vector2 destination,Vector2 startPos)
    {
        Vector2 moveVec;
        switch (m_MoveScaffoldState)
        {
            case MoveScaffoldState.PlayerWait:
                m_RemainingMoveTime = m_MoveTime;
                m_StopCoroutine = null;
                break;
            case MoveScaffoldState.Move:
                moveVec = destination - startPos;
                Move(moveVec.normalized);
                break;

            case MoveScaffoldState.Stop:
                //コルーチンが連続して起動しないように
                if (!m_IsStartCorutine)
                {
                    m_StopCoroutine = Stop();
                    StartCoroutine(m_StopCoroutine);
                    m_RemainingMoveTime = m_MoveTime;
                }
                break;
            case MoveScaffoldState.Return:
                moveVec = startPos - destination;
                Move(moveVec.normalized);
                break;
        }
    }


}
