#include "stdafx.h"
#include "iostream"
#include "SelfStudyFunctions.h"
#include "list"
#include <limits>
#include <map>
#include <limits>
#include <string>
using namespace std;

Dijkstra::Dijkstra(int s): size(s){
	this->graph = new std::list<Node>[s];
}

Dijkstra::Dijkstra(): size(0){}

Node Dijkstra::createNode(int val, int weight) {
	Node n;
	n.val = val;
	n.dist = weight;
	return n;
}

std::list<int> Dijkstra::getPath(int start, int end) {
	std::vector<Node> minHeap = getDefaultMinHeap(start);
	std::vector<Node> nodesCovered;
	std::vector<bool> nodesCoveredBool(this->size, false);
	std::vector<int> posArray(this->size, -1);
	bool endPosFound = false; int pos = -1;
	while (nodesCovered.size() < this->size) {
		Node n = popFromMinHeap(minHeap);
		nodesCovered.push_back(n);
		posArray[n.val] = ++pos;
		nodesCoveredBool[n.val] = true;
		for (std::list<Node>::iterator itr = this->graph[n.val].begin(); itr != this->graph[n.val].end(); itr++) {
			Node adc = *itr;
			if (!nodesCoveredBool[adc.val]) {
				int minHeapIdx = getMinHeapIdx(minHeap, adc);
				if (adc.dist + n.dist < minHeap[minHeapIdx].dist) {
					minHeap[minHeapIdx].dist = adc.dist + n.dist;
					minHeap[minHeapIdx].src = n.val;
					heapifyMinHeap(minHeap, minHeapIdx);
				}
			}
		}
	}

	return generatePath(nodesCovered, end, start, posArray);
}

std::list<int> Dijkstra::generatePath(std::vector<Node> nodes, int end, int start, std::vector<int> posArray) {
	std::list<int> path = { end };
	Node n = nodes[posArray[end]];
	while (n.src != start) {
		path.push_front(n.src);
		n = nodes[posArray[n.src]];
	}
	path.push_front(start);
	return path;
}

int Dijkstra::getMinHeapIdx(std::vector<Node> &heap, Node searchedNode) {
	//update with better logic
	int count = 1;
	for (std::vector<Node>::iterator itr = heap.begin()+1; itr != heap.end(); itr++) {
		if ((*itr).val == searchedNode.val) {
			return count;
		}
		count++;
	}
	return -999;
}

//Asumming Node value is updated with lesser value
void Dijkstra::heapifyMinHeap(std::vector<Node> &heap, int idx) {
	int child = idx;
	int par = child / 2;
	while (par > 0) {
		if (heap[par].dist > heap[child].dist) {
			Node t = heap[par];
			heap[par] = heap[child];
			heap[child] = t;
			child = par;
			par = child / 2;
		}
		else {
			break;
		}
	}
}

Node Dijkstra::popFromMinHeap(std::vector<Node> &heap) {
	Node n;
	if(heap.size() > 1) {
		n = heap[1];
		heap[1] = heap[heap.size() - 1];
		heap.erase(heap.begin() + heap.size()-1);
		int par = 1;
		int child = 2 * par;
		while (child < heap.size()) {
			child = ((child + 1 < heap.size()) && (heap[child + 1].dist < heap[child].dist)) ? child + 1 : child;
			if (heap[child].dist < heap[par].dist) {
				Node t = heap[child];
				heap[child] = heap[par];
				heap[par] = t;
				par = child;
				child = 2 * par;
			}
			else {
				break;
			}
		}
	}
	return n;
}

std::vector<Node> Dijkstra::getDefaultMinHeap(int start) {
	std::vector<Node> heap = { createNode(-999, -999)};
	heap.push_back(createNode(start, 0));
	for (int idx = 0; idx < this->size; idx++) {
		if (idx != start) {
			heap.push_back(createNode(idx, std::numeric_limits<int>::max()));
		}
	}
	heap[start].dist = 0;
	heap[start].src = start;
	heapifyMinHeap(heap, start+1);
	return heap;
}

void Dijkstra::testDijkstra() {
	Dijkstra dj(6);
	dj.graph[0].push_back(createNode(1, 1));
	dj.graph[0].push_back(createNode(5, 6));
	dj.graph[1].push_back(createNode(0, 1));
	dj.graph[1].push_back(createNode(2, 2));
	dj.graph[2].push_back(createNode(1, 2));
	dj.graph[2].push_back(createNode(3, 3));
	dj.graph[3].push_back(createNode(2, 3));
	dj.graph[3].push_back(createNode(4, 4));
	dj.graph[4].push_back(createNode(3, 4));
	dj.graph[4].push_back(createNode(5, 5));
	dj.graph[5].push_back(createNode(0, 6));
	dj.graph[5].push_back(createNode(4,5));
	std::list<int> path = dj.getPath(2,5);
	for (std::list<int>::iterator itr = path.begin(); itr != path.end(); itr++) {
		cout << *itr <<"\n";
	}
}