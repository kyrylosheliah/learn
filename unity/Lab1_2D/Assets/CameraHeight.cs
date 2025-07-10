using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraHeight : MonoBehaviour
{
    public GameObject cam;
    private float initialHeight;
    // Start is called before the first frame update
    void Start()
    {
        initialHeight = cam.transform.position.y;
    }

    // Update is called once per frame
    void Update()
    {
        cam.transform.position = new Vector2(cam.transform.position.x, initialHeight);
    }
}
