using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Player : MonoBehaviour
{
    GameMgr gameMgr;
    [Header("Player")]
    [Tooltip("�����̃I�u�W�F�N�g")] [SerializeField] private GameObject idol;
    [Tooltip("���܂��̃I�u�W�F�N�g")] [SerializeField] private GameObject kamae;
    [Tooltip("�����̃I�u�W�F�N�g")] [SerializeField] private GameObject iai;
    [Tooltip("�O��̃X�y�[�X�L�[�̏��")][SerializeField] private bool prevSpaceKeyState;

    [Tooltip("���݂̏��")][SerializeField] GameObject nowState;
    [Tooltip("�O��̏��")][SerializeField] GameObject prevState;

    [Tooltip("�����ʒu")][SerializeField] Vector3 firstPos;
    [Tooltip("�ړ���̈ʒu")][SerializeField] Vector3 endPos;

    [Header("�����֌W")]
    [SerializeField]private AudioSource audioSource;
    [Tooltip("���܂��̌��ʉ�")][SerializeField] private AudioClip se_kamae;
    [Tooltip("�������s�̌��ʉ�")][SerializeField] private AudioClip se_suka;
    [Tooltip("���������̌��ʉ�")][SerializeField] private AudioClip se_hit;

    // Start is called before the first frame update
    void Start()
    {
        gameMgr = GameObject.Find("GameMgr").GetComponent<GameMgr>();
        nowState = idol;
        prevState = idol;
        //�v���C���[��idol��Ԃŕ\��
        if (!nowState.activeSelf)
        {
            nowState.SetActive(true);
        }
        prevSpaceKeyState = false;
        //���݈ʒu�������ʒu�Ƃ��ċL�^����
        firstPos = this.transform.position;
        //�ړ���̈ʒu���L�^����
        {
            GameObject endPosObj;
            endPosObj = GameObject.Find("EndPos").gameObject;
            endPos = endPosObj.transform.position;
            endPosObj.SetActive(false);
        }
        audioSource = GetComponent<AudioSource>();
    }

    // Update is called once per frame
    void Update()
    {
        UpdateSpaceKeyState();
    }

    /// <summary>
    /// SpaceKey�̏�Ԃ�O��Ō��݂Ŕ�r���A�Ⴆ�΁AGameMgr�ɓ`����
    /// </summary>
    private void UpdateSpaceKeyState()
    {
        if(Input.GetKey(KeyCode.Space) != prevSpaceKeyState)
        {
            //��Ԃ𔽓]����
            prevSpaceKeyState = !prevSpaceKeyState;
            if(prevSpaceKeyState)
            {
                gameMgr.pressSpace();
            }
            else
            {
                gameMgr.ReleaseSpace();
            }
        }
    }

    /// <summary>
    /// �O��ƌ��݂̏�Ԃ��r���A�Ⴆ�ΕύX����
    /// </summary>
    private bool UpdateState()
    {
        //���݂̏�ԂƑO��̏�Ԃ��������
        if(nowState != prevState)
        {
            //���݂̏�Ԃ�\���ɓK����
            nowState.SetActive(true);
            //�O��̏�Ԃ��\���A
            prevState.SetActive(false);
            //�O��̏�Ԃɍ��̏�Ԃ��L�^����
            prevState = nowState;
            return true;
        }
        return false;
    }

    public void SetStateIdol()
    {
        this.transform.position = firstPos;
        nowState = idol;
        UpdateState();
    }
    //�N���A��̗���
    public void SetStateIdolClear()
    {
        this.transform.position = endPos;
        nowState = idol;
        UpdateState();
    }
    public void SetStateKamae()
    {
        this.transform.position = firstPos;
        nowState = kamae;
        if (UpdateState())
        {
            audioSource.clip = se_kamae;
            audioSource.Play();
        }
    }
    //��������
    public void SetStateIai()
    {
        this.transform.position = endPos;
        nowState = iai;
        UpdateState();
        audioSource.clip = se_hit;
        audioSource.Play();
    }
    //�������s
    public void SetStateIaiSuka()
    {
        this.transform.position = endPos;
        nowState = iai;
        UpdateState();
        audioSource.clip = se_suka;
        audioSource.Play();
    }
}
