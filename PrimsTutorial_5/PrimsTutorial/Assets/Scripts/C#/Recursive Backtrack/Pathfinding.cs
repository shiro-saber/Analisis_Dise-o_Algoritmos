using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public class Pathfinding : MonoBehaviour {
	Grid grid;
	Transform end;
	Transform begin;
    public Export_Data e;
    bool pathend;
    public float time;
	// Use this for initialization
	void Start () {
		grid = GetComponent<Grid>();
		begin = grid.begin;
		end = grid.end;
	}

	public void FindPath(Vector3 startPos, Vector3 targetPos)
    {
		List<Transform> openSet = new List<Transform>();
		HashSet<Transform> closedSet = new HashSet<Transform>();
        openSet.Add(begin);

		while (openSet.Count > 0)
        {
            Transform currentNode = openSet[0];
            
            for (int i = 0; i < openSet.Count; i++)
                if (openSet[i].GetComponent<Cell>().fCost < currentNode.GetComponent<Cell>().fCost || openSet[i].GetComponent<Cell>().fCost == currentNode.GetComponent<Cell>().fCost && openSet[i].GetComponent<Cell>().hCost < currentNode.GetComponent<Cell>().hCost)
                    currentNode = openSet[i];
            
            openSet.Remove(currentNode);
			closedSet.Add(currentNode);

            if (currentNode == end) {
            	RetracePath(begin,end);
				return;
			}

            foreach (Transform neighbour in grid.GetNeighbours(currentNode.GetComponent<Cell>())) 
            {
                if (closedSet.Contains(neighbour) || !neighbour.GetComponent<Cell>().IsOpened)
                    continue;
            
                int newMovementCostToNeighbour = currentNode.GetComponent<Cell>().gCost + GetDistance(currentNode, neighbour);
                if (newMovementCostToNeighbour < neighbour.GetComponent<Cell>().gCost || !openSet.Contains(neighbour))
                {
                    neighbour.GetComponent<Cell>().gCost = newMovementCostToNeighbour;
                    neighbour.GetComponent<Cell>().hCost = GetDistance(neighbour, end);
                    neighbour.parent = currentNode;
                   
                    if (!openSet.Contains(neighbour.GetComponent<Transform>()) && neighbour.GetComponent<Cell>().GetComponentInChildren<Cell>().tag != "pared")
                    {
                        openSet.Add(neighbour);
                        if(neighbour.position != end.position && neighbour.position != begin.position)
                            neighbour.GetComponent<Renderer>().material.color = Color.blue;
                    }
                }
            }
		}
	}
	
	void RetracePath(Transform startNode, Transform endNode) {
		List<Transform> path = new List<Transform>();
		Transform currentNode = endNode;
		
		while (currentNode != startNode) {
            path.Add(currentNode);
			currentNode = currentNode.parent;
			currentNode.GetComponent<Renderer>().material.color = Color.magenta;
		}
		path.Reverse();
        time = Time.time;
        e.pathTimes.Add(time);
        Debug.Log("Pathfinding done! Took " + time + " seconds");
        pathend = true;
    }

	int GetDistance(Transform nodeA, Transform nodeB)
    {
		int dstX = Mathf.Abs((int)(nodeA.GetComponent<Cell>().Position.x - nodeB.GetComponent<Cell>().Position.x));
		int dstY = Mathf.Abs((int)(nodeA.GetComponent<Cell>().Position.z - nodeB.GetComponent<Cell>().Position.z));
		
		if (dstX > dstY)
			return 14*dstY + 10* (dstX-dstY);

		return 14*dstX + 10 * (dstY-dstX);
	}

    // Update is called once per frame
    void Update()
    {
        if (!pathend)
            FindPath(begin.GetComponent<Transform>().position, end.GetComponent<Transform>().position);
        
        if (Input.GetKey(KeyCode.KeypadEnter) && pathend)
            Application.LoadLevel(1);
    }
}
