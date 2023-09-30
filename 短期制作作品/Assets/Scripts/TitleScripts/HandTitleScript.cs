using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class HandTitleScript : MonoBehaviour
{

    private bool moveLeftFlag = true;
    private bool moveUpFlag = true;
    public Vector2 pos;
    [SerializeField] private float horizontalSpeed = 0.1f;
    [SerializeField] private float verticalSpeed = 0.1f;
    [SerializeField] private int horizontalRandomRange = 21;
    [SerializeField] private int verticalRandomRange = 21;
    //private float handToMarkarDis = 3.3f;
    // Start is called before the first frame update
    void Start()
    {
        pos = transform.position;
    }

    // Update is called once per frame
    void Update()
    {
        if (moveLeftFlag == true)
        {
            pos.x -= horizontalSpeed;
        }
        else
        {
            pos.x += horizontalSpeed;
        }

        if (moveUpFlag == true)
        {
            pos.y += verticalSpeed;
        }
        else
        {
            pos.y -= verticalSpeed;
        }

        int rndH = Random.Range(1, horizontalRandomRange);
        int rndV = Random.Range(1, verticalRandomRange);

        if (rndH == 1)
        {
            if (moveLeftFlag == true)
            {
                moveLeftFlag = false;
            }
            else
            {
                moveLeftFlag = true;
            }
        }

        if (rndV == 1)
        {
            if (moveUpFlag == true)
            {
                moveUpFlag = false;
            }
            else
            {
                moveUpFlag = true;
            }
        }

        if (pos.x < -1.7f)
        {
            moveLeftFlag = false;
        }
        if (pos.x > 3.0f)
        {
            moveLeftFlag = true;
        }

        if (pos.y > 3.0f)
        {
            moveUpFlag = false;
        }
        if (pos.y < 0.7f)
        {
            moveUpFlag = true;
        }


        transform.position = pos;
    }

    public Vector2 GetPos
    {
        get { return pos; }
    }
}
