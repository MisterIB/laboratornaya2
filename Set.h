#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

struct Set {
private:
	struct Pair {
		int32_t first;
		int32_t second;

		Pair(int32_t first, int32_t second) : first(first), second(second) {}

		Pair() : first(NULL), second(NULL) {}
	};

	int32_t size, capacity;
	Pair* arr;

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
	Set(int32_t maxSize) {
		size = 0;
		capacity = maxSize;
		arr = new Pair[capacity];
	}

	int32_t SIZE() {
		return size;
	}

	bool IS_EMPTY() {
		return size == 0;
	}

	void SETADD(int32_t first, int32_t second) {
		std::string key = std::to_string(first) + std::to_string(second);
		int32_t index = hashFunction(key);
		arr[index].first = first;
		arr[index].second = second;
		size++;
	}

	void SETDEL(int32_t first, int32_t second) {
		std::string key = std::to_string(first) + std::to_string(second);
		int32_t index = hashFunction(key);
		arr[index].first = NULL;
		arr[index].second = NULL;
		size--;
	}

	bool SET_AT(int32_t first, int32_t second) {
		std::string key = std::to_string(first) + std::to_string(second);
		int32_t index = hashFunction(key);
		if (arr[index].first == first and arr[index].second == second) return true;
		if (arr[index].first == NULL) return false;
		
	}

	void print() {
		for (int32_t i = 0; i < capacity; i++) {
			if (arr[i].first == NULL) continue;
			else std::cout << arr[i].first << " " << arr[i].second << std::endl;
		}
	}

	void printInFile(std::ofstream& file) {
		file << size << std::endl;
		for (int32_t i = 0; i < capacity; i++) {
			if (arr[i].first == NULL) continue;
			else file << arr[i].first << " " << arr[i].second << std::endl;
		}
	}
};
