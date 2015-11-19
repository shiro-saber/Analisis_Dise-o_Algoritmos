using UnityEngine;
using System.Collections;

public class MiniCam : MonoBehaviour {
    public Transform Target;

    public Vector2 TransformPosition(Vector3 position)
    {
        Vector3 offset = position - Target.position;
        Vector2 newPosition = new Vector2(offset.x, offset.z);
        return newPosition;

    }
	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
	
	}
}
