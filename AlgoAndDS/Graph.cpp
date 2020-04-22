#include "stdafx.h"
#include "SelfStudyFunctions.h"
#include <iostream>
#include <map>
#include<unordered_map>;
#include <vector>
#include <limits>
Graph::Graph(int size):v(size) {
	this->adj.resize(size, {});
	this->weightMatrix.resize(size);
	for (int i = 0; i < size; i++) {
		this->weightMatrix[i].resize(size);
		for (int j = 0; j < size; j++) {
			this->weightMatrix[i][j] = std::numeric_limits<int>::max();
		};
	}
}

bool Graph::addEdge(int u, int v, int weight) {
	if (u <= this->v && v <= this->v) {
		this->adj[u].push_back(v);
		this->adj[v].push_back(u);
		this->weightMatrix[u][v] = weight;
		this->weightMatrix[v][u] = weight;
		return true;
	}
	else {
		return false;
	}
}

void Graph::createEdgeListFromAdj() {
	bool *edgeCovered = (bool*)malloc(sizeof(bool)*this->v*this->v);
	for (int i = 0; i < this->v; i++) {
		for (int j = 0; j < this->v; j++) {
			edgeCovered[i*this->v + j] = false;
		}
	}
	for (int idx = 0; idx < this->v; idx++) {
		for (std::vector<int>::iterator itr = this->adj[idx].begin(); itr != this->adj[idx].end(); itr++) {
			if (!edgeCovered[idx*this->v + *itr - 1] && !edgeCovered[idx + (*itr - 1)*this->v]) {
				struct Edge e;
				e.src = idx;
				e.dest = *itr - 1;
				e.weight = this->weightMatrix[idx][*itr - 1];
				this->edgeList.push_back(e);
				edgeCovered[idx*this->v + *itr - 1] = true;
				edgeCovered[idx + (*itr - 1)*this->v] = true;
			}
		}
	}
}

//void Graph::BFS(int start) {
//	std::map<int, bool>::iterator it;
//	map<int, bool>visited;
//	for (int idx = 0; idx < this->v; idx++) {
//		it = visited.find(idx+1);
//		if (it == visited.end()) {
//			std::cout << idx+1 << ", ";
//			visited[idx+1] = true;
//		}
//		for (std::list<int>::iterator itr = this->adj[idx].begin(); itr != this->adj[idx].end(); itr++) {
//			it = visited.find(*itr);
//			if (it == visited.end()) {
//				std::cout << *itr << ", ";
//				visited[*itr] = true;
//			}
//		}
//	}
//}
void Graph::BFS(int start) {
	std::list<int> list = {start};
	std::vector<bool> visited(this->v, false);
	this->traverseBFS(list, visited);
}

void Graph::traverseBFS(std::list<int> parents, std::vector<bool> &visited) {
	if (parents.size() > 0) {
		std::list<int> child;
		for (std::list<int>::iterator parItr = parents.begin(); parItr != parents.end(); parItr++) {
			if (!visited[*parItr - 1]) {
				std::cout << *parItr << ",";
				visited[*parItr - 1] = true;
				child.insert(child.end(), this->adj[*parItr-1].begin(), this->adj[*parItr - 1].end());
			}
		}
		this->traverseBFS(child, visited);
	}
}


void Graph::DFS() {
	std::map<int, bool>::iterator it;
	map<int, bool>visited;
	for (int idx = 0; idx < this->v; idx++) {
		it = visited.find(idx + 1);
		if (it == visited.end()) {
			std::cout << idx + 1 << ", ";
			visited[idx + 1] = true;
			printRow(idx, visited);
		}
	}
}


bool Graph::isGraphCyclic() {
	std::vector<int> groups(this->v, -1);
	std::vector<bool> edgeCovered(this->v*this->v, false);
	for (int i= 0; i < this->v; i++) {
		edgeCovered[i*this->v + i] = true;
		if (groups[i] == -1) {
			groups[i] = i;
		}
		for (std::vector<int>::iterator itr = this->adj[i].begin(); itr != this->adj[i].end(); itr++) {
			int connIdx = *itr - 1;
			if (!edgeCovered[i*this->v + connIdx]) {
				edgeCovered[i*this->v + connIdx] = true;
				edgeCovered[i + this->v*connIdx] = true;
				if (groups[connIdx] == -1) {
					int grpIdx = groups[i]; // grp index logic: take smaller idx to be grp indx
					groups[connIdx] = grpIdx;
				}
				else if (groups[connIdx] == groups[i]) {
					return true;
				}
				else {
					int grpIdx = (groups[i] < groups[connIdx]) ? groups[i] : groups[connIdx];
					int repGrpIdx = (grpIdx != groups[i]) ? groups[i] : groups[connIdx];
					groups[i] = grpIdx;
					groups[connIdx] = grpIdx;
					this->setGroups(groups, repGrpIdx, grpIdx);
				}
			}
		}
	}
	return false;
}

