using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ClickToStartTitleScript : MonoBehaviour
{
    private Color color;
    private float rad = 0.0f;
    // Start is called before the first frame update
    void Start()
    {
        color = this.GetComponent<SpriteRenderer>().color;
    }

    // Update is called once per frame
    void Update()
    {
        rad += Time.deltaTime;
        color.a = (Mathf.Cos(rad * Mathf.PI) + 1.0f) / 2.0f;
        this.GetComponent<SpriteRenderer>().color = color;
    }
}
