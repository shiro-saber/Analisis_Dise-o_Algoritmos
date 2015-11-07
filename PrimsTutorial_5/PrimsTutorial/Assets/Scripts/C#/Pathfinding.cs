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
		begin = grid.begin.GetComponent<Transform>();
		end = grid.end.GetComponent<Transform>();
        //grid.GetComponents<Cell>().material.color = Color.blue;
	}

	void FindPath(Vector3 startPos, Vector3 targetPos)
    {
		List<Transform> openSet = new List<Transform>();
		HashSet<Transform> closedSet = new HashSet<Transform>();
        openSet.Add(begin.GetComponent<Transform>());

        print(openSet.Count);

		while (openSet.Count > 0)
        {
            print("ESO");

            Transform currentNode = openSet[0];
            //print("nodo: " + currentNode.position.x + ", " + currentNode.position.y);
            //currentNode.GetComponent<Renderer>().material.color = Color.blue;

            for (int i = 0; i < openSet.Count; i++)
            {
                if (openSet[i].GetComponent<Cell>().fCost < currentNode.GetComponent<Cell>().fCost || openSet[i].GetComponent<Cell>().fCost == currentNode.GetComponent<Cell>().fCost && openSet[i].GetComponent<Cell>().hCost < currentNode.GetComponent<Cell>().hCost)
                    currentNode = openSet[i];
                print("ACA LLEGUE");
                print(openSet[i].position);
            }

            print("PARA CUANDO COINCIDAN");
			openSet.Remove(currentNode);
			closedSet.Add(currentNode);

            print(currentNode.position);
            print(end.position);
			if (currentNode == end.GetComponent<Transform>()) {
                print("LLEGUE AL NODO FINAL");
				RetracePath(begin.GetComponent<Transform>(),end.GetComponent<Transform>());
				return;
			}

            foreach (Cell neighbour in grid.GetNeighbours(currentNode.GetComponent<Cell>()))
            {
                if (closedSet.Contains(neighbour.GetComponent<Transform>()))
                {
                    print("Si logre aqui");
                    continue;
                }

                int newMovementCostToNeighbour = currentNode.GetComponent<Cell>().gCost + GetDistance(currentNode, neighbour.GetComponent<Transform>());
                if (newMovementCostToNeighbour < neighbour.gCost || !openSet.Contains(neighbour.GetComponent<Transform>()))
                {
                    print("LO LOGRE");
                    neighbour.gCost = newMovementCostToNeighbour;
                    neighbour.hCost = GetDistance(neighbour.GetComponent<Transform>(), end);
                    neighbour.parent = currentNode.GetComponent<Cell>();
                    print("Corro bien aqui");
                    if (!openSet.Contains(neighbour.GetComponent<Transform>()))
                        print("LO ALEGRE");
                    openSet.Add(neighbour.GetComponent<Transform>());
                    print(neighbour.Position);
                }
            }
		}
	}
	
	void RetracePath(Transform startNode, Transform endNode) {
		List<Transform> path = new List<Transform>();
		Transform currentNode = endNode;
		
		while (currentNode != startNode) {
            print("Estoy pintando!");
			path.Add(currentNode);
			currentNode = currentNode.parent;
			currentNode.GetComponent<Renderer>().material.color = Color.yellow;
		}
		path.Reverse();
		
		grid.path = path;
		
	}

	int GetDistance(Transform nodeA, Transform nodeB) {
		int dstX = Mathf.Abs((int)(nodeA.GetComponent<Cell>().Position.x - nodeB.GetComponent<Cell>().Position.x));
		int dstY = Mathf.Abs((int)(nodeA.GetComponent<Cell>().Position.z - nodeB.GetComponent<Cell>().Position.z));
		
		if (dstX > dstY)
			return 14*dstY + 10* (dstX-dstY);

		return 14*dstX + 10 * (dstY-dstX);
	}

	// Update is called once per frame
	void Update () {
		if (Input.GetKey (KeyCode.A)) {
			FindPath (begin.position, end.position);
            //print ("Deberia pero huevos");
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