void Graph::setGroups(std::vector<int> &groups, int oldGrp, int newGrp) {
	for (std::vector<int>::iterator itr = groups.begin(); itr != groups.end(); itr++) {
		*itr = (*itr == oldGrp) ? newGrp : *itr;
	}
}

vector<Edge> Graph::getMinSpanningTree() {
	this->createEdgeListFromAdj();
	this->sortEdgeList();
	std::vector<Edge> treeEdges;
	treeEdges.reserve(this->edgeList.size());
	for (std::vector<Edge>::iterator itr = this->edgeList.begin(); itr != this->edgeList.end(); itr++) {
		treeEdges.push_back(*itr);
		if (this->isGraphCyclicFromEdgeList(treeEdges)) {
			treeEdges.pop_back();
		}
		if (treeEdges.size() == this->v - 1) {
			break;
		}
	}
	return treeEdges;
}

void Graph::sortEdgeList() {
	//Simple bubble sort
	for (int i = 0; i < this->edgeList.size(); i++) {
		for (int j = 0; j < this->edgeList.size() - 1; j++) {
			if (this->edgeList[j].weight > this->edgeList[j + 1].weight) {
				Edge e = this->edgeList[j];
				this->edgeList[j] = this->edgeList[j + 1];
				this->edgeList[j + 1] = e;
			}
		}
	}
}

bool Graph::isGraphCyclicFromEdgeList(vector<Edge> &edgeList) {
	std::vector<int> vGroups(this->v, -1);
	for (int in = 0; in < this->v; in++) {
		vGroups[in] = in;
	}
	for (std::vector<Edge>::iterator itr = edgeList.begin(); itr != edgeList.end(); itr++) {
		int grp = vGroups[(*itr).src] < vGroups[(*itr).dest] ? vGroups[(*itr).src] : vGroups[(*itr).dest];
		if (vGroups[(*itr).src] == -1 && vGroups[(*itr).dest] == -1) {
			//Take group be the lower index
			vGroups[(*itr).src] = grp;
			vGroups[(*itr).dest] = grp;
		}
		else if (vGroups[(*itr).src] != -1 && vGroups[(*itr).dest] != -1 && vGroups[(*itr).src] == vGroups[(*itr).dest]) {
			return true;
		}
		else {
			int toReplaceGroup = (grp == vGroups[(*itr).src]) ? vGroups[(*itr).dest] : vGroups[(*itr).src];
			vGroups[(*itr).src] = grp;
			vGroups[(*itr).dest] = grp;
			for (std::vector<int>::iterator i = vGroups.begin(); i != vGroups.end(); i++) {
				*i = (*i == toReplaceGroup) ? grp : *i;
			}
		}
	}
	return false;
}

void Graph::printRow(int idx, map<int, bool>& visited) {
	std::map<int, bool>::iterator it;
	for(std::vector<int>::iterator itr = this->adj[idx].begin(); itr != this->adj[idx].end(); itr++) {
		it = visited.find(*itr);
		if (it == visited.end()) {
			std::cout << *itr << ", ";
			visited[*itr] = true;
			printRow(*itr - 1, visited);
		}
	}
}

void Graph::printACycleInAGraph() {
	vector<int> group(this->v, -1);
	for (int i = 0; i < this->v; i++) {
		group[i] = i;
	}
	vector<int> cycle;
	for (int i = 0; i < this->v; i++) {
		if (group[i] == i) {
			cycle = getCycle(group, i, i);
			if (cycle.size() > 0) {
				break;
			}
		}
	}
	if (cycle.size() == 0) {
		std::cout << "No Cycle Found\n";
	}
	else {
		std::cout << "Cycle Found \n";
		for(std::vector<int>::iterator itr = cycle.begin(); itr != cycle.end(); itr++) {
			std::cout << *itr << " -> ";
		}
	}
}

std::vector<int> Graph::getCycle(std::vector<int>& group, int startidx, int par) {
	for (std::vector<int>::iterator itr = adj[startidx].begin(); itr != adj[startidx].end(); itr++) {
		if (par != *itr) {
			if (group[*itr] == group[startidx]) {
				return { startidx };
			}
			else {
				group[*itr] = group[startidx];
				std::vector<int> v = getCycle(group, *itr, startidx);
				if (v.size() > 0) {
					v.push_back(startidx);
					return v;
				}
			}
		}
	}
	return {};
}
void Graph::testBFS() {
	std::cout << "Testing graph BFS \n";
	Graph g(4);
	if (g.addEdge(1, 3)) {
		std::cout << "Added 1-3 edge\n";
	}
	if (g.addEdge(3, 4)) {
		std::cout << "Added 3-4 edge\n";
	}
	if (g.addEdge(1, 4)) {
		std::cout << "Added 1-4 edge\n";
	}
	if (g.addEdge(2, 4)) {
		std::cout << "Added 2-4 edge\n";
	}
	//output: 1,3,2,4
	g.BFS(3);
}

