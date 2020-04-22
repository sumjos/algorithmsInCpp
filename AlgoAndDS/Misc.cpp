#include "stdafx.h"
#include "Misc.h"
#include <iostream>

bool insertInMinHeap(std::vector<int> &heapArr, int val) {
	heapArr.push_back(val);
	int child = heapArr.size()-1;
	while (child / 2 > 0) {
		int par = child / 2;
		if (heapArr[child] < heapArr[par]) {
			int temp = heapArr[child];
			heapArr[child] = heapArr[par];
			heapArr[par] = temp;
			child = par;
		}
		else {
			break;
		}
	}
	return true;
}

int popFromMinHeap(std::vector<int> &heapArr) {
	if (heapArr.size() > 1) {
		int val = heapArr[1];
		heapArr[1] = heapArr[heapArr.size() - 1];
		heapArr.erase(heapArr.begin() + heapArr.size()-1);
		int par = 1;
		while (2 * par < heapArr.size()) {
			int child = 2 * par;
			child = ((child + 1 < heapArr.size()) && (heapArr[child + 1] < heapArr[child])) ? child + 1 : child;
			if (heapArr[child] < heapArr[par]) {
				int temp = heapArr[par];
				heapArr[par] = heapArr[child];
				heapArr[child] = temp;
				par = child;
			}
			else {
				break;
			}
		}
		return val;
	}
	return -99999;
}

int peekHeap(const std::vector<int> & heap) {
	if (heap.size() > 1) {
		return heap[1];
	}
	else {
		return -99999;
	}
}

void testMinHeap() {
	std::vector<int> ls = { -1 };
	insertInMinHeap(ls, 5);
	std::cout << "Peeking heap... " << peekHeap(ls) << "\n";
	popFromMinHeap(ls);
	std::cout << "Peeking heap... " << peekHeap(ls) << "\n";
	insertInMinHeap(ls, 100);
	std::cout << "Peeking heap... " << peekHeap(ls) << "\n";
	insertInMinHeap(ls, 101);
	std::cout << "Peeking heap... " << peekHeap(ls) << "\n";
	insertInMinHeap(ls, 20);
	std::cout << "Peeking heap... " << peekHeap(ls) << "\n";
	insertInMinHeap(ls, 1);
	std::cout << "Peeking heap... " << peekHeap(ls) << "\n";
	insertInMinHeap(ls, 3);
	std::cout << "Peeking heap... " << peekHeap(ls) << "\n";
	popFromMinHeap(ls);
	std::cout << "Peeking heap... " << peekHeap(ls) << "\n";
	popFromMinHeap(ls);
	std::cout << "Peeking heap... " << peekHeap(ls) << "\n";
	popFromMinHeap(ls);
	std::cout << "Peeking heap... " << peekHeap(ls) << "\n";
}

void printPascal(int rows) {
	int len = rows * (rows + 1) / 2;
	std::vector<int> pascal(len, 0);
	for (int a = 0; a < rows; a++) {
		int start = a * (a + 1) / 2;
		for (int b = 0; b <= a; b++) {
			if (b == 0 || b == a) {
				pascal[start + b] = 1;
			}
			else {
				int prev_start = a*(a - 1) / 2;
				pascal[start + b] = pascal[prev_start + b - 1] + pascal[prev_start + b];
			}
			std::cout << pascal[start + b] << "\t";
		}
		std::cout << "\n";
	}
}