#pragma once
#include<list>
#include<map>
#include<vector>
using namespace std;
class demoClass
{
public:
	int n;
	demoClass();
	void printVal();

};

struct Edge {
	int src;
	int dest;
	int weight;
};

struct Node {
	int src;
	int val;
	int dist;
};

class Graph {
private:
	const int v;
	vector<vector<int>> adj;
	vector<Edge> edgeList;
	vector<vector<int>> weightMatrix;
	void sortEdgeList();
	void traverseBFS(list<int>, vector<bool> &);
	std::vector<int> getCycle(std::vector<int>&, int, int);
public:
	Graph(int);
	bool addEdge(int, int, int weight = 1);
	void BFS(int);
	void testBFS();
	void DFS();
	void testDFS();
	void printRow(int, map<int, bool>&);
	bool isGraphCyclic();
	bool isGraphCyclicFromEdgeList(vector<Edge> &);
	void testIsGraphCyclic();
	void createEdgeListFromAdj();
	vector<Edge> getMinSpanningTree();
	void testGetMinSpanningTree();
	void setGroups(std::vector<int> &, int, int);
	bool _isGraphCyclicDFS(std::vector<bool> &, int, int);
	bool isGraphCyclicDFS();
	void testIsGraphCyclicDFS();
	list<int> findShortestPath(int, int);
	void testFindShortestPath();
	void printACycleInAGraph();
	std::vector<int> getDominantGroup();
	void testGetDominantGroup();
};

//Disjkstra
class Dijkstra {
public:
	const int size;
	std::list<Node>* graph;
	Dijkstra(int size);
	Dijkstra();
	void testDijkstra();
	Node createNode(int, int);
	std::vector<Node> getDefaultMinHeap(int);
	std::list<int> getPath(int, int);
	Node popFromMinHeap(std::vector<Node> &);
	int getMinHeapIdx(std::vector<Node> &, Node);
	void heapifyMinHeap(std::vector<Node> &, int);
	std::list<int> generatePath(std::vector<Node>, int, int, std::vector<int>);
};

class SearchSort {
public:
	SearchSort(std::vector<int>);
	std::vector<int> data;
	int doBinarySearch(int);
	void doQuickSort();
	void doMergeSort();
	void printArray();
private:
	void quickSort(int low, int high);
	void mergeSort(int low, int high);
	int partitionQS(int, int);
};

class DP {
public:
	int longestIncreasingSubsequence(std::vector<int>);
};

class FordFulkerson {
public:
	std::vector<std::vector<int>> graph;
	int size;
	FordFulkerson(int);
	FordFulkerson();
	bool getBFSPath(int, int, std::vector<int>&, std::vector<std::vector<int>>);
	int getMaxFlow(int, int);
	void testGetMaxFlow();
};