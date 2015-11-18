using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public class Cell : MonoBehaviour
{
	public Vector3 Position;
	public bool IsOpened;

	public int gCost;
	public int hCost;
	public Cell parent;

    public Vector3 norte;
    public Vector3 sur;
    public Vector3 este;
    public Vector3 oeste;

    void Start()
    {
        norte.x = 1;
        norte.z = 0;
        sur.x = -1;
        sur.z = 0;
        oeste.x = 0;
        oeste.z = -1;
        este.x = 0;
        este.z = 1;
    }
	public int fCost
    {
		get
        {
			return gCost + hCost;
		}
	}
}