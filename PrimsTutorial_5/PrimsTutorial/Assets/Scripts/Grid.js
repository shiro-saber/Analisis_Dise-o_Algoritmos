#pragma strict
#pragma downcast

//* -> Assigned in Inspector
public var CellPrefab : Transform; //*
public var GridSize : Vector3; //*

public var GridArr : Transform[,];

public var Set = new Array();
public var CompletedSet = new Array();
private var RandX : int;
private var RandZ : int;
public var mScript : mover;
private var isPaused;

function Start () {
	RandZ = Random.Range((GridSize.z/2), GridSize.z);
	RandX = Random.Range((GridSize.x/2), GridSize.x);
	CreateGrid();
	SetStart(0,0);
	mScript.enabled = false;
}

function CreateGrid(){ 
	var maxXZ : int = Mathf.Max(GridSize.x, GridSize.z);
//	Camera.main.transform.position = Vector3(maxXZ/2f, maxXZ, maxXZ/8f);
	var x : int = GridSize.x;
	var z : int = GridSize.z;
	GridArr = new Transform[x,z];
	for(var ix = 0; ix < GridSize.x; ix++)
	{
		for(var iz = 0; iz < GridSize.z; iz++)
		{
			var newCell : Transform = 
			 Instantiate(CellPrefab, Vector3(ix,0,iz), Quaternion.identity);
			newCell.name = "("+ix+",0,"+iz+")";
			newCell.parent = transform;
			
			var newCellScript : Cell = newCell.GetComponent("Cell");
			newCellScript.Position = Vector3(ix,0,iz);
			
			GridArr[ix,iz] = newCell;
		}
	}
}
function SetStart(x : int, z : int){
	AddToSet(GridArr[x,z]);
	GridArr[x,z].GetComponent.<Renderer>().material.color = Color.green;
}
function AddToSet(toAdd : Transform){
	toAdd.GetComponent.<Renderer>().material.color = Color.black;
	var taScript : Cell = toAdd.GetComponent("Cell");
	taScript.IsOpened = true;
	Set.Unshift(toAdd);
}

var Directions : Vector3[]; //*
function FindNext(){
	
	var previous : Transform = Set[0]; 
	var pScript : Cell = previous.GetComponent("Cell");
	
	var next : Transform;
	var nextScript : Cell;
	
	var prevX : int = pScript.Position.x; 
 	var prevZ : int = pScript.Position.z; 
 	
	var randDirection : Vector3; 
	var randSeed : int = Random.Range(0,4);
	
	var nextX : int;
	var nextZ : int; 
	var counter : int;
	
	do{
		do{
			randDirection = Directions[randSeed];
			nextX = prevX+randDirection.x; 
			nextZ = prevZ+randDirection.z; 
			randSeed = (randSeed+1) % 4;
			counter++;
			if(counter > 4){ 
				if(previous != GridArr[0,0]){
					Set.RemoveAt(0);
					previous.GetComponent.<Renderer>().material.color = Color.gray;
				}  
				return;
			}  
		}while(nextX < 0 || nextZ < 0 || nextX >= GridSize.x || nextZ >= GridSize.z); 
		next = GridArr[nextX,nextZ];
		nextScript = next.GetComponent("Cell"); 
		GridArr[RandX,RandZ].GetComponent.<Renderer>().material.color = Color.red;
	}while(nextScript.IsOpened); 
	AddToSet(next); 
	//DrawDebugLines(10, previous, next);
	ClearWalls(previous, next); 
}

function DrawDebugLines(lines :int, p : Transform, n : Transform)
{
	for(var i = 0; i < lines; i++)
	{
		Debug.DrawLine(p.position, n.position, Color.magenta, 100);
	}
}

function ClearWalls(p : Transform, n : Transform) 
{
	var hitInfo : RaycastHit[]; 
	hitInfo = Physics.RaycastAll(p.position + Vector3.up, n.position - p.position, 1);
	for(var i : int = 0; i < hitInfo.length; i++) {
		Destroy(hitInfo[i].transform.gameObject);
	}
}



function Update () {
	FindNext ();
	if(Input.GetKey(KeyCode.Space) && !isPaused)
	{
		this.enabled = false;
		mScript.enabled = true;
		isPaused = true;
	}
	else if (Input.GetKey(KeyCode.Space) && isPaused)
	{
		this.enabled = true;
		mScript.enabled = false;
		isPaused = false;
	}
}