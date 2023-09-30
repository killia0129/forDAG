using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEditor;
using UnityEngine.UI;

public class Enemy : MonoBehaviour
{
    [Header("�摜")]
    [Tooltip("�؂ꂽ�Ƃ��@")] [SerializeField] private GameObject obj_split1;
    [Tooltip("�؂ꂽ�Ƃ��A")] [SerializeField] private GameObject obj_split2;
    [Tooltip("�؂ꂽ�摜������p�X")] [SerializeField] private string path1;
    [Tooltip("�؂ꂽ�摜������p�X")] [SerializeField] private string path2;
    //[Tooltip("�؂ꂽ�Ƃ��̔w�i")] [SerializeField] private GameObject obj_back;
    private GameObject spriteSpace;

    private Rigidbody2D rb_split1;
    private Rigidbody2D rb_split2;

    private void Awake()
    {
        spriteSpace = GameObject.Find("SpliteSpace");

        path1 = "Assets/Prefab/" + this.GetComponent<SpriteRenderer>().sprite.name + "split1.prefab";
        obj_split1 = AssetDatabase.LoadAssetAtPath<GameObject>(path1);
        obj_split1 = Instantiate(obj_split1);
        obj_split1.transform.parent = spriteSpace.transform;
        obj_split1.SetActive(false);
        rb_split1 = obj_split1.GetComponent<Rigidbody2D>();

        path2 = "Assets/Prefab/" + this.GetComponent<SpriteRenderer>().sprite.name + "split2.prefab";
        obj_split2 = AssetDatabase.LoadAssetAtPath<GameObject>(path2);
        obj_split2 = Instantiate(obj_split2);
        obj_split2.transform.parent = spriteSpace.transform;
        obj_split2.SetActive(false);
        rb_split2 = obj_split2.GetComponent<Rigidbody2D>();

    }
    private void Start()
    {
        //�؂�ꂽ�Ƃ��ɔ�ԃI�u�W�F�N�g���擾

        //�؂ꂽ�Ƃ��ɔ�ԃI�u�W�F�N�g���畨�����擾
    }

    /// <summary>
    /// ��ʊO�ɏo�����A�N�e�B�u��
    /// </summary>
    /// <param name="other"></param>
    private void OnTriggerExit2D(Collider2D other)
    {
        if(other.tag=="Map")
        {
            this.gameObject.SetActive(false);
        }
    }

    public void Split()
    {
        //�̗͂ʂ��쐬
        Vector2 vec2 = new Vector2(-600, 600);
        //��������ʒu��ݒ�
        obj_split1.transform.position = this.transform.position;
        obj_split2.transform.position = this.transform.position;
        //�A�N�e�B�u��
        obj_split1.SetActive(true);
        obj_split2.SetActive(true);
        //�͂����Z�b�g���Ă���
        rb_split1.velocity = Vector2.zero;
        rb_split2.velocity = Vector2.zero;
        //�������A�N�e�B�u�ɂ���
        this.gameObject.SetActive(false);
        //�͂�������
        rb_split1.AddForce(vec2);
        rb_split2.AddForce(-vec2);
    }
    public void Failed()
    {
        this.gameObject.GetComponent<SpriteRenderer>().color = HalfAlpha(this.gameObject.GetComponent<SpriteRenderer>().color);
    }

    private Color HalfAlpha(Color _color)
    {
        _color.a = _color.a / 2;
        return _color;
    }
}
