using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Particle : MonoBehaviour
{
    private ParticleSystem particle;
    private Color color;
    private ScoreText score;
    ParticleSystem.MainModule main;

    private bool playFlag = false;
    // Start is called before the first frame update
    void Start()
    {
        particle = this.GetComponent<ParticleSystem>();
        main = particle.main;
        color = main.startColor.color;

        
        GameObject objM = GameObject.Find("Score");
        score = objM.GetComponent<ScoreText>();
    }

    // Update is called once per frame
    void Update()
    {
        if (playFlag==true)
        {
            if (score.GetScore >= 70)
            {
                color.a = 1.0f;
            }
            else
            {
                color.a = 0.0f;
            }
        }
        else
        {
            color.a = 0.0f;
        }

        main.startColor = new ParticleSystem.MinMaxGradient(color);
    }

    public void SetEndFlag()
    {
        playFlag = !playFlag;
    }
}
