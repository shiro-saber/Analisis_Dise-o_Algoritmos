using UnityEngine;
using System.Collections;

public class go_menu2 : MonoBehaviour {
    public PathScript ps;
	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
	
	}

    public void go_menu()
    {
        if (ps.pathend)
            Application.LoadLevel(1);
    }
}
