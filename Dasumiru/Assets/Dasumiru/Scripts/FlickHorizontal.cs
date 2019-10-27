using System;
using TouchScript.Gestures;
using UnityEngine;

public class FlickHorizontal : MonoBehaviour
{
    public FlickGesture flickGesture;
    public GameObject moveObj;
    public float magnification = 0.2f;
    private float flickDirection;
    private float horizontalMoveSpeed = 0f;

    void Update ()
    {
        moveObj.transform.position += new Vector3 (flickDirection, 0f, 0f) * horizontalMoveSpeed * Time.deltaTime;
        if (horizontalMoveSpeed > 0f)
        {
            Debug.Log ("遅くなる");
            horizontalMoveSpeed -= 10.0f * Time.deltaTime;
        }

        if (moveObj.transform.position.x < -3f || moveObj.transform.position.x > 3f)
        {
            horizontalMoveSpeed = 0f;
        }
    }

    private void OnEnable ()
    {
        flickGesture.Flicked += OnFlicked;
    }

    private void OnDisable ()
    {
        flickGesture.Flicked -= OnFlicked;
    }

    private void OnFlicked (object sender, EventArgs e)
    {
        Debug.Log ("フリックされた: " + flickGesture.ScreenFlickVector);
        horizontalMoveSpeed = Mathf.Clamp (Math.Abs (flickGesture.ScreenFlickVector.x), 0, 100);
        horizontalMoveSpeed *= magnification;
        flickDirection = flickGesture.ScreenFlickVector.x > 0 ? -1 : 1;
    }
}