#include <bits/stdc++.h>

using namespace std;

// https://www.geeksforgeeks.org/depth-first-search-or-dfs-for-a-graph/

/**
	A graph is a data structure that consists of the following two components: 
	1. A finite set of vertices also called as nodes. 
	2. A finite set of ordered pair of the form (u, v) called as edge.

	The following two are the most commonly used representations of a graph. 
	1. Adjacency Matrix 
	2. Adjacency List 
	There are other representations also like, Incidence Matrix and Incidence List. The
	choice of graph representation is situation-specific. It totally depends on the type
	of operations to be performed and ease of use. 
	Adjacency Matrix: 
	Adjacency Matrix is a 2D array of size V x V where V is the number of vertices in a
	graph.

	Depth First Traversal (or Search) for a graph is similar to Depth First Traversal of a
	tree. The only catch here is, that, unlike trees, graphs may contain cycles (a node
	may be visited twice). To avoid processing a node more than once, use a boolean
	visited array. A graph can have more than one DFS traversal.

	Handling A Disconnected Graph:

    This will happen by handling a corner case. 
	The above code traverses only the vertices reachable from a given source vertex. All
	the vertices may not be reachable from a given vertex, as in a Disconnected graph. To
	do a complete DFS traversal of such graphs, run DFS from all unvisited nodes after a
	DFS. The recursive function remains the same.

	Follow the below steps to solve the problem:

	Create a recursive function that takes the index of the node and a visited array.
    Mark the current node as visited and print the node.
	Traverse all the adjacent and unmarked nodes and call the recursive function with the
	index of the adjacent node.
	Run a loop from 0 to the number of vertices and check if the node is unvisited in the
	previous DFS, then call the recursive function with the current node.

	Time complexity: O(V + E), where V is the number of vertices and E is the number of
	edges in the graph.
	Auxiliary Space: O(V), since an extra visited array of size V is required.
*/

class Graph {

	// A function used by DFS
	void DFSUtil(int v);

public:
	map<int, bool> visited;
	map<int, list<int> > adj;
	// function to add an edge to graph
	void addEdge(int v, int w);

	// prints DFS traversal of the complete graph
	void DFS();
};

void Graph::addEdge(int v, int w)
{
	adj[v].push_back(w); // Add w to v’s list.
}

void Graph::DFSUtil(int v)
{
	// Mark the current node as visited and print it
	visited[v] = true;
	cout << v << " ";

	// Recur for all the vertices adjacent to this vertex
	list<int>::iterator i;
	for (i = adj[v].begin(); i != adj[v].end(); ++i)
		if (!visited[*i])
			DFSUtil(*i);
}

// The function to do DFS traversal. It uses recursive
// DFSUtil()
void Graph::DFS()
{
	// Call the recursive helper function to print DFS
	// traversal starting from all vertices one by one
	for (auto i : adj)
		if (visited[i.first] == false)
			DFSUtil(i.first);
}

// Driver's Code
int main()
{
	// Create a graph given in the above diagram
	Graph g;
	g.addEdge(0, 1);
	g.addEdge(0, 2);
	g.addEdge(1, 2);
	g.addEdge(2, 0);
	g.addEdge(2, 3);
	g.addEdge(3, 3);

	cout << "Following is Depth First Traversal \n";

	// Function call
	g.DFS();

	return 0;
}
