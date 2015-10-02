
function OnGUI () { 
	if (GUI.Button (Rect(50,50,80,20), "Idle")) { GetComponent.<Animation>().CrossFade ("idle");
	}
	if (GUI.Button (Rect(50,75,80,20), "Creep")) { GetComponent.<Animation>().CrossFade ("Creep");
	}
	if (GUI.Button (Rect(50,100,80,20), "Walk")) { GetComponent.<Animation>().CrossFade ("Walk");
	}
	if (GUI.Button (Rect(50,125,80,20), "Run")) { GetComponent.<Animation>().CrossFade ("Run");
	}
	if (GUI.Button (Rect(50,150,80,20), "Full_Jump")) { GetComponent.<Animation>().CrossFade ("Full_Jump");
	}
	if (GUI.Button (Rect(50,175,80,20), "Jump pose1")) { GetComponent.<Animation>().CrossFade ("Jump Pose1");
	}
	if (GUI.Button (Rect(50,200,80,20), "Jump Pose2")) { GetComponent.<Animation>().CrossFade ("Jump Pose2");
	}
	if (GUI.Button (Rect(50,225,80,20), "Jump Pose3")) { GetComponent.<Animation>().CrossFade ("Jump Pose3");
	}
	if (GUI.Button (Rect(50,250,80,20), "Jump Pose4")) { GetComponent.<Animation>().CrossFade ("Jump Pose4");
	}
	if (GUI.Button (Rect(50,275,80,20), "Land on thing")) { GetComponent.<Animation>().CrossFade ("Land_on_thing");
	}
	if (GUI.Button (Rect(50,300,80,20), "Landed eat")) { GetComponent.<Animation>().CrossFade ("Landed_eat");
	}
	if (GUI.Button (Rect(50,325,80,20), "Jump off thing")) { GetComponent.<Animation>().CrossFade ("Jump_off_thing");
	}
	if (GUI.Button (Rect(50,350,80,20), "Look right")) { GetComponent.<Animation>().CrossFade ("Look_right");
	}
	if (GUI.Button (Rect(50,375,80,20), "Look left")) { GetComponent.<Animation>().CrossFade ("Look_left");
	}
	if (GUI.Button (Rect(50,400,80,20), "Sniff")) { GetComponent.<Animation>().CrossFade ("Sniff");
	}
	if (GUI.Button (Rect(50,425,80,20), "Hit")) { GetComponent.<Animation>().CrossFade ("Hit");
	}
	if (GUI.Button (Rect(50,450,80,20), "Death")) { GetComponent.<Animation>().CrossFade ("Death");
	}
	/////////////////////
	//if (GUI.Button (Rect(100,50,80,20), "Saddle")) { transform.Find("saddle").GetComponent(MeshRenderer).Active;
	//}
	
	
}