using UnityEngine;
using System.Collections;

public class go_menu : MonoBehaviour {
    public Pathfinding p;
	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
	
	}

    public void go_Menu()
    {
        if(p.pathend)
            Application.LoadLevel(1);
    }
}
