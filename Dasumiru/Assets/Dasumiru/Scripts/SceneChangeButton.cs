using System;
using TouchScript.Gestures;
using UnityEngine;
using UnityEngine.SceneManagement;

public class SceneChangeButton : MonoBehaviour
{
    public string sceneName = "Main";
    public TapGesture tapGesture;

    private void OnEnable ()
    {
        tapGesture.Tapped += OnTapped;
    }

    private void OnDisable ()
    {
        tapGesture.Tapped -= OnTapped;
    }

    private void OnTapped (object sender, EventArgs e)
    {
        Debug.Log ("タップされた");
        SceneManager.LoadScene (sceneName);
    }
}