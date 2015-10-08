using UnityEngine;
using System.Collections;
using System.Collections.Generic;


public class GridScript : MonoBehaviour
{
    public Transform CellPrefab;
    public Transform Raptor;
    public Vector3 Size;
    public Transform[,] Grid;

    // Use this for initialization
    void Start()
    {
        CreateGrid();
        SetRandomNumbers();
        SetAdjacents();
        SetStart();
        FindNext();
    }

    void CreateGrid()
    {
        Grid = new Transform[(int)Size.x, (int)Size.z];

        for (int x = 0; x < Size.x; x++)
        {
            for (int z = 0; z < Size.z; z++)
            {
                Transform newCell;
                newCell = (Transform)Instantiate(CellPrefab, new Vector3(x, 0, z), Quaternion.identity);
                newCell.name = string.Format("({0},0,{1})", x, z);
                newCell.parent = transform;
                newCell.GetComponent<CellScript>().Position = new Vector3(x, 0, z);
                Grid[x, z] = newCell;
            }
        }
        //Camera.main.transform.position = Grid[(int)(Size.x/2f),(int)(Size.z/2f)].position + Vector3.up*20f;
        //Camera.main.orthographicSize = Mathf.Max(Size.x, Size.z);
    }

    void SetRandomNumbers()
    {
        foreach (Transform child in transform)
        {
            int weight = Random.Range(0, 10);
            child.GetComponentInChildren<TextMesh>().text = weight.ToString();
            child.GetComponent<CellScript>().Weight = weight;
        }
    }

    void SetAdjacents()
    {
        for (int x = 0; x < Size.x; x++)
        {
            for (int z = 0; z < Size.z; z++)
            {
                Transform cell;
                cell = Grid[x, z];
                CellScript cScript = cell.GetComponent<CellScript>();

                if (x - 1 >= 0)
                   cScript.Adjacents.Add(Grid[x - 1, z]);
                if (x + 1 < Size.x)
                    cScript.Adjacents.Add(Grid[x + 1, z]);
                if (z - 1 >= 0)
                    cScript.Adjacents.Add(Grid[x, z - 1]);
                if (z + 1 < Size.z)
                    cScript.Adjacents.Add(Grid[x, z + 1]);

                cScript.Adjacents.Sort(SortByLowestWeight);
            }
        }
    }

   int SortByLowestWeight(Transform inputA, Transform inputB)
    {
        int a = inputA.GetComponent<CellScript>().Weight; //peso de a
        int b = inputB.GetComponent<CellScript>().Weight; //peso de b
        return a.CompareTo(b);
    }

    public List<Transform> Set;
    public List<List<Transform>> AdjSet;

    void SetStart()
    {
        Set = new List<Transform>();
        AdjSet = new List<List<Transform>>();

        for (int i = 0; i < 10; i++)
            AdjSet.Add(new List<Transform>());
        
        Grid[0, 0].GetComponent<Renderer>().material.color = Color.green;
        Transform raptor;
        raptor = (Transform)Instantiate(Raptor, new Vector3(0f, 0.1f, 0f), Quaternion.identity);
        AddToSet(Grid[0, 0]);
    }

    void AddToSet(Transform toAdd)
    {
        Set.Add(toAdd);

        foreach (Transform adj in toAdd.GetComponent<CellScript>().Adjacents)
        {
            adj.GetComponent<CellScript>().AdjacentsOpened++;
            if (!Set.Contains(adj) && !(AdjSet[adj.GetComponent<CellScript>().Weight].Contains(adj)))
                AdjSet[adj.GetComponent<CellScript>().Weight].Add(adj);
        }
    }

    void FindNext()
    {
        Transform next;

        do
        {
            bool empty = true;
            int lowestList = 0;
            for (int i = 0; i < 10; i++)
            {
                lowestList = i;
                if (AdjSet[i].Count > 0)
                {
                    empty = false;
                    break;
                }
            }
            if (empty)
            {
                Debug.Log("We're Done, " + Time.timeSinceLevelLoad + " seconds taken");
                CancelInvoke("FindNext");
                Set[Set.Count - 1].GetComponent<Renderer>().material.color = Color.red;
                foreach (Transform cell in Grid)
                {
                //    if (!Set.Contains(cell))
                //    {
                //        //cell.Translate(Vector3.up);	
                //        //cell.GetComponent<Renderer>().material.color = Color.black;
                //    }
                }
                return;
            }
            next = AdjSet[lowestList][0];
            AdjSet[lowestList].Remove(next);
        } while (next.GetComponent<CellScript>().AdjacentsOpened >= 2);

        next.GetComponent<Renderer>().material.color = Color.white;
        AddToSet(next);
        Invoke("FindNext", 0);
    }


    void Update()
    {
        if (Input.GetKeyDown(KeyCode.F1)) //nada mas reinicia el nivel
        {
            Application.LoadLevel(0);
        }
    }
}
