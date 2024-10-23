#pragma once

#include "Array.h"

template <typename T>
struct SBT {
private:
	template <typename U>
	struct Node {
		Node<U>* right;
		Node<U>* left;
		U value;

		Node(U value): value(value), left(nullptr), right(nullptr) {}
	};

	Node<T>* root;

public:

	SBT() {
		root = nullptr;
	}

	bool is_empty() {
		return root == nullptr;
	}

	void findPlaceToInsert(T value, Node<T>* node) {
		if (node->value > value and node->left == nullptr) {
			Node<T>* newNode = new Node<T>(value);
			node->left = newNode;
			return;
		}
		else if (node->value <= value and node->right == nullptr) {
			Node<T>* newNode = new Node<T>(value);
			node->right = newNode;
			return;
		}
		else if (node->value > value and node->left != nullptr) {
			findPlaceToInsert(value, node->left);
		}
		else if (node->value <= value and node->right != nullptr) {
			findPlaceToInsert(value, node->right);
		}
	}

	void insert(T value) {
		if (is_empty()) {
			Node<T>* newNode = new Node<T>(value);
			root = newNode;
			return;
		}
		findPlaceToInsert(value, root);
	}

	bool printRec(Node<T>* node, Array<T>& leaves) {
		if (node == nullptr) return true;
		bool isEmptyRight = printRec(node->right, leaves);
		bool isEmptyLeft = printRec(node->left, leaves);
		if (isEmptyRight and isEmptyLeft) leaves.push_back(node->value);
		return false;
	}

	void print() {
		if (is_empty()) return;
		Array<T> leaves;
		printRec(root, leaves);
		leaves.sort();
		for (int32_t i = 0; i < leaves.size(); i++) {
			std::cout << leaves[i] << " ";
		}
	}
};
