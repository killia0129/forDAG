using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class GameMgr : MonoBehaviour
{
    [Header("�A�^�b�`�E�l�̐ݒ肪�K�v�ȍ���")]
    [Header("�Q�[���̐ݒ�")]
    [Tooltip("�c��̐�")][SerializeField] private int lifeNum;

    [Header("���Ԃ̐ݒ�")]
    [Tooltip("����\������")] [SerializeField] private float showTaskTime;

    [Header("UI�֘A")]
    [Tooltip("����̃L�����o�X")]       [SerializeField]   private GameObject obj_taskCanvas;
    [Tooltip("���܂��̃L�����o�X")]     [SerializeField]   private GameObject obj_kamaeCanvas;
    [Tooltip("�r���X�R�A�̃L�����o�X")] [SerializeField]   private GameObject obj_subResult;
    [Tooltip("���s�̃L�����o�X")]       [SerializeField]   private GameObject obj_failedCanvas;

    [Header("�Q�[���̐ݒ�")]
    [Tooltip("�ۑ�̒B����(�ǐ�)")][SerializeField] private int clearCount;
    [SerializeField] public GameObject staticScore;

    [Header("�v���C���[�̏��")]
    [Tooltip("C#���蓖�Ċm�F�p(�ǐ�)")][SerializeField]private Player player;
    [Tooltip("true:���܂���� / false:�������(�ǐ�)")][SerializeField] private bool spaceKeyState;
    [Space(10)]

    [Header("�G�̏��")]
    [Tooltip("C#���蓖�Ċm�F�p(�ǐ�)")][SerializeField] private EnemyMgr enemyMgr;
    [Tooltip("����̓G(�ǐ�)")][SerializeField] private GameObject obj_task;
    [Tooltip("���݂̓G(�ǐ�)")][SerializeField] private GameObject obj_activeEnemy;
    [Tooltip("�A�N�e�B�u���ҋ@���Ԃ͈̔�(x:�ŏ����� / y:�ő厞��)")][SerializeField] private Vector2 activateWaitTimeRange;
    [Tooltip("�ݒ肵���͈͂��烉���_���Ɏ��ꂽ�ҋ@���� / -1�Őݒ�Ȃ�(�ǐ�)")][SerializeField]private float waitTime;
    [Tooltip("�G��|���̂ɂ�����������")][SerializeField] private float clearTime;
    [Tooltip("�G��|���̂ɂ����������Ԃ̑���")][SerializeField] private float clearTimeTotal;
    [Space(10)]

    [Header("UI�̏��")]
    private bool showTaskFlag;  //true:�^�X�N�\����/false:�^�X�N��\����

    [Header("SE�֘A")]
    [Tooltip("�Q�[���J�n���ɂȂ炷���ʉ�")][SerializeField] AudioClip se_printTask;
    [Tooltip("�Q�[���J�n���ɂȂ炷���ʉ�")] [SerializeField] AudioClip se_split;
    [Tooltip("�Q�[���J�n���ɂȂ炷���ʉ�")] [SerializeField] AudioClip se_failed;
    
    AudioSource audioSource;

    [Header("���L���Ďg�p")]
    [SerializeField] private float timer;

    enum GameMode
    {
       TUTORIAL,           //�ŏ��̈�񂾂����s�����
       GENERATE_TASK,      //����𐶐�����
       ACTIVATE_ENEMY,     //�G���A�N�e�B�u������
       GAME_MAIN,          //
       GAME_FAILED,        //���s
       GAME_SUCCESS,       //����
       INIT,               //������(2��ڈȍ~�̃v���C�ɕK�v)
    }
    [Header("�Q�[���i�s���")]
    [Tooltip("���݂̃��[�h")][SerializeField]private GameMode mode;


    void Start()
    {
        //-------------------------------------------------------
        //Player
        //-------------------------------------------------------
        //�v���C���[�̃X�N���v�g���m��
        player = GameObject.Find("Player").GetComponent<Player>();

        //-------------------------------------------------------
        //Enemy
        //-------------------------------------------------------
        //�G�̃X�N���v�g���m��
        enemyMgr = GameObject.Find("EnemyMgr").GetComponent<EnemyMgr>();
        waitTime = -1;

        //-------------------------------------------------------
        //SE
        //-------------------------------------------------------
        audioSource = GetComponent<AudioSource>();
    }

    // Update is called once per frame
    void Update()
    {
        if(mode == GameMode.TUTORIAL)
        {
            if(timer ==0)
            {
                timer += Time.deltaTime;
            }
            else if(timer <= 3)
            {
                timer += Time.deltaTime;
            }
            else
            {
                timer = 0;
                mode = GameMode.GENERATE_TASK;
            }

        }
        if (mode == GameMode.GENERATE_TASK)
        {
            if (timer == 0)
            {
                //�v���C���[���A�C�h����Ԃ�
                player.SetStateIdol();
                //�����_�����萶���̒����珜�������G�������ɁA����𐶐�
                obj_task = enemyMgr.GenerateTask(obj_task);
                timer += Time.deltaTime;
                //�����\��
                obj_taskCanvas.gameObject.SetActive(true);
                audioSource.clip = se_printTask;
                audioSource.Play();
                obj_taskCanvas.GetComponent<TaskCanvas>().printTask(obj_task);
                //���Ԃ̌v���J�n(����ł���if�����ɓ���Ȃ��Ȃ�)
            }
            else if (timer <= showTaskTime)
            {
                //���Ԃ̌v���𑱂���
                timer += Time.deltaTime;
            }
            else
            {
                //�g���I������̂Ń��Z�b�g
                timer = 0;
                //����̕\�����I��肩�܂��̑���w����\��
                obj_taskCanvas.gameObject.SetActive(false);
                //���܂��\��
                obj_kamaeCanvas.SetActive(true);
                //Activate�Ɉڍs
                mode = GameMode.ACTIVATE_ENEMY;
            }
        }

        if(mode == GameMode.ACTIVATE_ENEMY && spaceKeyState)
        {
            if (timer == 0)
            {
                //���܂��̑���w�����\��
                obj_kamaeCanvas.SetActive(false);
                //�v���C���[���\����Ԃ�
                player.SetStateKamae();
                //�ҋ@���Ԃ�ݒ肳�ꂽ�͈͓��ō쐬
                waitTime = GenerateTimeRangeRandom(activateWaitTimeRange);
                //���Ԃ̌v���J�n
                timer += Time.deltaTime;
            }
            else if (timer <= waitTime)
            {
                timer += Time.deltaTime;
            }
            else
            {
                //�g���I������̂Ń^�C�}�[�����Z�b�g
                timer = 0;
                //�G�������_���ɃA�N�e�B�u��
                obj_activeEnemy = enemyMgr.ActivateEnemyRandom();
                //GAME_MAIN�Ɉڍs
                mode = GameMode.GAME_MAIN;
            }
        }

        if (mode == GameMode.GAME_MAIN)
        {
            if (obj_activeEnemy == obj_task)
            {
                //�|���̂ɂ����������Ԃ̋L�^�J�n
                clearTime += Time.deltaTime;
                if (spaceKeyState)
                {
                    if (!obj_activeEnemy.activeSelf)
                    {
                        //Failed�Ɉڍs
                        mode = GameMode.GAME_FAILED;
                    }
                }
                else
                {
                    //�v���C���[��������Ԃ�
                    player.SetStateIai();
                    //�G�̈ʒu���Œ�
                    obj_activeEnemy.GetComponent<Rigidbody2D>().velocity = Vector2.zero;
                    //Success�Ɉڍs
                    mode = GameMode.GAME_SUCCESS;
                }
            }
            else
            {
                if (spaceKeyState)
                {
                    if (!obj_activeEnemy.activeSelf)
                    {
                        //Activate�Ɉڍs
                        mode = GameMode.ACTIVATE_ENEMY;
                    }
                }
                else
                {
                    //�v���C���[�������~�X��Ԃ�
                    player.SetStateIaiSuka();
                    //�G�̈ʒu���Œ�
                    obj_activeEnemy.GetComponent<Rigidbody2D>().velocity = Vector2.zero;
                    //Failed�Ɉڍs
                    mode = GameMode.GAME_FAILED;
                }
            }
        }

        if (mode == GameMode.GAME_FAILED)
        {
            //���o�̉��u��
            if (timer <= 5)
            {
                if(timer == 0)
                {
                    obj_failedCanvas.SetActive(true);
                }
                audioSource.clip = se_failed;
                audioSource.Play();
                obj_activeEnemy.GetComponent<Enemy>().Failed();
                timer += Time.deltaTime;
            }
            else
            {
                timer = 0;
                //�c������
                if (lifeNum > 0)
                {
                    obj_failedCanvas.SetActive(false);
                    //1���炵
                    --lifeNum;
                    //Init�Ɉڍs
                    mode = GameMode.INIT;
                }
                else
                {
                    staticScore.GetComponent<StaticScore>().ScoreCheck(clearCount, clearTimeTotal);
                    //Result�ɑJ��
                    SceneManager.LoadScene("Result");
                }
            }
        }
        else if (mode == GameMode.GAME_SUCCESS)
        {
            //���o���u��
            if (timer <= 5)
            {
                if(timer == 0)
                {
                    audioSource.clip = se_split;
                    audioSource.Play();
                    //�G�𕪗􂳂���
                    obj_activeEnemy.GetComponent<Enemy>().Split();
                    //�|���̂ɂ����������Ԃ̑������L�^
                    clearTimeTotal += clearTime;
                    //�N���A�񐔂��J�E���g
                    ++clearCount;
                    //�r���̃��U���g��\��
                    obj_subResult.gameObject.SetActive(true);
                    obj_subResult.GetComponent<SubResult>().PrintSubScore(clearCount, clearTime);
                }
                timer += Time.deltaTime;

                //�v���C���[�������ʒu�ŃA�C�h���ɂȂ��āA�G�������
            }
            else
            {
                timer = 0;
                //�X�R�A�̕\�����\��
                obj_subResult.gameObject.SetActive(false);
                //Init�Ɉڍs
                mode = GameMode.INIT;
            }
        }

        if (mode == GameMode.INIT)
        {
            //���o���u�����̊ԕK�v
            obj_activeEnemy.SetActive(false);

            //�|���̂ɂ����������Ԃ�������
            clearTime = 0;
            //Generate�Ɉڍs
            mode = GameMode.GENERATE_TASK;
        }
    }

    //-------------------------------------------------------
    //Private Method
    //-------------------------------------------------------

    /// <summary>
    /// �ݒ肳�ꂽ�͈͂Ń����_���Ɏ��Ԃ��쐬����
    /// </summary>
    /// <param name="_timeRange">�����_���Ȏ��Ԃ͈̔�</param>
    /// <returns>�쐬���ꂽ����</returns>
    private float GenerateTimeRangeRandom(Vector2 _timeRange)
    {
        return Random.Range(_timeRange.x, _timeRange.y);
    }

    //-------------------------------------------------------
    //Public Method For Player
    //-------------------------------------------------------
    /// <summary>
    /// �v���C���[���X�y�[�X���������̂�`���邽�߂Ɏg�p
    /// </summary>
    public void pressSpace() { spaceKeyState = true; }
    /// <summary>
    /// �v���C���[���X�y�[�X�𗣂����̂�`���邽�߂Ɏg�p
    /// </summary>
    public void ReleaseSpace() { spaceKeyState = false; }
}
