using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ClickToReturn : MonoBehaviour
{
    private Color color;
    private float rad = 0.0f;
    private ResultTarget target;
    // Start is called before the first frame update
    void Start()
    {
        color = this.GetComponent<SpriteRenderer>().color;
        GameObject obj = GameObject.Find("ResultTarget");
        target = obj.GetComponent<ResultTarget>();
    }

    // Update is called once per frame
    void Update()
    {
        if (target.GetPos.y >= 0.0f)
        {
            rad += Time.deltaTime;
            color.a = (Mathf.Sin(rad * Mathf.PI) + 1.0f) / 2.0f;
        }
        else
        {
            color.a = 0.0f;
        }
        this.GetComponent<SpriteRenderer>().color = color;
    }
}
