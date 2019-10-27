using System;
using TouchScript.Gestures;
using UnityEngine;

public class Tap : MonoBehaviour
{
    [SerializeField] TapGesture _tapGesture;

    private void OnEnable ()
    {
        _tapGesture.Tapped += OnTapped;
    }

    private void OnDisable ()
    {
        _tapGesture.Tapped -= OnTapped;
    }

    private void OnTapped (object sender, EventArgs e)
    {
        Debug.Log ("タップされた");
    }
}