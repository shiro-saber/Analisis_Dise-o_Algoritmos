using UnityEngine;
using System.Collections;

public class go_Export : MonoBehaviour {
    public Export_Data e;
	// Use this for initialization
	void Start ()
    {
        e.enabled = false;
	}
	
	// Update is called once per frame
	void Update ()
    {
	    
	}

    public void save()
    {
        e.Save();
    }
}
