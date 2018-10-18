#include "stdafx.h"
#include <iostream>
#include "MyFunctions.h"
#include "SelfStudyFunctions.h"
#include "vector"
#include "Misc.h"

int main() {

	//Coursera
	//w1p2();

	//Self study
	//Graph gp(1);
	//gp.testIsGraphCyclic();
	//gp.testGetMinSpanningTree();
	//gp.testFindShortestPath();
	//testMinHeap();
	FordFulkerson ff;
	ff.testGetMaxFlow();
	//Hold off
	std::cin.clear();
	std::cin.ignore(32767, '\n');
	std::cin.get();
	return 0;
}