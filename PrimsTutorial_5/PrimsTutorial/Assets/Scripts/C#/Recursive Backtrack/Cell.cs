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

	public int fCost
    {
		get
        {
			return gCost + hCost;
		}
	}
}