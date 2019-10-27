using TouchScript.Gestures.TransformGestures;
using UnityEngine;

public class Drag : MonoBehaviour
{
    public float yPos = 0f;
    public TransformGesture transformGesture;
    private Transform imgObjTrans;

    void Start ()
    {
        imgObjTrans = transformGesture.gameObject.transform;
    }

    private void LateUpdate ()
    {
        imgObjTrans.position = new Vector3 (imgObjTrans.position.x, yPos, 0f);
    }
}