void Graph::testIsGraphCyclic() {
	std::cout << "Testing if graph cyclic \n";
	Graph g(5);

	if (g.addEdge(1, 2)) {
		std::cout << "Added 1-2 edge\n";
	}
	if (g.addEdge(2, 4)) {
		std::cout << "Added 2-4 edge\n";
	}
	if (g.addEdge(4, 3)) {
		std::cout << "Added 4-3 edge\n";
	}
	if (g.addEdge(2, 3)) {
		std::cout << "Added 1-5 edge\n";
	}
	if (g.addEdge(3, 4)) {
		std::cout << "Added 3-4 edge\n";
	}
	//if (g.addEdge(2, 5)) {
	//	std::cout << "Added 2-5 edge\n";
	//}
	//output: true
	//std::cout << g.isGraphCyclic()<< "\n";
	g.printACycleInAGraph();
}

void Graph::testIsGraphCyclicDFS() {
	std::cout << "Testing if graph cyclic \n";
	Graph g(6);

	if (g.addEdge(1, 2)) {
		std::cout << "Added 1-2 edge\n";
	}
	//if (g.addEdge(2, 4)) {
	//	std::cout << "Added 2-4 edge\n";
	//}
	if (g.addEdge(4, 3)) {
		std::cout << "Added 4-3 edge\n";
	}
	//if (g.addEdge(4, 6)) {
	//	std::cout << "Added 4-6 edge\n";
	//}
	if (g.addEdge(3, 6)) {
		std::cout << "Added 3-6 edge\n";
	}
	if (g.addEdge(1, 5)) {
		std::cout << "Added 1-5 edge\n";
	}
	//if (g.addEdge(2, 5)) {
	//	std::cout << "Added 2-5 edge\n";
	//}
	//output: true
	std::cout << g.isGraphCyclicDFS() << "\n";
}

void Graph::testGetMinSpanningTree() {
	std::cout << "Testing if graph cyclic \n";
	Graph g(7);

	if (g.addEdge(1, 2, 1)) {
		std::cout << "Added 1-2 edge\n";
	}
	if (g.addEdge(1, 3, 3)) {
		std::cout << "Added 1-3 edge\n";
	}
	if (g.addEdge(2, 7, 1)) {
		std::cout << "Added 1-2 edge\n";
	}
	if (g.addEdge(3, 4, 2)) {
		std::cout << "Added 3-4 edge\n";
	}
	if (g.addEdge(3, 5, 3)) {
		std::cout << "Added 3-5 edge\n";
	}
	if (g.addEdge(5, 6, 5)) {
		std::cout << "Added 5-6 edge\n";
	}
	if (g.addEdge(6, 7, 100)) {
		std::cout << "Added 6-7 edge\n";
	}
	std::vector<Edge>edges = g.getMinSpanningTree();
	for (int i = 0; i < edges.size(); i++) {
		cout << edges[i].src+1 << "<->" << edges[i].dest+1 << " with weight " << edges[i].weight<<"\n";
	}
}

void Graph::testDFS() {
	std::cout << "Testing graph BFS \n";
	Graph g(4);
	if (g.addEdge(1, 3)) {
		std::cout << "Added 1-3 edge\n";
	}
	if (g.addEdge(3, 4)) {
		std::cout << "Added 2-4 edge\n";
	}
	//output: 1,3,4,2
	g.DFS();
}

bool Graph::_isGraphCyclicDFS(std::vector<bool> &visited, int start, int parent) {
	if(visited[start-1]) {
		return true;
	}
	else {
		visited[start - 1] = true;
		for (std::vector<int>::iterator itr = this->adj[start-1].begin(); itr != this->adj[start-1].end(); itr++) {
			if (*itr != parent) {
				bool cyclic = _isGraphCyclicDFS(visited, *itr, start);
				if (cyclic) {
					return true;
				}
			}
		}
		return false;
	}
}

bool Graph::isGraphCyclicDFS() {
	std::vector<bool> visited(this->v, false);
	for (int i = 0; i < this->v; i++) {
		if (!visited[i]) {
			bool c = _isGraphCyclicDFS(visited, i + 1, i + 1);
			if (c) {
				return true;
			}
		}
	}
	return false;
}

