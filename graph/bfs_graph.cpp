#include <bits/stdc++.h>

using namespace std;

// https://www.geeksforgeeks.org/breadth-first-search-or-bfs-for-a-graph/

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

	The breadth-first search (BFS) algorithm is used to search a tree or graph data
	structure for a node that meets a set of criteria. It starts at the tree’s root or
	graph and searches/visits all nodes at the current depth level before moving on to the
	nodes at the next depth level. Breadth-first search can be used to solve many problems
	in graph theory.

	Breadth-First Traversal (or Search) for a graph is similar to the Breadth-First
	Traversal of a tree (See method 2 of this post). 

	The only catch here is, that, unlike trees, graphs may contain cycles, so we may come
	to the same node again. To avoid processing a node more than once, we divide the
	vertices into two categories:
    Visited and
    Not visited.

	A boolean visited array is used to mark the visited vertices. For simplicity, it is
	assumed that all vertices are reachable from the starting vertex. BFS uses a queue
	data structure for traversal.

	Follow the below method to implement BFS traversal:
    Declare a queue and insert the starting vertex.
    Initialize a visited array and mark the starting vertex as visited.
    Follow the below process till the queue becomes empty:
        Remove the first vertex of the queue.
        Mark that vertex as visited.
        Insert all the unvisited neighbors of the vertex into the queue.

	The implementation uses an adjacency list representation of graphs. STL‘s list
	container stores lists of adjacent nodes and the queue of nodes needed for BFS
	traversal.
*/

// This class represents a directed graph using
// adjacency list representation
class Graph {
	int V; // No. of vertices

	// Pointer to an array containing adjacency
	// lists
	vector<list<int> > adj;

public:
	Graph(int V); // Constructor

	// function to add an edge to graph
	void addEdge(int v, int w);

	// prints BFS traversal from a given source s
	void BFS(int s);
};

Graph::Graph(int V)
{
	this->V = V;
	adj.resize(V);
}

void Graph::addEdge(int v, int w)
{
	adj[v].push_back(w); // Add w to v’s list.
}

void Graph::BFS(int s)
{
	// Mark all the vertices as not visited
	vector<bool> visited;
	visited.resize(V, false);

	// Create a queue for BFS
	list<int> queue;

	// Mark the current node as visited and enqueue it
	visited[s] = true;
	queue.push_back(s);

	while (!queue.empty()) {
		// Dequeue a vertex from queue and print it
		s = queue.front();
		cout << s << " ";
		queue.pop_front();

		// Get all adjacent vertices of the dequeued
		// vertex s. If a adjacent has not been visited,
		// then mark it visited and enqueue it
		for (auto adjacent : adj[s]) {
			if (!visited[adjacent]) {
				visited[adjacent] = true;
				queue.push_back(adjacent);
			}
		}
	}
}

// Driver program to test methods of graph class
int main()
{
	// Create a graph given in the above diagram
	Graph g(4);
	g.addEdge(0, 1);
	g.addEdge(0, 2);
	g.addEdge(1, 2);
	g.addEdge(2, 0);
	g.addEdge(2, 3);
	g.addEdge(3, 3);

	cout << "Breadth First Traversal " << "(starting from vertex 2) \n";
	g.BFS(2);

	return 0;
}
