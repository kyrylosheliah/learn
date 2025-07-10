using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class ToggleBehaviour : MonoBehaviour
{
    public Clock clock;

    void Start()
    {
        this.GetComponent<Toggle>().onValueChanged.AddListener(delegate {
            ToggleValueChanged(this.GetComponent<Toggle>());
        });
    }

    void ToggleValueChanged(Toggle change)
    {
        clock.UpdateSkybox();
    }
}
