using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public class CellScript : MonoBehaviour
{	
	public List<Transform> Adjacents;
    public int Weight;
    public int AdjacentsOpened = 0;

    public Vector3 Position;
    public int gCost;
    public int hCost;
    public CellScript parent;

    
    // Use this for initialization
    public int fCost
    {
        get
        {
            return gCost + hCost;
        }
    }
}
