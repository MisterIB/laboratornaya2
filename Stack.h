#pragma once

#include <iostream>
#include <fstream>

template <typename T>
struct Stack {
private:
	template <typename U>
	struct Node {
		U value;
		Node<U>* next;
		Node<U>* prev;

		Node(U value) : value(value), next(nullptr), prev(nullptr) {}
	};

	Node<T>* head;
	Node<T>* tail;

public:
	Stack() : head(nullptr), tail(nullptr) {}

	bool is_empty() {
		return head == nullptr;
	}

	void push(T value) {
		Node<T>* newNode = new Node<T>(value);
		if (is_empty()) {
			head = newNode;
			tail = newNode;
			return;
		}
		newNode->next = head;
		head->prev = newNode;
		head = newNode;
	}

	T pop() {
		if (is_empty()) return NULL;
		Node<T>* temp = head;
		head = head->next;
		head->prev = nullptr;
		T value = temp->value;
		delete temp;
		return value;
	}

	int32_t size() {
		int32_t size = 0;
		Node<T>* tempNode = head;
		while (tempNode) {
			tempNode = tempNode->next;
			size++;
		}
		return size;
	}

	void print() {
		Node<T>* tempNode = head;
		while (tempNode) {
			std::cout << tempNode->value << " ";
			tempNode = tempNode->next;
		}
		std::cout << std::endl;
	}

	void printInFile(std::ofstream& file) {
		Node<T>* tempNode = tail;
		while (tempNode) {
			file << tempNode->value << " ";
			tempNode = tempNode->prev;
		}
		file << std::endl;
	}
};
