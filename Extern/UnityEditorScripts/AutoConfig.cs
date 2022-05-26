using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.IO;
using System.Text;

public class AutoConfig
{
    private static string ExportedPath => Application.streamingAssetsPath;


    public static void Export(GameObject go)
    {
        if (!Directory.Exists(ExportedPath)) Directory.CreateDirectory(ExportedPath);

        var folderPath = Path.Combine(ExportedPath, go.name);
        var splitsFoloderPath = Path.Combine(folderPath, "Splits");
        var textureFolderPath = Path.Combine(folderPath, "Textures");
        if (!Directory.Exists(folderPath)) Directory.CreateDirectory(folderPath);
        if (!Directory.Exists(splitsFoloderPath)) Directory.CreateDirectory(splitsFoloderPath);
        if (!Directory.Exists(textureFolderPath)) Directory.CreateDirectory(textureFolderPath);

        var sb = new StringBuilder();
        int submeshCount = 0;

        var meshes = new List<Mesh>();

        var materials = new List<Material>();
        var texturesDictionary = new Dictionary<string, Texture>();
        var textures = new List<Texture>();

        foreach (var i in go.GetComponentsInChildren<SkinnedMeshRenderer>())
        {
            submeshCount += i.sharedMesh.subMeshCount;
            meshes.Add(i.sharedMesh);

            foreach (var m in i.sharedMaterials)
                materials.Add(m);
        }

        foreach (var mat in materials)
        {
            var texture = mat.mainTexture;

            if (texture)
                texturesDictionary[texture.name] = mat.mainTexture;
        }

        foreach (var texture in texturesDictionary)
            textures.Add(texture.Value);


        sb.AppendLine("[SubMeshCount]");
        sb.AppendLine($"{submeshCount}");

        sb.AppendLine();

        sb.AppendLine("[TextureCount]");
        sb.AppendLine($"{textures.Count}");

        sb.AppendLine();
        sb.AppendLine("[SubMeshFiles]");


        foreach (var mesh in meshes)
        {
            for (int i = 0; i < mesh.subMeshCount; i++)
                sb.AppendLine($"{go.name}_{mesh.name}_{i}.txt");
        }


        sb.AppendLine();
        sb.AppendLine("[TextureFiles]");

        foreach (var texture in textures)
            sb.AppendLine(texture.name + ".png");


        sb.AppendLine();
        sb.AppendLine("[Map]");

        for (int i = 0; i < materials.Count; i++)
            sb.AppendLine($"{textures.IndexOf(materials[i].mainTexture)}");

        //export splits config file
        File.WriteAllText(Path.Combine(folderPath, "splits_config.txt"), sb.ToString());

        //export meshes data
        MeshData.Export(go, Path.Combine(splitsFoloderPath, $"{go.name}.txt"), true);

        //export textures data
        foreach (var texture in textures)
        {
            var texture2D = texture as Texture2D;
            if(texture2D)
            {
                var bytes = texture2D.EncodeToPNG();
                File.WriteAllBytes(Path.Combine(textureFolderPath, texture.name + ".png"), bytes);
            }
        }
    }
}
