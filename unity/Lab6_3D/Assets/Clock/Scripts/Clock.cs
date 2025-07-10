using UnityEngine;
using System.Collections;
using UnityEngine.UI;

public class Clock : MonoBehaviour {
	[SerializeField] private float seconds = 0;
    public Slider speedSlider; 
    public Toggle realTime;
	
    public Transform directionalLight;
	public GameObject pointerSeconds;
    public GameObject pointerMinutes;
    public GameObject pointerHours;

    void Start() 
    {
        seconds = System.DateTime.Now.Second + System.DateTime.Now.Hour*60*60 + System.DateTime.Now.Minute*60;
        UpdateSkybox();
    }

    void Update() 
    {
        float delta;
        if (realTime.isOn)
	    {
            delta = Time.deltaTime;
	    	seconds += delta;
            float query = System.DateTime.Now.Second + System.DateTime.Now.Hour*60*60 + System.DateTime.Now.Minute*60;
            if ((seconds >= 86400.0f) || (Mathf.Abs(query - seconds) > 1))
            {
                seconds = System.DateTime.Now.Second + System.DateTime.Now.Hour*60*60 + System.DateTime.Now.Minute*60;
                UpdateSkybox();
            }
	    }
        else
        {
            delta = Time.deltaTime * speedSlider.value;
            seconds += delta;
            if (seconds >= 86400.0f)
            {
                seconds = seconds - 86400.0f;
                UpdateSkybox();
            }
        }
        directionalLight.Rotate(new Vector3(delta * 360.0f / 86400.0f, 0.0f, 0.0f));

        float second = seconds % 60.0f;
        float minute = (seconds / 60.0f) % 60.0f;
        float hour = seconds / (60.0f * 60.0f);

        //Debug.Log($"{hour}\t{minute}\t{second}");

        //float hour24 = seconds / (60.0f * 60.0f);
        //this.currentExposure = Mathf.Lerp(this.exposureStart, this.exposureEnd, Mathf.Clamp01(relativeHour / 12.0f));
        //RenderSettings.skybox.SetFloat("_Exposure", currentExposure);

        //-- calculate pointer angles
        float rotationSeconds = (360.0f / 60.0f) * second;
        float rotationMinutes = (360.0f / 60.0f) * minute;
        float rotationHours = (360.0f / 12.0f) * hour;

        //-- draw pointers
        pointerSeconds.transform.localEulerAngles = new Vector3(0.0f, 0.0f, rotationSeconds);
        pointerMinutes.transform.localEulerAngles = new Vector3(0.0f, 0.0f, rotationMinutes);
        pointerHours.transform.localEulerAngles = new Vector3(0.0f, 0.0f, rotationHours);

        //float rot = -90.0f + (360.0f * (seconds / 86400.0f));
        //directionalLight.localEulerAngles = new Vector3(rot,
        //                                                directionalLight.localEulerAngles.y,
        //                                                directionalLight.localEulerAngles.z);
        //Debug.Log($"{rot}");
    }

    public void UpdateSkybox()
    {
        float rot = -90.0f + (360.0f * (seconds / 86400.0f));
        directionalLight.localEulerAngles = new Vector3(rot,
                                                        directionalLight.localEulerAngles.y,
                                                        directionalLight.localEulerAngles.z);
    }
}
