using UnityEngine;
using System;
using System.Text;
using System.IO;
using System.Collections;
using System.Collections.Generic;

public class Export_Data : MonoBehaviour
{
    private List<string[]> rowData = new List<string[]>();
    public static List<float> mazeTimes = new List<float>();
    public static List<float> pathTimes = new List<float>();
    public static List<float> primTimes = new List<float>();
    public static List<float> primPath = new List<float>();
    string[] rowDataTemp = new string[5];

    void Start()
    {
        rowDataTemp[0] = " ";
        rowDataTemp[1] = "Growing Tree";
        rowDataTemp[2] = "A* Growing Tree";
        rowDataTemp[3] = "Prim";
        rowDataTemp[4] = "A* Prim";
        rowData.Add(rowDataTemp);
        DontDestroyOnLoad(transform.gameObject);// si no es con player prefs para poner el valor de la variable 
        //otra manera de conseguirlo es cambiar
    }

    //esta sería la función para imprimir los datos en la consola.
    public static int imprimirDatos()
    {
        //debe ser un ciclo y la impresíón de listas en c#
        return 1;
    }

    void update()
    {
        Save();
    }
    // Use this for initialization
    //la clase, hacerla como public static para todas las escenas
    //si no sirve usar un done des
    public void Save()
    {
        /* hay que sacar los tiempos */
        //public static List<float> pathTimes = new List<float>();
    //mazeTimes = g.recursiveTimes;
    //pathTimes = p.recursivepath;
    //primTimes = gs.primtime;
    //primPath = ps.pathprim;
    /*Ya sacamos los tiempos a exportar*/

        //después tendríamos que hacer la clase public static para imprimir donde queramos la condición

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
       

        if (mazeTimes.Count != 0 && pathTimes.Count != 0 && rowDataTemp.Length < 4)
        {
            for (int i = 0; i < mazeTimes.Count; ++i)
            {
                rowDataTemp = new string[2];
                rowDataTemp[1] = mazeTimes[i].ToString();
                rowDataTemp[2] = pathTimes[i].ToString();
                rowData.Add(rowDataTemp);
            }
        }
        else if (rowDataTemp.Length > 4)
        {
            rowDataTemp = new string[2];
            rowDataTemp[1] = " ";
            rowDataTemp[2] = " ";
            rowData.Add(rowDataTemp);
        }

        if (primTimes.Count != 0 && primPath.Count != 0 && rowDataTemp.Length > 5)
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
