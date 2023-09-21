using System;
using System.Collections.Generic;
using System.IO;
using System.Text.RegularExpressions;

public class ContinentID
{
    public const int EasternKingdoms = 0;
    public const int Kalimdor = 1;
    public const int Outland = 530;
    public const int Northrend = 571;
}

public class Graph
{
    private Dictionary<int, List<int>> graph = new Dictionary<int, List<int>>();
    private Dictionary<int, List<int>> nodeHistory = new Dictionary<int, List<int>>();
    private int currStartId = 0;
    private bool targetFound = false;
    private Dictionary<int, HashSet<int>> foundTargets = new Dictionary<int, HashSet<int>>();
    public bool ShouldPrint { get; set; } = false;

    public void AddEdge(int u, int v)
    {
        if (!graph.ContainsKey(u))
        {
            graph[u] = new List<int>();
        }
        graph[u].Add(v);
    }

    private void DFSUtil(int v, HashSet<int> visited, int targetV)
    {
        visited.Add(v);
        if (!nodeHistory.ContainsKey(currStartId))
        {
            nodeHistory[currStartId] = new List<int>();
        }
        if (!nodeHistory[currStartId].Contains(v) && v != currStartId)
        {
            nodeHistory[currStartId].Add(v);
        }

        if (v == targetV)
        {
            if (ShouldPrint)
            {
                Console.WriteLine($"{v} Target found!");
            }
            targetFound = true;
            if (!foundTargets.ContainsKey(targetV))
            {
                foundTargets[targetV] = new HashSet<int>();
            }
            foundTargets[targetV].UnionWith(visited);
            return;
        }
        else if (!targetFound)
        {
            if (ShouldPrint)
            {
                Console.Write($"{v} ");
            }
            foreach (var neighbour in graph.GetValueOrDefault(v, new List<int>()))
            {
                if (!visited.Contains(neighbour))
                {
                    DFSUtil(neighbour, visited, targetV);
                }
            }
        }
    }

    public bool DFS_search(int startId, int targetId)
    {
        if (ShouldPrint)
        {
            Console.WriteLine($"start_id: {startId}, target_id: {targetId}");
        }
        currStartId = startId;
        var visited = new HashSet<int>();

        if (foundTargets.ContainsKey(targetId) && foundTargets[targetId].Contains(startId))
        {
            return true;
        }
        else if (nodeHistory.ContainsKey(startId))
        {
            if (foundTargets.ContainsKey(targetId))
            {
                foreach (var startNode in nodeHistory[startId])
                {
                    if (startNode == targetId || foundTargets[targetId].Contains(startNode))
                    {
                        return true;
                    }
                }
            }
            else
            {
                startId = nodeHistory[startId][nodeHistory[startId].Count - 1];
                if (nodeHistory.ContainsKey(startId))
                {
                    visited.UnionWith(nodeHistory[startId]);
                }
            }
        }

        targetFound = false;
        foreach (var vertex in graph.GetValueOrDefault(startId, new List<int>()))
        {
            if (!visited.Contains(vertex) && !targetFound)
            {
                DFSUtil(vertex, visited, targetId);
            }

            if (targetFound)
            {
                return true;
            }
        }
        return targetFound;
    }
}

public class Program
{
    private static bool TRICKERER_SQL = true;
    private static int continent = ContinentID.Northrend;

    private static List<string> ReadLinesFromFile(string filename)
    {
        return new List<string>(File.ReadAllLines(filename));
    }

    private static bool Contains(string c, string e)
    {
        return c.Contains(e);
    }

    private static string ExtractIndex(string inputStr, char sep, int idx)
    {
        return inputStr.Split(sep)[idx];
    }

    private static readonly List<Tuple<int, int>> isolatedNodes = new List<Tuple<int, int>>
    {
        Tuple.Create(3923, 3936),
        Tuple.Create(3959, 3978),
        Tuple.Create(4087, 4103),
        Tuple.Create(4746, 4789),
        Tuple.Create(4790, 4854)
    };

    private static bool IsIsolatedNodes(int nodeId, int otherNodeId)
    {
        foreach (var nodeRange in isolatedNodes)
        {
            if (nodeId >= nodeRange.Item1 && nodeId <= nodeRange.Item2)
            {
                return !(otherNodeId >= nodeRange.Item1 && otherNodeId <= nodeRange.Item2);
            }
            else if (otherNodeId >= nodeRange.Item1 && otherNodeId <= nodeRange.Item2)
            {
                return !(nodeId >= nodeRange.Item1 && nodeId <= nodeRange.Item2);
            }
        }
        return false;
    }

    public static void Main()
    {
        // ... [rest of the code, similar to the Python version, but translated to C#]
    }
}
