using UnityEngine;
using System;
using System.Text;
using System.IO;
using System.Collections;
using System.Collections.Generic;

public class Export_Data : MonoBehaviour {
    private List<string[]> rowData = new List<string[]>();
    public List<float> mazeTimes = new List<float>();
    public List<float> pathTimes = new List<float>();
    public List<float> primTimes = new List<float>();
    public List<float> primPath = new List<float>();
    
    // Use this for initialization
    public void Save()
    {
        string[] rowDataTemp = new string[5];
        rowDataTemp[0] = " ";
        rowDataTemp[1] = "Growing Tree";
        rowDataTemp[2] = "A* Growing Tree";
        rowDataTemp[3] = "Prim";
        rowDataTemp[4] = "A* Prim";
        rowData.Add(rowDataTemp);

        int max = Mathf.Max(mazeTimes.Count, pathTimes.Count, primPath.Count, primTimes.Count);

        if (max != 0)
        {
            for (int m = 0; m < max; ++m)
            {
                rowDataTemp = new string[1];
                rowDataTemp[0] = "Tiempo " + m;
                rowData.Add(rowDataTemp);
            }
        }
        else
            print("NADA QUE EXPORTAR");

        if (mazeTimes.Count != 0 && pathTimes.Count != 0)
        {
            for (int i = 0; i < mazeTimes.Count; ++i)
            {
                rowDataTemp = new string[2];
                rowDataTemp[1] = mazeTimes[i].ToString();
                rowDataTemp[2] = pathTimes[i].ToString();
                rowData.Add(rowDataTemp);
            }
        }

        if (primTimes.Count != 0 && primPath.Count != 0)
        {
            for (int j = 0; j < primTimes.Count; ++j)
            {
                rowDataTemp = new string[2];
                rowDataTemp[3] = primTimes[j].ToString();
                rowDataTemp[4] = primPath[j].ToString();
                rowData.Add(rowDataTemp);
            }
        }

        string[][] output = new string[rowData.Count][];

        for (int k = 0; k < output.Length; ++k)
            output[k] = rowData[k];

        int length = output.GetLength(0);
        string delimiter = ",";

        StringBuilder sb = new StringBuilder();

        for (int l = 0; l < length; ++l)
            sb.AppendLine(string.Join(delimiter, output[l]));

        string filePath = getPath();
        print(filePath);

        StreamWriter outStream = System.IO.File.CreateText(filePath);
        outStream.WriteLine(sb);
        outStream.Close();
    }

    private string getPath()
    {
        #if UNITY_EDITOR
        return Application.dataPath + "/CSV" + "Tiempos.csv";
        #elif UNITY_ANDROID
        return Application.persistentDataPath + "Tiempos.csv";
        #elif UNITY_IPHONE
        return Application.persistentDataPath + "/" + "Tiempos.csv";
        #else
        return Application.dataPath + "/" + "Tiempos.csv";
        #endif
    }
}
