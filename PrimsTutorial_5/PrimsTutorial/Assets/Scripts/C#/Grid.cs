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
    public int GridX;
    public int GridY;

	public Pathfinding p;

	//public mover mscript;
	Transform newRaptor;
	public Transform raptor;

	public Cell begin;
	public Cell end;

	void Start ()
	{
        GridX = (int)GridSize.x;
        GridY = (int)GridSize.y;
		RandZ = (int)Random.Range((GridSize.z/2), GridSize.z);
		RandX = (int)Random.Range((GridSize.x/2), GridSize.x);
		CreateGrid ();
		SetStart (0, 0);
		p.enabled = false;
		//mscript.enabled = false;
	}
	public Transform[,]GridArr;
	public void CreateGrid ()
	{
		int x = (int)GridSize.x;
		int z = (int)GridSize.z;
		int maxXZ = Mathf.Max (x, z);
		GridArr = new Transform[x, z];
		Transform newCell;
		for (int ix = 0; ix < x; ix++) {
			for (int iz = 0; iz < z; iz++) {
				newCell = (Transform)Instantiate (CellPrefab, new Vector3 (ix, 0, iz) * Buffer, Quaternion.identity);
				newCell.name = string.Format ("({0},0,{1})", ix, iz);
				newCell.parent = transform;
				newCell.GetComponent<Cell> ().Position = new Vector3 (ix, 0, iz);
				GridArr [ix, iz] = newCell;
			}
		}
	}
	void SetStart (int x, int z)
	{
		AddToSet(GridArr[x,z]);
		GridArr [x, z].GetComponent<Renderer> ().material.color = Color.green;
		GridArr[x, z].name = string.Format("BEGIN");
		GridArr[x, z].tag = string.Format("begin");
		begin = GridArr [x, z].GetComponent<Cell>();
	}

	void AddToSet (Transform n)
	{
		Set.Insert (0, n);
		Cell nScript = n.GetComponent<Cell> ();
		nScript.IsOpened = true;
		n.GetComponent<Renderer>().material.color = Color.black;
	}
	
	public List<Vector3> Directions; //*
	void FindNext ()
	{
		
		if (Set.Count == 0) {
            GridArr[RandX, RandZ].GetComponent<Renderer>().material.color = Color.red;
            GridArr[RandX, RandZ].name = string.Format("End");
            GridArr[RandX, RandZ].tag = string.Format("end");
            Debug.Log ("We're done! Took " + Time.timeSinceLevelLoad + " seconds for a " + GridSize.x + " by " + GridSize.z + " grid.");
			CancelInvoke("FindNext");
			acabo = true;
			return;
		}
		
		Transform previous = Set [0];
		Cell pScript = Set [0].GetComponent<Cell> ();
		
		Transform next;
		Cell nScript;
		
		int prevX = (int)pScript.Position.x;
		int prevZ = (int)pScript.Position.z;
		
		int randSeed = Random.Range (0, 4);
		int counter = 0;
		
		int nextX;
		int nextZ;
		
		
		do {
			do {
				Vector3 randDirection = Directions [randSeed];
				nextX = prevX + (int)randDirection.x;
				nextZ = prevZ + (int)randDirection.z;
				randSeed = (randSeed + 1) % 4;
				counter++;
				if (counter > 4) {
					AddToCompletedSet (previous);
					return;
				}
			} while(nextX < 0 || nextZ < 0 || nextX >= GridSize.x || nextZ >= GridSize.z);
			next = GridArr [nextX, nextZ];
			nScript = next.GetComponent <Cell> ();
			end = GridArr [RandX, RandZ].GetComponent<Cell>();
		} while(nScript.IsOpened);
		ClearWalls (previous, next);
		AddToSet (next);
	}
	
	void AddToCompletedSet (Transform  toAdd)
	{
		Set.Remove (toAdd);
		CompletedSet.Add (toAdd);
		if(toAdd != GridArr[0,0])
			toAdd.GetComponent<Renderer>().material.color = Color.gray;
		
	}
	
	void ClearWalls(Transform p, Transform n)
	{
		RaycastHit[] hitInfo;
		hitInfo = Physics.RaycastAll (p.position + Vector3.up, n.position - p.position, Buffer);
		foreach (RaycastHit hit in hitInfo) {
			Destroy (hit.transform.gameObject);
		}
	}

	public List<Cell> GetNeighbours(Cell node) {
		List<Cell> neighbours = new List<Cell>();
		
		for (int x = -1; x <= 1; x++) {
			for (int y = -1; y <= 1; y++) {
				if (x == 0 && y == 0)
					continue;
				
				int checkX =(int)GridSize.x + x;
				int checkY =(int)GridSize.z + y;
				
				if (checkX >= 0 && checkX < GridSize.x && checkY >= 0 && checkY < GridSize.z) {
					neighbours.Add(GridArr[checkX,checkY].GetComponent<Cell>());
				}
			}
		}
		
		return neighbours;
	}
	public List<Transform> path;
	void Update ()
	{
		if (!acabo) 
			FindNext (); 
		else 
		{
            enabled = false;
			p.enabled = true;
            newRaptor = (Transform)Instantiate(raptor, new Vector3(0, 0, 0), Quaternion.identity);
            newRaptor.localScale = new Vector3(0.2f, 0.2f, 0.2f);
            newRaptor.GetComponent<mover>().enabled = false;
            newRaptor.GetComponent<mover> ().enabled = true;
            if(Input.GetKeyDown(KeyCode.A))
                for (int i = 0; i < path.Count; i++)
                    path[i].GetComponent<Renderer>().material.color = Color.green;
		}
		if(Input.GetKeyDown(KeyCode.Space))
		{
			Application.LoadLevel(0);
		}
	}
}