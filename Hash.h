#pragma once

#include <iostream>
#include <string>

#include "Pair.h"

struct HList {
private:
	struct Node {
		std::string first, second;
		int32_t delay;
		Node* next;

		Node(std::string first, std::string second, int32_t delay) : delay(delay), first(first), second(second), next(nullptr) {}
	};
public:

	Node* head;
	Node* tail;
	int32_t itemsAmountForeach = 0;

public:
	HList() : head(nullptr), tail(nullptr) {}

	bool is_empty() {
		return head == nullptr;
	}

	int32_t get(std::string first, std::string second) {
		Node* tempNode = head;
		while (tempNode and tempNode->first != first and tempNode->second != second) tempNode = tempNode->next;
		if (tempNode and tempNode->first == first and tempNode->second == second) return tempNode->delay;
		return NULL;
	}

	void push_back(std::string first, std::string second, int32_t delay) {
		Node* newNode = new Node(first, second, delay);
		if (is_empty()) {
			head = newNode;
			tail = newNode;
			return;
		}
		tail->next = newNode;
		tail = newNode;
	}

	PAIR foreach(std::string first) {
		if (is_empty()) {
			PAIR NullPair;
			return NullPair;
		}
		Node* tempNode = head;
		PAIR correctPair;
		for (int32_t numberCurrentItem = 0; tempNode; numberCurrentItem++) {
			if (tempNode->first == first) {
				correctPair.add(tempNode->second, tempNode->delay);
				if (itemsAmountForeach == numberCurrentItem) {
					itemsAmountForeach++;
					if (tempNode->next == nullptr) itemsAmountForeach = 0;
					return correctPair;
				}
			}
			tempNode = tempNode->next;
		}
		PAIR NullPair;
		return NullPair;
	}

	void print() {
		if (is_empty()) return;
		Node* printNode = head;
		while (printNode) {
			std::cout << "<" << printNode->first << ", " << printNode->second << "> ";
			printNode = printNode->next;
		}
		std::cout << std::endl;
	}
};

struct Hash {
private:
	HList* arr;
	int32_t amountOfItems, capacity;

	int32_t hashFunction(std::string key) {
		const int32_t k = 41, mod = 1e9 + 9;
		int64_t h = 0, m = 1;
		for (unsigned char character : key) {
			int32_t x = character - 'a' + 1;
			h = (h + m * x) % mod;
			m = (m * k) % mod;
		}
		if (h < 0) return -h % capacity;
		return h % capacity;
	}
public:
	int32_t itemsAmountForeach;

	Hash() {
		capacity = 100;
		amountOfItems = 0;
		itemsAmountForeach = 0;
		arr = new HList[capacity];
	}

	int32_t SIZE() {
		return amountOfItems;
	}

	void HSET(std::string first, std::string second, int32_t delay) {
		std::string key = first + second;
		int32_t index = hashFunction(key);
		HList tempList = arr[index];
		tempList.push_back(first, second, delay);
		arr[index] = tempList;
		amountOfItems++;
	}

	int32_t HGET(std::string first, std::string second) {
		std::string key = first + second;
		int32_t index = hashFunction(key);
		HList tempList = arr[index];
		return tempList.get(first, second);
	}

	PAIR foreach(std::string first) {
		for (; itemsAmountForeach < capacity; itemsAmountForeach++) {
			if (arr[itemsAmountForeach].foreach(first).delay == NULL) continue;
			return arr[itemsAmountForeach].foreach(first);
		}
		if (itemsAmountForeach == capacity) itemsAmountForeach = 0;
		PAIR NullPair;
		return NullPair;
	}

	void print() {
		for (int32_t i = 0; i < capacity; i++) {
			if (!arr[i].is_empty()) arr[i].print();
		}
		std::cout << std::endl;
	}
};
