#include "stdafx.h";
#include <vector>;
#include <iostream>;

void heapifyBottonToTop(std::vector<int>& n, int idx) {
	if (idx != 0 && idx <= n.size()) {
		int parIdx = (idx - 1) / 2;
		if (n[parIdx] > n[idx]) {
			int minIdx = 2 * parIdx + 1;
			if (2 * parIdx + 2 < n.size() && n[minIdx] > n[2 * parIdx + 2]) {
				minIdx = 2 * parIdx + 2;
			}
			int temp = n[parIdx];
			n[parIdx] = n[minIdx];
			n[minIdx] = temp;
			heapifyBottonToTop(n, parIdx);
		}
	}
}

void heapifyTopToBottom(std::vector<int> &v, int idx) {
	if (idx >=0 && idx < v.size()) {
		int minIdx = idx;
		int leftIdx = 2 * idx + 1;
		int rightIdx = 2 * idx + 2;
		if (leftIdx < v.size() && v[leftIdx] < v[minIdx]) {
			minIdx = leftIdx;
		} 
		if (rightIdx < v.size() && v[rightIdx] < v[minIdx]) {
			minIdx = rightIdx;
		}
		if (minIdx != idx) {
			int temp = v[minIdx];
			v[minIdx] = v[idx];
			v[idx] = temp;
			heapifyTopToBottom(v, minIdx);
		}
	}
}

void popTop(std::vector<int>& v) {
	if (v.size() > 0) {
		v[0] = v[v.size() - 1];
		v.pop_back();
		if (v.size() > 0) {
			heapifyTopToBottom(v, 0);
		}
	}
}

void deleteIdx(std::vector<int>& v, int idx) {
	if (idx < v.size()) {
		v[idx] = INT_MIN;
		heapifyBottonToTop(v, idx);
		popTop(v);
	}
}

std::vector<int> createHeap(const std::vector<int> &n) {
	std::vector<int> heap(n.size(), INT_MAX);
	int i = 0;
	for (std::vector<int>::const_iterator it = n.begin(); it != n.end(); it++) {
		heap[i] = *it;
		heapifyBottonToTop(heap, i);
		i++;
	}
	return heap;
}


void printHeap(const std::vector<int> &n) {
	for (std::vector<int>::const_iterator it = n.begin(); it != n.end(); it++) {
		std::cout << *it << "\t";
	}
}

void insertInHeap(std::vector<int> &v, int n) {
	int idx = v.size();
	v.push_back(n);
	heapifyBottonToTop(v, idx);
}

//Sort a neary sorted array, kth sorted array
std::vector<int> sortKsortedArray(std::vector<int>& v, int k) {
	k = k >= v.size() ? v.size() - 1 : k;
	if (k > 0) {
		std::vector<int> firstKPlus1Elements(v.begin(), v.begin() + k + 1);
		std::vector<int> heap = createHeap(firstKPlus1Elements);
		std::vector<int> sorted;
		sorted.reserve(v.size());
		int i = k + 1;
		while (i < v.size()) {
			sorted.push_back(heap[0]);
			popTop(heap);
			insertInHeap(heap, v[i]);
			i++;
		}
		while (heap.size() > 0) {
			sorted.push_back(heap[0]);
			popTop(heap);
		}
		return sorted;
	}
	else
		return v;
}

void testHeapCreation() {
	std::vector<int> v{ 100, 34, 2, 56, 20 };
	printHeap(createHeap(v));
}

void testDeleteIdx() {
	std::vector<int> v{ 100, 34, 2, 56, 20 };
	std::vector<int> heap = createHeap(v);
	std::cout << "Original heap\n"; 
	printHeap(heap);
	deleteIdx(heap, 3);
	std::cout << "\nAfter deleting 3rd idx\n";
	printHeap(heap);
	deleteIdx(heap, 1);
	std::cout << "\nAfter deleting 1st idx\n";
	printHeap(heap);
}

void testsortKsortedArray() {
	std::vector<int> v{ 5, 1, 6, 4, 7};
	std::vector<int> sorted = sortKsortedArray(v, 2);
	std::cout << "Sorted array is\n";
	printHeap(sorted);

}


