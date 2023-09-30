using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PauseFadeTitleScript : MonoBehaviour
{
    private Color color;
    [SerializeField] private float maxAlfa;

    private bool pauseFlag = false;
    void Start()
    {
        color = this.GetComponent<SpriteRenderer>().color;
    }

    // Update is called once per frame
    void Update()
    {
        if (pauseFlag==true)
        {
            color = new Color(color.r, color.g, color.b, maxAlfa);
        }
        else
        {
            color = new Color(color.r, color.g, color.b, 0.0f);
        }

        this.GetComponent<SpriteRenderer>().color = color;
    }

    public void SetPauseFase()
    {
        pauseFlag = !pauseFlag;
    }
}
