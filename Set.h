#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include "List.h"

struct Set {
	int32_t size, capacity;
	List<int32_t>* arr;
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
		arr = new List<int32_t>[capacity];
	}

	int32_t SIZE() {
		return size;
	}

	bool IS_EMPTY() {
		return size == 0;
	}

	void SETADD(int32_t value) {
		std::string key = std::to_string(value);
		int32_t index = hashFunction(key);
		if (arr[index].is_empty() or arr[index].find(value) == nullptr) {
			arr[index].push_back(value);
			size++;
		}
	}

	void SETDEL(int32_t value) {
		std::string key = std::to_string(value);
		int32_t index = hashFunction(key);
		arr[index].remove(value);
		size--;
	}

	bool SET_AT(int32_t value) {
		std::string key = std::to_string(value);
		int32_t index = hashFunction(key);
		if (arr[index].find(value) != nullptr) return true;
		return false;
	}

	void printInFile(std::ofstream& file, int32_t amountOfItem) {
		file << amountOfItem << std::endl;
		for (int32_t i = 0; i < capacity; i++) {
			arr[i].printInFileq(file);
		}
	}
};
