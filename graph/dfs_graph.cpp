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

	Advantages of Depth First Search:

	Memory requirement is only linear with respect to the search graph. This is in
	contrast with breadth-first search which requires more space. The reason is that the
	algorithm only needs to store a stack of nodes on the path from the root to the
	current node.
	The time complexity of a depth-first Search to depth d is O(bd) since it generates the
	same set of nodes as breadth-first search, but simply in a different order. Thus
	practically depth-first search is time-limited rather than space-limited.
	If depth-first search finds solution without exploring much in a path then the time
	and space it takes will be very less.
	DFS requires less memory since only the nodes on the current path are stored. By
	chance DFS may find a solution without examining much of the search space at all.

	Disadvantages of Depth First Search:
	The disadvantage of Depth-First Search is that there is a possibility that it may down
	the left-most path forever. Even a finite graph can generate an infinite tre One
	solution to this problem is to impose a cutoff depth on the search. Although ideal
	cutoff is the solution depth d and this value is rarely known in advance of actually
	solving the problem. If the chosen cutoff depth is less than d, the algorithm will
	fail to find a solution, whereas if the cutoff depth is greater than d, a large price
	is paid in execution time, and the first solution found may not be an optimal one.
	Depth-First Search is not guaranteed to find the solution.
	And there is no guarantee to find a minimal solution, if more than one solution.

	Time complexity: O(V + E), where V is the number of vertices and E is the number of
	edges in the graph.
	Auxiliary Space: O(V), since an extra visited array of size V is required.
*/

// Graph class represents a directed graph
// using adjacency list representation
class Graph {
public:
	map<int, bool> visited;
	map<int, list<int> > adj;

	// function to add an edge to graph
	void addEdge(int v, int w);

	// DFS traversal of the vertices
	// reachable from v
	void DFS(int v);
};

void Graph::addEdge(int v, int w)
{
	adj[v].push_back(w); // Add w to v’s list.
}

void Graph::DFS(int v)
{
	// Mark the current node as visited and
	// print it
	visited[v] = true;
	cout << v << " ";

	// Recur for all the vertices adjacent
	// to this vertex
	list<int>::iterator i;
	for (i = adj[v].begin(); i != adj[v].end(); ++i)
		if (!visited[*i])
			DFS(*i);
}

// Driver's code
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

	cout << "Depth First Traversal (starting from vertex 2) \n";

	// Function call
	g.DFS(2);

	return 0;
}
