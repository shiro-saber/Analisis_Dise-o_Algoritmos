using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public class Pathfinding : MonoBehaviour
{
    Grid grid;
    Transform end;
    Transform begin;
    public Export_Data e;
    public bool pathend;
    public float time;
    Cell prevNode;
    // Use this for initialization
    void Start()
    {
        grid = GetComponent<Grid>();
        begin = grid.begin;
        end = grid.end;
    }

    public void FindPath(Vector3 startPos, Vector3 targetPos)
    {
        List<Transform> openSet = new List<Transform>(); //lo que no pasado
        HashSet<Transform> closedSet = new HashSet<Transform>(); //lo que ya pasamos
        openSet.Add(begin); //agregamos el inicio para comparar desde ahi
        prevNode = begin.GetComponent<Cell>();

        while (openSet.Count > 0)
        {
            Transform currentNode = openSet[0];

            for (int i = 0; i < openSet.Count; i++)
                //if (openSet[i].GetComponent<Cell>().fCost < currentNode.GetComponent<Cell>().fCost || openSet[i].GetComponent<Cell>().fCost == currentNode.GetComponent<Cell>().fCost && openSet[i].GetComponent<Cell>().hCost < currentNode.GetComponent<Cell>().hCost) //depende de los costos, agregamos el siguiente
                currentNode = openSet[i];

            openSet.Remove(currentNode); //quitar el nodo de los no recorridos
            closedSet.Add(currentNode); //agregarlo al de recorridos

            if (currentNode == end)
            {
                RetracePath(begin, end); //pintamos caminito
                return;
            }

            foreach (Transform neighbour in grid.GetNeighbours(currentNode.GetComponent<Cell>(), prevNode)) //buscas el vecino dentro de los vecinos de este nodo 
            {
                if (closedSet.Contains(neighbour))//si ya lo pasamos, no lo probamos
                    continue;

                neighbour.GetComponent<Cell>().papa = currentNode.GetComponent<Cell>(); //asignmos el papa que al final de cuentas es como el prevcell pero guardandolo en la misma celda

                if (!openSet.Contains(neighbour.GetComponent<Transform>()))
                {
                    openSet.Add(neighbour); //agregamos el vecino que necesitamos
                    prevNode = currentNode.GetComponent<Cell>(); //el nodo anterior para pasarlo al getneighbours 
                    if (neighbour.position != end.position && neighbour.position != begin.position)
                        neighbour.GetComponent<Renderer>().material.color = Color.blue;
                }
            }
        }
    }

    void RetracePath(Transform startNode, Transform endNode) {
		List<Transform> path = new List<Transform>();
		Transform currentNode = endNode;

        while (currentNode != startNode)
        {
            path.Add(currentNode);
            currentNode = currentNode.GetComponent<Cell>().papa.transform;
            currentNode.GetComponent<Renderer>().material.color = Color.yellow;
        }
		path.Reverse();
        time = Time.time;
        //e.mazeTimes.Add(time);    //al parecer ya no se necesita
        Debug.Log("Pathfinding done! Took " + time + " seconds");
        Export_Data.pathTimes.Add(time); //esto fue lo que agregó para pasar los datos de la var
        pathend = true;
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
