using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEditor;
using System.IO;

public class Tools { 

    [MenuItem("Tools/Temp")]
    static void _00()
    {

        var files = File.ReadAllLines("Assets/UnityEditorScripts/Editor/exports.txt");

        foreach(var file in files)
        {
            var obj = AssetDatabase.LoadAssetAtPath<GameObject>(file);
            if(obj) AutoConfig.Export(obj);

        }
    }

}
