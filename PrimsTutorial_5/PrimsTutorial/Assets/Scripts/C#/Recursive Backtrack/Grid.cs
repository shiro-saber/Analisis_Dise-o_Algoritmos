using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public class Grid : MonoBehaviour
{
    public Transform CellPrefab;
    public Vector3 GridSize;
    public float Buffer;
    public List<Transform> Set = new List<Transform>();
    public List<Transform> CompletedSet = new List<Transform>();
    private int RandZ;
    private int RandX;
    private bool acabo = false;
    public float time;
    public Export_Data e; //para exportar (aun se esta trabajando)
    public Pathfinding p;
    public Transform begin; //para el pathfinding
    public Transform end; //para el pathfinding

    void Start()
    {
        RandZ = (int)Random.Range((GridSize.z / 2), (GridSize.z/2));
        RandX = (int)Random.Range((GridSize.x / 2), (GridSize.x/2));
        CreateGrid();
        SetStart(0, 0);
        p.enabled = false;
    }
    public Transform[,] GridArr;
    public void CreateGrid()
    {
        int x = (int)GridSize.x;
        int z = (int)GridSize.z;
        GridArr = new Transform[x, z];
        Transform newCell;
        for (int ix = 0; ix < x; ix++)
        {
            for (int iz = 0; iz < z; iz++)
            {
                //newCell = (Transform)Instantiate(CellPrefab, new Vector3(ix, 0, iz) * Buffer, Quaternion.identity);
                newCell = (Transform)Instantiate(CellPrefab, new Vector3(ix, 0, iz) * Buffer, Quaternion.identity);
                newCell.name = string.Format("({0},0,{1})", ix, iz);
                newCell.parent = transform;
                newCell.GetComponent<Cell>().Position = new Vector3(ix, 0, iz);
                GridArr[ix, iz] = newCell;
            }
        }
    }
    void SetStart(int x, int z)
    {
        AddToSet(GridArr[x, z]);
        GridArr[x, z].GetComponent<Renderer>().material.color = Color.green;
        GridArr[x, z].name = string.Format("BEGIN");
        GridArr[x, z].tag = string.Format("BEGIN");
        begin = GridArr[x, z];
    }

    void AddToSet(Transform n)
    {
        Set.Insert(0, n);
        Cell nScript = n.GetComponent<Cell>();
        nScript.IsOpened = true;
        n.GetComponent<Renderer>().material.color = Color.black;
    }

    public List<Vector3> Directions; //*
    void FindNext()
    {

        if (Set.Count == 0)
        {
            GridArr[RandX, RandZ - 1].GetComponent<Renderer>().material.color = Color.red;
            GridArr[RandX, RandZ - 1].name = string.Format("End");
            GridArr[RandX, RandZ - 1].tag = string.Format("END");
            time = Time.time;
            e.mazeTimes.Add(time);
            Debug.Log("We're done! Took " + time + " seconds for a " + GridSize.x + " by " + GridSize.z + " grid.");
            CancelInvoke("FindNext");
            acabo = true;
            return;
        }

        Transform previous = Set[0];
        Cell pScript = Set[0].GetComponent<Cell>();

        Transform next;
        Cell nScript;

        int prevX = (int)pScript.Position.x;
        int prevZ = (int)pScript.Position.z;

        int randSeed = Random.Range(0, 4);
        int counter = 0;

        int nextX;
        int nextZ;


        do
        {
            do
            {
                Vector3 randDirection = Directions[randSeed];
                nextX = prevX + (int)randDirection.x;
                nextZ = prevZ + (int)randDirection.z;
                randSeed = (randSeed + 1) % 4;
                counter++;
                if (counter > 4)
                {
                    AddToCompletedSet(previous);
                    return;
                }
            } while (nextX < 0 || nextZ < 0 || nextX >= GridSize.x || nextZ >= GridSize.z);
            next = GridArr[nextX, nextZ];
            nScript = next.GetComponent<Cell>();
            end = GridArr[RandX, RandZ - 1];
        } while (nScript.IsOpened);
        ClearWalls(previous, next);
        AddToSet(next);
    }

    void AddToCompletedSet(Transform toAdd)
    {
        Set.Remove(toAdd);
        CompletedSet.Add(toAdd);
        if (toAdd != GridArr[0, 0])
            toAdd.GetComponent<Renderer>().material.color = Color.magenta;

    }

    void ClearWalls(Transform p, Transform n)
    {
        RaycastHit[] hitInfo;
        hitInfo = Physics.RaycastAll(p.position + Vector3.up, n.position - p.position, Buffer);
        foreach (RaycastHit hit in hitInfo)
        {
            Destroy(hit.transform.gameObject);
        }
    }

    //Se supone aqui estamos quitando todos los vecinos que no se pueden pasar, que al fin y al cabo debería regresar solo uno o dos neighbour pasable 
    public List<Transform> GetNeighbours(Cell node, Cell prevNode)
    {
        List<Transform> neighbours = new List<Transform>();
        //Debug.Log("Estas comparando " + node.name + " mi celda pasada es " + prevNode.name);

        for (int x = -1; x <= 1; x++)
        {
            for (int y = -1; y <= 1; y++)
            {
                if (x == -1 && y == -1) //no puede ser -1, -1 para que no sea diagonal
                    continue;

                if (x == 0 && y == 0) //no puede ser 0, 0 porque el nodo actual no es vecino del nodo actual
                    continue;

                if (x == 1 && y == 1) // no puede ser 1,1 para que no sea diagonal
                    continue;

                if (x == -1 && y == 1) //no puede ser -1, 1 para que no sea diagonal
                    continue;

                if (x == 1 && y == -1) //no puede ser 1, -1 para que no sea diagonal
                    continue;

                int checkX = (int)node.Position.x + x; //la posicion del nodo ahorita mas x que sera -1,0 o 1 es el siguiente en x
                int checkY = (int)node.Position.z + y; //la posicion del nodo ahorita mas y que sera 1,-1 o 0 es el siguiente en y
             
                if (checkX >= 0 && checkX < GridSize.x && checkY >= 0 && checkY < GridSize.z) //para que la siguiente no sea mayor al tamaño del grid o menor a 0,0 que es el inicio
                {
                    neighbours.Add(GridArr[checkX, checkY]); //agregamos todos los vecinos posibles

                    foreach (Transform t in GridArr[checkX, checkY].transform)//para todos los hijos del next, para obtener los tags de las paredes
                    {
                        foreach (Transform g in node.transform) //para todos los hijos del actual, para obtener los tags de las paredes
                        {
                            if (x == 0 && y == 1 && GridArr[checkX, checkY] != prevNode && t.tag == "sur" && g.tag == "norte")  //si el tag del next es sur el del actual es norte no puedes ir arriba
                            {
                                neighbours.Remove(GridArr[checkX, checkY]);
                                //Debug.Log("Removi " + GridArr[checkX, checkY].name + "del set");
                            }
                            else if (y == -1 && x == 0 && GridArr[checkX, checkY] != prevNode && t.tag == "norte" && g.tag == "sur") //si el de next es nortye el del actual sur no puedes ir abajo
                            {
                                neighbours.Remove(GridArr[checkX, checkY]);
                                //Debug.Log("Removi " + GridArr[checkX, checkY].name + "del set");
                            }
                            else if (y == 0 && x == -1 && GridArr[checkX, checkY] != prevNode && t.tag == "este" && g.tag == "oeste") //si el de next en este el de actual es oeste no puede ir izquierda
                            {
                                neighbours.Remove(GridArr[checkX, checkY]);
                                //Debug.Log("Removi " + GridArr[checkX, checkY].name + "del set");
                            }
                            else if (y == 0 && x == 1 && GridArr[checkX, checkY] != prevNode && t.tag == "oeste" && g.tag == "este") //si el de next es oeste y el actual este no puede ir derecha
                            {
                                neighbours.Remove(GridArr[checkX, checkY]);
                                //Debug.Log("Removi " + GridArr[checkX, checkY].name + "del set");
                            }
                        }
                    }
                }
            }
        }

        return neighbours;
    }

    void Update()
    {
        if (!acabo)
            FindNext();
        else
        {
            enabled = false;
            p.enabled = true;
        }
    }
}