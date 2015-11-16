using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public class PathScript : MonoBehaviour
{
    GridScript g;
    Transform begin;
    Transform end;
    bool pathend;

	// Use this for initialization
	void Start ()
    {
        pathend = false;
        g = GetComponent<GridScript>();
        begin = g.begin;
        end = g.end;
	}

    public void FindParth(Vector3 startPos, Vector3 endPos)
    {
        List<Transform> openSet = new List<Transform>();
        HashSet<Transform> closedSet = new HashSet<Transform>();
        openSet.Add(begin);

        while (openSet.Count > 0)
        {
            Transform currentNode = openSet[0];

            for (int i = 0; i < openSet.Count; i++)
            {

                if (openSet[i].GetComponent<CellScript>().fCost < currentNode.GetComponent<CellScript>().fCost || openSet[i].GetComponent<CellScript>().fCost == currentNode.GetComponent<CellScript>().fCost && openSet[i].GetComponent<CellScript>().hCost < currentNode.GetComponent<CellScript>().hCost)
                    currentNode = openSet[i];
                print("Todo bien despues de agregar el actual al set");
            }

            openSet.Remove(currentNode);
            closedSet.Add(currentNode);

            if (currentNode == end)
            {
                print("LLEGUE AL NODO FINAL");
                RetracePath(begin, end);
                return;
            }

            foreach (Transform neighbour in currentNode.GetComponent<CellScript>().Adjacents)
            {
                if (closedSet.Contains(neighbour.GetComponent<Transform>()))
                    continue;

                int newMovementCostToNeighbour = currentNode.GetComponent<CellScript>().gCost + GetDistance(currentNode, neighbour);
                if (newMovementCostToNeighbour < neighbour.GetComponent<CellScript>().gCost || !openSet.Contains(neighbour))
                {
                    neighbour.GetComponent<CellScript>().gCost = newMovementCostToNeighbour;
                    neighbour.GetComponent<CellScript>().hCost = GetDistance(neighbour, end);
                    neighbour.parent = currentNode;
                    print("Pase hasta definir los costos");

                    if (!openSet.Contains(neighbour.GetComponent<Transform>()))
                    {
                        openSet.Add(neighbour.GetComponent<Transform>());
                        if (neighbour.position != end.position && neighbour.position != begin.position)
                            neighbour.GetComponent<Renderer>().material.color = Color.blue;
                    }
                }
            }
        }
    }

    void RetracePath(Transform startNode, Transform endNode)
    {
        List<Transform> path = new List<Transform>();
        Transform currentNode = endNode;

        while (currentNode != startNode)
        {
            path.Add(currentNode);
            currentNode = currentNode.parent;
            currentNode.GetComponent<Renderer>().material.color = Color.magenta;
        }
        path.Reverse();
        pathend = true;
    }

    int GetDistance(Transform nodeA, Transform nodeB)
    {
        int dstX = Mathf.Abs((int)(nodeA.GetComponent<CellScript>().Position.x - nodeB.GetComponent<CellScript>().Position.x));
        int dstY = Mathf.Abs((int)(nodeA.GetComponent<CellScript>().Position.z - nodeB.GetComponent<CellScript>().Position.z));

        if (dstX > dstY)
            return 14 * dstY + 10 * (dstX - dstY);

        return 14 * dstX + 10 * (dstY - dstX);
    }

    // Update is called once per frame
    void Update ()
    {
        if(Input.GetKey(KeyCode.A))
            FindParth(begin.position, end.position);

        if (pathend)
        {
            Debug.Log("Pathfinding done! Took " + Time.time + " seconds");
            enabled = false;
        }
    }
}
