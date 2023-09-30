using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class StarTitleScript : MonoBehaviour
{

    private Vector2 pos;
    private HandTitleScript hand;

    // Start is called before the first frame update
    void Start()
    {
        GameObject obj = GameObject.Find("hand");
        hand = obj.GetComponent<HandTitleScript>();
        pos = hand.GetPos;
        pos.x -= 0.6f;
        pos.y -= 0.7f;
    }

    // Update is called once per frame
    void Update()
    {
        pos = hand.GetPos;
        pos.x -= 0.6f;
        pos.y -= 0.7f;
        transform.position = pos;

    }
}
