using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Text;


class MeshData
{
    /*
    uint vertexCount;
    uint indexCount;
    Vertex[] vertices;
    uint[] indices;

    struct Vertex
    {
        Vector3 position;
        Vector3 normal;
        Vector2 uv;
    }
    */

    static List<Mesh> GetMeshes(GameObject go)
    {
        var meshes = new List<Mesh>();

        foreach (var i in go.GetComponentsInChildren<MeshFilter>())
            meshes.Add(i.mesh);

        foreach (var i in go.GetComponentsInChildren<SkinnedMeshRenderer>())
            meshes.Add(i.sharedMesh);

        return meshes;
    }

    public static void Export(GameObject go, string path, bool splitMesh = false)
    {
        if (!go || path == null) return;

        var meshes = GetMeshes(go);
        var sb = new StringBuilder();

        if (!splitMesh)
        {
            var vertices = new List<Vector3>();
            var normals = new List<Vector3>();
            var uvs = new List<Vector2>();
            var indices = new List<int>();

            int indexOffset = 0;

            foreach (var mesh in meshes)
            {
                //vertex
                foreach (var vertex in mesh.vertices)
                    vertices.Add(vertex);

                //uv
                foreach (var uv in mesh.uv)
                    uvs.Add(uv);

                //normal
                foreach (var normal in mesh.normals)
                    normals.Add(normal);

                //index
                for (int i = 0; i < mesh.triangles.Length; i += 3)
                {
                    int a = mesh.triangles[i + 2];
                    int b = mesh.triangles[i + 1];
                    int c = mesh.triangles[i];

                    indices.Add(a + indexOffset);
                    indices.Add(b + indexOffset);
                    indices.Add(c + indexOffset);
                }

                indexOffset += mesh.vertices.Length;
            }

            sb.Append("[Vertex Count]\n");
            sb.Append(vertices.Count).Append("\n");
            sb.Append("[Index Count]\n");
            sb.Append(indices.Count).Append("\n");

            foreach (var vertex in vertices)
                sb.Append("v").Append(" ").Append($"{vertex.x} {vertex.y} {vertex.z}\n");

            foreach (var uv in uvs)
                sb.Append("t").Append(" ").Append($"{uv.x} {uv.y}\n");

            foreach (var normal in normals)
                sb.Append("n").Append(" ").Append($"{normal.x} {normal.y} {normal.z}\n");

            foreach (var index in indices)
                sb.Append("i").Append(" ").Append($"{index}\n");

            System.IO.File.WriteAllText(path, sb.ToString());
        }
        else
        {
            foreach (var mesh in meshes)
            {
                for (int di = 0; di < mesh.subMeshCount; di++)
                {
                    sb.Clear();

                    var descriptor = mesh.GetSubMesh(di);

                    var vertices = new List<Vector3>(descriptor.vertexCount);
                    var normals = new List<Vector3>(descriptor.vertexCount);
                    var uvs = new List<Vector2>(descriptor.vertexCount);
                    var indices = new List<int>(descriptor.indexCount);

                    for (int vi = 0; vi < descriptor.vertexCount; vi++)
                        vertices.Add(mesh.vertices[descriptor.firstVertex + vi]);

                    for (int ti = 0; ti < descriptor.vertexCount; ti++)
                        uvs.Add(mesh.uv[descriptor.firstVertex + ti]);

                    for (int ni = 0; ni < descriptor.vertexCount; ni++)
                        normals.Add(mesh.normals[descriptor.firstVertex + ni]);

                    for (int ii = 0; ii < descriptor.indexCount; ii += 3)
                    {
                        var a = mesh.triangles[descriptor.indexStart + descriptor.baseVertex + (ii + 2)];
                        var b = mesh.triangles[descriptor.indexStart + descriptor.baseVertex + (ii + 1)];
                        var c = mesh.triangles[descriptor.indexStart + descriptor.baseVertex + (ii + 0)];

                        indices.Add(a - descriptor.firstVertex);
                        indices.Add(b - descriptor.firstVertex);
                        indices.Add(c - descriptor.firstVertex);
                    }

                    sb.Append("[Vertex Count]\n");
                    sb.Append(descriptor.vertexCount).Append("\n");
                    sb.Append("[Index Count]\n");
                    sb.Append(descriptor.indexCount).Append("\n");

                    for (int vi = 0; vi < descriptor.vertexCount; vi++)
                    {
                        var vertex = vertices[vi];
                        sb.Append("v").Append(" ").Append($"{vertex.x} {vertex.y} {vertex.z}\n");
                    }

                    for (int ti = 0; ti < descriptor.vertexCount; ti++)
                    {
                        var uv = uvs[ti];
                        sb.Append("t").Append(" ").Append($"{uv.x} {(uv.y > 0 ? uv.y : uv.y + 1)}\n");
                    }

                    for (int ni = 0; ni < descriptor.vertexCount; ni++)
                    {
                        var normal = normals[ni];
                        sb.Append("n").Append(" ").Append($"{normal.x} {normal.y} {normal.z}\n");
                    }

                    for (int ii = 0; ii < descriptor.indexCount; ii++)
                    {
                        var index = indices[ii];
                        sb.Append("i").Append(" ").Append($"{index}\n");
                    }

                    System.IO.File.WriteAllText(path.Insert(path.LastIndexOf('.'), $"_{mesh.name}_{di}"), sb.ToString());
                }
            }
        }
    }

}
