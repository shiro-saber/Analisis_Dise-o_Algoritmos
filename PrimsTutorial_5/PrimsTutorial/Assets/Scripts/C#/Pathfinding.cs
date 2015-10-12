using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public class Pathfinding : MonoBehaviour {
	Grid grid;
	Transform end;
	Transform begin;
	// Use this for initialization
	void Start () {
		grid = GetComponent<Grid>();
		begin = grid.begin;
		end = grid.end;
	}

	/*void FindPath(Vector3 startPos, Vector3 targetPos) {
		List<Transform> openSet = new List<Transform>();
		HashSet<Transform> closedSet = new HashSet<Transform>();
		openSet.Add(begin.GetComponent<Transform>());
		
		while (openSet.Count > 0) {
			Cell currentNode = openSet[0];
			for (int i = 1; i < openSet.Count; i ++) {
				if (openSet[i].fCost < currentNode.fCost || openSet[i].fCost == currentNode.fCost && openSet[i].hCost < currentNode.hCost) {
					currentNode = openSet[i];
				}
			}
			
			openSet.Remove(currentNode);
			closedSet.Add(currentNode);
			
			if (currentNode == end.GetComponent<Transform>()) {
				RetracePath(begin.GetComponent<Transform>(),end.GetComponent<Transform>());
				return;
			}
			
			foreach (Transform neighbour in grid.GetNeighbours(currentNode)) {
				if (closedSet.Contains(neighbour)) {
					continue;
				}
				
				int newMovementCostToNeighbour = currentNode.gCost + GetDistance(currentNode, neighbour);
				if (newMovementCostToNeighbour < neighbour.gCost || !openSet.Contains(neighbour)) {
					neighbour.gCost = newMovementCostToNeighbour;
					neighbour.hCost = GetDistance(neighbour, end.GetComponent<Transform>());
					neighbour.parent = currentNode;
					
					if (!openSet.Contains(neighbour))
						openSet.Add(neighbour);
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
			currentNode.GetComponent<Renderer>().material.color = Color.yellow;
		}
		path.Reverse();
		
		grid.path = path;
		
	}

	int GetDistance(Transform nodeA, Transform nodeB) {
		int dstX = Mathf.Abs((int)(nodeA.Position.x - nodeB.Position.x));
		int dstY = Mathf.Abs((int)(nodeA.Position.z - nodeB.Position.z));
		
		if (dstX > dstY)
			return 14*dstY + 10* (dstX-dstY);

		return 14*dstX + 10 * (dstY-dstX);
	}*/

	// Update is called once per frame
	void Update () {
		if (Input.GetKey (KeyCode.A)) {
			//FindPath (begin.position, end.position);
			print ("Deberia pero huevos");
		}
		//proposito de debug
		/*if (Input.GetKey (KeyCode.A)) {
			print ((string)end.tag);
			print (end.position);
			print ((string)begin.tag);
			print (begin.position);
		}*/
	}
}
