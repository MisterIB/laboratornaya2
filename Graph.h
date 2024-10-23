#pragma once
//исключения

#include <iostream>

struct Graph {
private:
	struct Node {
		int32_t key;
		Node* next;

		Node(int32_t key) : key(key), next(nullptr) {}
	};

	int32_t amountOfVertices;
	Node** graph;

public:
	Graph(int32_t size) {
		amountOfVertices = size;
		graph = new Node*[amountOfVertices];
		for (int32_t i = 0; i < amountOfVertices; i++) {
			graph[i] = nullptr;
		}
	}

	void addEdge(int32_t firstVertex, int32_t secondVertex) {
		Node* firstNewNode = new Node(firstVertex);
		if (graph[secondVertex] == nullptr) graph[secondVertex] = firstNewNode;
		else {
			firstNewNode->next = graph[secondVertex]->next;
			graph[secondVertex]->next = firstNewNode;
		}
		Node* secondNewNode = new Node(secondVertex);
		if (graph[firstVertex] == nullptr) graph[firstVertex] = secondNewNode;
		else {
			secondNewNode->next = graph[firstVertex]->next;
			graph[firstVertex]->next = secondNewNode;
		}
	}

	int32_t size() {
		return amountOfVertices;
	}

	int32_t chainSize(int32_t key) {
		int32_t size = 0;
		Node* tempNode = graph[key];
		while (tempNode) {
			tempNode = tempNode->next;
			size++;
		}
		return size;
	}

	void print() {
		std::cout << "Список смежности вершин" << std::endl;
		for (int32_t i = 0; i < amountOfVertices; i++) {
			Node* tempNode = graph[i];
			std::cout << i << ": ";
			while (tempNode) {
				std::cout << tempNode->key << " ";
				tempNode = tempNode->next;
			}
			std::cout << std::endl;
		}
	}

	int32_t getItemFromChain(int32_t key, int32_t indexOfItem) {
		int32_t counter = 1;
		Node* tempNode = graph[key];
		while (tempNode) {
			if (counter == indexOfItem) break;
			tempNode = tempNode->next;
			counter++;
		}
		return tempNode->key;
	}
};

