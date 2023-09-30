using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EnemyMgr : MonoBehaviour
{
    //�G�֘A
    [Header("Enemy")]
    [Tooltip("��������v���n�u���A�^�b�`")][SerializeField] private List<GameObject> enemys;
    [Tooltip("�f�o�b�O�p")][SerializeField] private short enemyTypeNum;
    [Tooltip("�f�o�b�O�p")][SerializeField] private float timer;

    //�A�N�e�B�u���֘A
    [Header("Activator")]
    [Tooltip("�A�N�e�B�x�[�^���܂Ƃ߂����")] private GameObject activateSpace;
    [Tooltip("�f�o�b�O�p")][SerializeField] private short activatorNum;

    //�I�u�W�F�N�g�v�[���֘A
    [Header("Object Pool")]
    private GameObject objectPool;      //�I�u�W�F�N�g�v�[�����g�p���邽�߂̃I�u�W�F�N�g���A�^�b�`����
    private GameObject poolSpace;     //�I�u�W�F�N�g�v�[�����i�[������
    [Tooltip("�v�[���̃T�C�Y���w��")][SerializeField] private short poolSize;

    // Start is called before the first frame update
    void Start()
    {
        //�G�֘A
        enemyTypeNum = (short)enemys.Count;                         //�G�̎�ނ��v��

        //�A�N�e�B�u���֘A
        activateSpace = this.transform.Find("ActivatePoints").gameObject;  //�W�F�l���[�^�̋�Ԃ�����
        activatorNum = (short)activateSpace.transform.childCount;      //�W�F�l���[�^�����v��

        //�I�u�W�F�N�g�v�[���֘A
        objectPool = GameObject.Find("ObjectPool");         //�I�u�W�F�N�g�v�[����T��
        poolSpace = GameObject.Find("PoolSpace");            //�v�[���I�u�W�F�N�g���i�[�����Ԃ��쐬
        for (int i = 0; i < enemyTypeNum; ++i)                      //�v�[���I�u�W�F�N�g�g�𐶐�
        {
            objectPool.GetComponent<ObjectPool>().InsPool(enemys[i], poolSize, poolSpace);
        }
    }

    //-------------------------------------------------------
    //Public Method For GameMgr
    //-------------------------------------------------------
    /// <summary>
    /// ���萶���̎w�����󂯐�������
    /// </summary>
    /// <param name="_removeObj">����ɂ��ė~�����Ȃ��G������ / null:�ݒ�Ȃ�</param>
    /// <returns>������������(GameObject)</returns>
    public GameObject GenerateTask(GameObject _removeObj)
    {
        //�����ɂ��Ă������Ƃŏ������̐������点��
        GameObject themeObj = _removeObj;
        while (themeObj == _removeObj)
        {
            themeObj = poolSpace.transform.GetChild(Random.Range(0, enemyTypeNum)).gameObject;
        }

        return themeObj;
    }

    /// <summary>
    /// �A�N�e�B�u���̎w�����󂯃����_���ŃA�N�e�B�u������
    /// </summary>
    /// <returns>�A�N�e�B�u�������G(GameObject)</returns>
    public GameObject ActivateEnemyRandom()
    {
        GameObject activateEnemyObj;
        //�ǂ̓G���A�N�e�B�u�����邩�H
        activateEnemyObj = poolSpace.transform.GetChild((short)Random.Range(0, enemyTypeNum)).gameObject;
        //�A�N�e�B�u���E�A�N�e�B�u������ꏊ��ݒ�
        activateSpace.transform.GetChild(Random.Range(0, activatorNum)).GetComponent<ActivatePoint>().Activate(activateEnemyObj);
       
        //�A�N�e�B�u�������G�I�u�W�F�N�g��Ԃ�
        return activateEnemyObj;
    }

    public GameObject GetPoolSpace()
    {
        return poolSpace;
    }
}