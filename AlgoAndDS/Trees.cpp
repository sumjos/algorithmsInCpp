#include "stdafx.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

struct TreeNode {
	struct TreeNode* Left;
	struct TreeNode* Right;
	int val;
	TreeNode(int data) {
		this->Left = NULL;
		this->Right = NULL;
		this->val = data;
	}
};

struct Info {
	int sumTree;
	bool isBST;
};

struct InfoBalancedTree {
	bool isBalanced;
	int height;
};

// Find maximum sum of a valid sub BST in a given tree
Info findMaxSumOfSubBST(TreeNode* root) {
	if (root == NULL) {
		return {0, true};
	}
	else if (root->Left == NULL && root->Right == NULL) {
		return {root->val, true};
	}
	else {
		Info leftInfo = findMaxSumOfSubBST(root->Left);
		Info rightInfo = findMaxSumOfSubBST(root->Right);
		Info finalInfo = {0, true};
		if (leftInfo.isBST && rightInfo.isBST && (root->Left == NULL || root->val > root->Left->val) && 
			(root->Right == NULL || root->val < root->Right->val)) {
			finalInfo.sumTree = leftInfo.sumTree + root->val + rightInfo.sumTree;
		} 
		else {
			finalInfo.sumTree = std::max(leftInfo.sumTree, rightInfo.sumTree);
			finalInfo.isBST = false;
		}
		return finalInfo;
	}
}

InfoBalancedTree isTreeBalanced(TreeNode* tree) {
	if (tree == NULL) {
		return {true, 0};
	}
	else {
		InfoBalancedTree leftSubTreeInfo = isTreeBalanced(tree->Left);
		InfoBalancedTree rightSubTreeInfo = isTreeBalanced(tree->Right);
		bool isBalanced = leftSubTreeInfo.isBalanced && rightSubTreeInfo.isBalanced &&
			abs(leftSubTreeInfo.height - rightSubTreeInfo.height) <= 1;
		int height = (leftSubTreeInfo.height > rightSubTreeInfo.height) ? leftSubTreeInfo.height : rightSubTreeInfo.height;
		return { isBalanced , 1 + height};
	}
}

void printInOrderTree(TreeNode* t) {
	if (t != NULL) {
		printInOrderTree(t->Left);
		std::cout << t->val << "\t";
		printInOrderTree(t->Right);
	}
}

TreeNode* popFirstInorderLeaf(TreeNode* t, TreeNode* parent) {
	if (t->Left == NULL) {
		parent->Left = t->Right;
		t->Right = NULL;
		return t;
	}
	else {
		return popFirstInorderLeaf(t->Left, t);
	}
}

TreeNode* deleteNodeInBST(TreeNode* t, int val) {
	if (t != NULL) {
		if (val < t->val) {
			t->Left = deleteNodeInBST(t->Left, val);
			return t;
		}
		else if (val > t->val) {
			t->Right = deleteNodeInBST(t->Right, val);
			return t;
		}
		else {
			if (t->Left == NULL) {
				return t->Right;
			}
			else if (t->Right == NULL) {
				return t->Left;
			}
			else {
				TreeNode* temp = popFirstInorderLeaf(t->Right, t->Right);
				temp->Left = t->Left;
				if (temp != t->Right) {
					temp->Right = t->Right;
				}
				return temp;
			}
		}
	}
	else {
		return NULL;
	}
}

void getVectorFromArray(TreeNode* n, std::vector<int>& arr) {
	if (n != NULL) {
		getVectorFromArray(n->Left, arr);
		arr.push_back(n->val);
		getVectorFromArray(n->Right, arr);
	}
}

std::vector<int> convertBSTToVector(TreeNode* n) {
	std::vector<int> arr;
	arr.reserve(20);
	getVectorFromArray(n, arr);
	arr.shrink_to_fit();
	return arr;
}

int findMaxTreeWidth(TreeNode* t) {
	if (t != NULL) {
		std::queue<TreeNode*> q;
		q.push(t);
		int max = q.size();
		while (!q.empty()) {
			int count = q.size();
			while (count > 0) {
				TreeNode* temp = q.front();
				q.pop();
				count--;
				if (temp->Left != NULL) {
					q.push(temp->Left);
				}
				if (temp->Right != NULL) {
					q.push(temp->Right);
				}
			}
			if (max < q.size()) {
				max = q.size();
			}
		}
		return max;
	}
	else {
		return 0;
	}
}

void testfindMaxSumOfSubBST() {
	struct TreeNode* root = new TreeNode(5);
	root->Left = new TreeNode(14);
	root->Right = new TreeNode(3);
	root->Left->Left = new TreeNode(6);
	root->Right->Right = new TreeNode(7);
	root->Left->Left->Left = new TreeNode(9);
	root->Left->Left->Right = new TreeNode(1);
	std::cout << "\nMaximum sum of a Sub BST is " << findMaxSumOfSubBST(root).sumTree;
}

void testisTreeBalanced() {
	struct TreeNode* root = new TreeNode(5);
	root->Left = new TreeNode(14);
	root->Right = new TreeNode(3);
	root->Left->Left = new TreeNode(6);
	root->Right->Right = new TreeNode(7);
	root->Left->Left->Left = new TreeNode(9);
	root->Left->Left->Right = new TreeNode(1);
	std::cout << "\nResult of tree balance check is " << isTreeBalanced(root).isBalanced;
}

void testdeleteNodeInBST() {
	struct TreeNode* root = new TreeNode(14);
	root->Left = new TreeNode(10);
	root->Left->Left = new TreeNode(9);
	root->Left->Right = new TreeNode(13);
	root->Right = new TreeNode(20);
	root->Right->Left = new TreeNode(17);
	root->Right->Right = new TreeNode(30);
	root->Right->Right->Left = new TreeNode(25);
	root->Right->Right->Left->Right = new TreeNode(26);
	root->Right->Right->Right = new TreeNode(35);
	std::cout << "Before deletion inorder tree is \n";
	printInOrderTree(root);
	std::cout << "\n";
	deleteNodeInBST(root, 20);
	std::cout << "Post deletion inorder tree is \n";
	printInOrderTree(root);
	std::cout << "\n";
}

void testconvertBSTToVector() {
	struct TreeNode* root = new TreeNode(14);
	root->Left = new TreeNode(10);
	root->Left->Left = new TreeNode(9);
	root->Left->Right = new TreeNode(13);
	root->Right = new TreeNode(20);
	root->Right->Left = new TreeNode(17);
	root->Right->Right = new TreeNode(30);
	root->Right->Right->Left = new TreeNode(25);
	root->Right->Right->Left->Right = new TreeNode(26);
	root->Right->Right->Right = new TreeNode(35);
	std::vector<int> vec = convertBSTToVector(root);
	for (std::vector<int>::iterator itr = vec.begin(); itr != vec.end(); itr++) {
		std::cout << *itr << "\t";
	}
}

void testfindMaxTreeWidth() {
	struct TreeNode* root = new TreeNode(14);
	root->Left = new TreeNode(10);
	root->Left->Left = new TreeNode(9);
	root->Left->Right = new TreeNode(13);
	root->Right = new TreeNode(20);
	root->Right->Left = new TreeNode(17);
	root->Right->Right = new TreeNode(30);
	root->Right->Right->Left = new TreeNode(25);
	root->Right->Right->Left->Right = new TreeNode(26);
	root->Right->Right->Right = new TreeNode(35);
	std::cout << "Max tree width is " << findMaxTreeWidth(root);
}