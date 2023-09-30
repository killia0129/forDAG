using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Thorn : GimmickBase
{
    [SerializeField]private BoxCollider2D m_ThornCollider;
     private void OnCollisionEnter2D(Collision2D collision)
    {
        m_IsOvarlap = true;
    }
    private void OnCollisionExit2D(Collision2D collision)
    {
        m_IsOvarlap = false;
    }
    private void OnTriggerStay2D(Collider2D collision)
    {
        TriggerEvenet(collision.gameObject);
    }
    public override void OnUpperOrHide(bool _upper)
    {
        Color color = m_Sprite.color;
        if (_upper)
        {
            color.a = 255;
            m_Sprite.color = color;
            m_Collider.enabled = true;
            m_ThornCollider.enabled = true;
        }
        else
        {
            color.a = 0;
            m_Sprite.color = color;
            m_Collider.enabled = false;
            m_ThornCollider.enabled = false;
        }
    }
}
