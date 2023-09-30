using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ObjectPool : MonoBehaviour
{
    /// <summary>
    /// �I�u�W�F�N�g�v�[�����쐬����֐�
    /// </summary>
    /// <param name="_poolingObj">�v�[�����O����I�u�W�F�N�g</param>
    /// <param name="_size">�v�[���̃T�C�Y</param>
    /// <param name="_insSpace">��������ꏊ</param>
    public void InsPool(GameObject _poolingObj, int _size, GameObject _insSpace)
    {
        //�v�[���̃T�C�Y���Ώۂ̃I�u�W�F�N�g���w��ꏊ�ɐ�������
        for (int i = 0; i < _size; i++)
        {
            Instantiate(_poolingObj, this.transform.position, _poolingObj.transform.rotation, _insSpace.transform);
        }
        //�A�N�e�B�u�ȃI�u�W�F�N�g��T�����Ė���������
        //foreach...�v�f�̐��������[�v���s����
        foreach (Transform t in _insSpace.transform)
        {
            if (t.gameObject.activeSelf)
            {
                t.gameObject.SetActive(false);
            }
        }
    }

    GameObject insdObj;
    /// <summary>
    /// �v�[��������I�u�W�F�N�g���A�N�e�B�u�ɂ���
    /// </summary>
    /// <param name="_poolingSpace">�v�[�����Ă���ꏊ</param>
    /// <param name="_setPos">�A�N�e�B�u�ɂ���Ƃ��̈ʒu</param>
    public GameObject SetActive(GameObject _poolingSpace, Vector3 _setPos)
    {    
        //��A�N�e�B�u�I�u�W�F�N�g���v�[���̒�����T��
        foreach (Transform t in _poolingSpace.transform)
        {
            if (!t.gameObject.activeSelf)
            {
                //�I�u�W�F�N�g�Ɉʒu�Ɖ�]���Z�b�g
                t.SetPositionAndRotation(_setPos, t.transform.rotation);
                //�A�N�e�B�u��
                t.gameObject.SetActive(true);
                //return ��1�񂵂���������Ȃ��悤�ɂȂ�
                return t.gameObject;
            }
        }
        foreach(Transform t in _poolingSpace.transform)
        {
            //��A�N�e�B�u�I�u�W�F�N�g���Ȃ�������V�K�ɐ���
            insdObj = Instantiate(t.gameObject, _setPos, t.transform.rotation, _poolingSpace.transform);
        }
        return insdObj;
    }
    /// <summary>
    /// �v�[�����܂��͎w��I�u�W�F�N�g���A�N�e�B�u�ɂ���֐�
    /// </summary>
    /// <param name="_poolingSpace">�v�[�����Ă���ꏊ�F�w�肵�Ĕ�A�N�e�B�u���̏ꍇ�́@null</param>
    /// <param name="_setObj">�w�肵�Ĕ�A�N�e�B�u���F�v�[�����ǂ�ł��悯��� null</param>
    /// <detail> �����͂ǂ��炩��null�ǂ��炩���w�肵�Ďg���K�v������ </detail>
    public void SetDeactive(GameObject _poolingSpace, GameObject _setObj)
    {
        //���s�����Ȃ��ŏI��������ꍇ
        if(_poolingSpace && _setObj || !_poolingSpace && !_setObj)
        {
            Debug.Log("��A�N�e�B�u���Ɏ��s���܂����B�����������Ƃ�null���Z�b�g����Ă��܂��B�Е��݂̂ɂ��Ă�������");
            Application.Quit();
        }
        //�w�肳��Ă�����w�肳��Ă���I�u�W�F�N�g���A�N�e�B�u��
        if(_setObj)
        {
            _setObj.SetActive(false);
            return;
        }
        //�A�N�e�B�u�ȃI�u�W�F�N�g���v�[���̒�����T��
        foreach (Transform t in _poolingSpace.transform)
        {
            if (t.gameObject.activeSelf)
            {
                //��A�N�e�B�u��
                t.gameObject.SetActive(false);
                //��A�N�e�B�u�ɂ�����I��
                return;
            }
        }
    }

    /// <summary>
    /// �v�[�����̃I�u�W�F�N�g�̐��𐔂��ĕԂ��֐�
    /// </summary>
    /// <param name="_poolingSpace"></param>
    /// <returns></returns>
    public int CountPoolingObj(GameObject _poolingSpace)
    {
        int count = 0;
        //�v�[��������A�N�e�B�u�ȃI�u�W�F�N�g��T������
        foreach(Transform t in _poolingSpace.transform)
        {
            if(t.gameObject.activeSelf)
            {
                count++;
            }
        }
        return count;
    }

    /// <summary>
    /// �q�ɃA�N�e�B�u�I�u�W�F�N�g�����邩���ׂ�
    /// </summary>
    /// <param name="_parent">�e�̃g�����X�t�H�[��</param>
    /// <returns>�A�N�e�B�u�I�u�W�F�N�g��Ԃ�</returns>
    public GameObject FindActiveObjctInChild(Transform _parent)
    {
        foreach (Transform t in _parent)
        {
            if (t.gameObject.activeSelf)
            {
                return t.gameObject;
            }
        }
        return null;
    }
}
