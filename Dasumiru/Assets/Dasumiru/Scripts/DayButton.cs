using System;
using System.Collections.Generic;
using TMPro;
using TouchScript.Gestures;
using UnityEngine;

public class DayButton : MonoBehaviour
{
    public TapGesture tapGesture;
    private DateTime day;
    private List<TimeAndType> numbers;

    public void Init (DateTime day, List<TimeAndType> numbers)
    {
        this.day = day;
        this.numbers = numbers;
        GetComponentInChildren<TextMeshProUGUI> ().text = day.ToString ("M/d");
    }

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
    }
}