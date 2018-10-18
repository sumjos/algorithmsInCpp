#include "stdafx.h"
#include <vector>
#include "SelfStudyFunctions.h"

int DP::longestIncreasingSubsequence(std::vector<int> list) {
	int lMax = 1;
	std::vector<int> lengthArray(list.size(), 0);
	for (int idx = 0; idx < list.size(); idx++) {
		int maxIdx = idx;
		for (int bidx = idx - 1; bidx >= 0; bidx--) {
			if (list[bidx] < list[idx] && lengthArray[bidx] > lengthArray[maxIdx]) {
				maxIdx = bidx;
			}
		}
		lengthArray[idx] = lengthArray[maxIdx] + 1;
		if (lMax < lengthArray[idx]) {
			lMax = lengthArray[idx];
		}
	}
	return lMax;
}