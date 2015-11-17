using UnityEngine;
using System.Collections;

public class go_Export : MonoBehaviour {
    public Export_Data e = new Export_Data();
	// Use this for initialization
	void Start ()
    {
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