std::list<int> Graph::findShortestPath(int start, int end) {
	std::vector<int> parents(this->v, -1);
	std::vector<bool> visited(this->v, false);
	std::list<int> queue = {start};
	parents[start - 1] = start;
	bool pathFound = false;
	while(queue.size() > 0 && !pathFound) {
		int node = queue.front();
		queue.pop_front();
		visited[node - 1] = true;
		for (std::vector<int>::iterator itr = this->adj[node - 1].begin(); itr != adj[node - 1].end(); itr++) {
			if (!visited[*itr-1]) {
				parents[*itr - 1] = node;
				if (*itr == end) {
					pathFound = true;
					break;
				}
				queue.push_back(*itr);
			}
		}
	}
	if (pathFound) {
		int par = -1; int child = end;
		std::list<int> path = { child };
		while (par != start) {
			par = parents[child - 1];
			path.push_front(par);
			child = par;
		}
		return path;
	}
	else {
		return {};
	}
}

void Graph::testFindShortestPath() {
	Graph g(7);

	if (g.addEdge(1, 2)) {
		std::cout << "Added 1-2 edge\n";
	}
	if (g.addEdge(2, 5)) {
		std::cout << "Added 2-5 edge\n";
	}
	if (g.addEdge(1, 3)) {
		std::cout << "Added 1-3 edge\n";
	}
	if (g.addEdge(3, 4)) {
		std::cout << "Added 3-4 edge\n";
	}
	if (g.addEdge(4, 6)) {
		std::cout << "Added 4-6 edge\n";
	}
	if (g.addEdge(6, 7)) {
		std::cout << "Added 6-7 edge\n";
	}
	if (g.addEdge(7, 5)) {
		std::cout << "Added 7-5 edge\n";
	}
	
	std::list<int> path = g.findShortestPath(1,6);
	for (std::list<int>::iterator itr = path.begin(); itr != path.end(); itr++) {
		std::cout << *itr << ",";
	}
}

std::vector<int> Graph::getDominantGroup() {
	std::vector<bool> visited(this->v, false);
	std::vector<int> dominant;
	std::unordered_map<int, int> order;
	for (int i = 0; i < this->v; i++) {
		order[i] = this->adj[i].size();
	}
	while (order.size() > 0) {
		int count = -1; int maxIdx = -1;
		for (std::unordered_map<int, int>::iterator itr = order.begin(); itr != order.end(); itr++) {
			if (itr->second > count) {
				count = itr->second;
				maxIdx = itr->first;
			}
			else if (itr->second == count && count !=0) {
				int c1 = 0, c2 = 0;
				for (int i = 0; i < this->adj[maxIdx].size(); i++) {
					if (!visited[adj[maxIdx][i]]) {
						c1++;
					}
				}
				for (int i = 0; i < this->adj[itr->first].size(); i++) {
					if (!visited[adj[itr->first][i]]) {
						c2++;
					}
				}
				if (c2 > c1) {
					maxIdx = itr->first;
				}
			}
		}
		dominant.push_back(maxIdx);
		visited[maxIdx] = true;
		order.erase(maxIdx);
		for (int i = 0; i < this->adj[maxIdx].size(); i++) {
			visited[adj[maxIdx][i]] = true;
			order.erase(adj[maxIdx][i]);
		}
	}
	return dominant;
}

void Graph::testGetDominantGroup() {
	Graph g(8);

	if (g.addEdge(0, 1)) {
		std::cout << "Added 0-1 edge\n";
	}if (g.addEdge(0, 6)) {
		std::cout << "Added 0-6 edge\n";
	}if (g.addEdge(0, 7)) {
		std::cout << "Added 0-7 edge\n";
	}if (g.addEdge(1, 7)) {
		std::cout << "Added 1-7 edge\n";
	}if (g.addEdge(1, 2)) {
		std::cout << "Added 1-2 edge\n";
	}if (g.addEdge(2, 7)) {
		std::cout << "Added 2-7 edge\n";
	}if (g.addEdge(2, 3)) {
		std::cout << "Added 2-3 edge\n";
	}if (g.addEdge(3, 7)) {
		std::cout << "Added 3-7 edge\n";
	}if (g.addEdge(3, 4)) {
		std::cout << "Added 3-4 edge\n";
	}if (g.addEdge(4, 5)) {
		std::cout << "Added 4-5 edge\n";
	}if (g.addEdge(5, 6)) {
		std::cout << "Added 5-6 edge\n";
	}
	std::vector<int> v = g.getDominantGroup();
	std::cout << "Dominant group is \t";
	for (std::vector<int>::iterator itr = v.begin(); itr != v.end(); itr++) {
		cout << *itr <<" , ";
	}
}