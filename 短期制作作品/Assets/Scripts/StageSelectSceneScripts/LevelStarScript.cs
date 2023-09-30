using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class LevelStarScript : MonoBehaviour
{
    float rad;
    

    void Start()
    {
        rad = 0.0f;
    }

    // Update is called once per frame
    void Update()
    {
        transform.rotation = Quaternion.Euler(0.0f, 0.0f, 180.0f * rad);
        rad += Time.deltaTime * 0.5f;
    }
}
