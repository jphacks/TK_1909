using System;
using TMPro;
using TouchScript.Gestures;
using UnityEngine;

public class ReturnButton : MonoBehaviour
{
    public TapGesture tapGesture;

    private void OnEnable ()
    {
        if (tapGesture == null)
        {
            tapGesture = GetComponent<TapGesture> ();
        }
        tapGesture.Tapped += OnTapped;
    }

    private void OnDisable ()
    {
        tapGesture.Tapped -= OnTapped;
    }

    private void OnTapped (object sender, EventArgs e)
    {
        Debug.Log ("タップされた");
        transform.parent.gameObject.SetActive (false);
    }
}