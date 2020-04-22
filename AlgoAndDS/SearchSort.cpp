#include "stdafx.h"
#include "SelfStudyFunctions.h"
#include <iostream>

SearchSort::SearchSort(std::vector<int> d) {
	this->data = d;
}

int SearchSort::doBinarySearch(int val) {
	int foundIdx = -1;
	int start = 0, end = this->data.size()-1, mid = -1, intmd;
	do {
		mid = (start + end) / 2;
		intmd = this->data[mid];
		if (intmd == val) {
			return mid;
		}
		else if (intmd > val) {
			end = mid - 1;
		}
		else {
			start = mid + 1;
		}
	} while (end >= start);
	return foundIdx;
}

void SearchSort::doQuickSort() {
	this->quickSort(0, this->data.size()-1);
}

void SearchSort::quickSort(int low, int high) {
	if (high >= low) {
		int ptnIdx = partitionQS(low, high);
		quickSort(low, ptnIdx - 1);
		quickSort(ptnIdx+1, high);
	}
}

int SearchSort::partitionQS(int low, int high) {
	int ptnValue = this->data[high];
	int ptnIdx = low;
	for (int idx = low; idx < high; idx++) {
		if (this->data[idx] < ptnValue) {
			int temp = this->data[ptnIdx];
			this->data[ptnIdx] = this->data[idx];
			this->data[idx] = temp;
			ptnIdx++;
		}
	}
	int temp = this->data[ptnIdx];
	this->data[ptnIdx] = ptnValue;
	this->data[high] = temp;
	return ptnIdx;
}

void SearchSort::doMergeSort() {
	this->mergeSort(0, this->data.size() - 1);
}

void SearchSort::mergeSort(int low, int high) {
	if (high > low) {
		int mid = (high + low) / 2;
		mergeSort(low, mid);
		mergeSort(mid + 1, high);
		std::vector<int> left(this->data.begin() + low, this->data.begin() + mid + 1);
		std::vector<int> right(this->data.begin() + mid + 1, this->data.begin() + high + 1);
		int lidx = 0, ridx = 0, idx = low;
		while (lidx < left.size() && ridx < right.size()) {
			if (left[lidx] <= right[ridx]) {
				this->data[idx] = left[lidx];
				lidx++;
			}
			else {
				this->data[idx] = right[ridx];
				ridx++;
			}
			idx++;
		}
		while (ridx < right.size()) {
			this->data[idx] = right[ridx];
			ridx++;
			idx++;
		}
		while (lidx < left.size()) {
			this->data[idx] = left[lidx];
			lidx++;
			idx++;
		}
	}
}

void SearchSort::printArray() {
	for (int a : this->data) {
		std::cout << a << "\n";
	}
}