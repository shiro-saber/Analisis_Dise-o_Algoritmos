using UnityEngine;
using System.Collections;

public class Blip : MonoBehaviour {
    public Transform target;

    MiniCam map;
    RectTransform myRecTransform;
	// Use this for initialization
	void Start ()
    {
        map = GetComponentInParent<MiniCam>();
        myRecTransform = GetComponent<RectTransform>();
	}
	
	// Update is called once per frame
	void LateUpdate () {
        Vector2 newPosition = map.TransformPosition(target.position);
        myRecTransform.localPosition = newPosition;
	}
}
