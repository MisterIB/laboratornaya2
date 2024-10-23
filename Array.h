#pragma once

#include <iostream>
#include <algorithm>

template <typename T>
struct Array {
public://Изменить
	T* arr;
	int32_t capacity, currentSize;

	Array() {
		arr = new T[1];
		capacity = 1;
		currentSize = 0;
	}

	~Array() { delete[] arr; }

	void push_back(T value) {
		if (capacity == currentSize) {
			T* temp = new T[2 * capacity];
			for (int32_t i = 0; i < capacity; i++) temp[i] = arr[i];
			delete[] arr;
			capacity *= 2;
			arr = temp;
		}
		arr[currentSize] = value;
		currentSize++;
	}

	void insert(int32_t index, T value) {
		if (index == currentSize) {
			push_back(value);
			return;
		}
		if (capacity == currentSize) {
			T* temp = new T[2 * capacity];
			for (int32_t i = 0; i < capacity; i++) temp[i] = arr[i];
			delete[] arr;
			capacity *= 2;
			arr = temp;
		}
		T* tempArray = new T[capacity];
		if (index > currentSize) return;
		for (int32_t i = 0, j = 0; i < currentSize; i++, j++) {
			if (i == index) {
				tempArray[i] = value;
				if (index + 1 != capacity) {
					j++;
					tempArray[j] = arr[i];
				}
			}
			else tempArray[j] = arr[i];
		}
		delete[] arr;
		arr = tempArray;
		currentSize++;
	}

	void erase(int32_t index) {
		if (index >= currentSize) return;
		T* temp = new T[capacity];
		for (int32_t i = 0, j = 0; i < currentSize; i++, j++) {
			if (i == index) {
				i++;
			}
			temp[j] = arr[i];
		}
		delete[] arr;
		arr = temp;
		currentSize--;
	}

	int32_t size() {
		return currentSize;
	}

	int32_t compare(const void* a, const void* b) {
		const int* x = (int*)a;
		const int* y = (int*)b;
		if (*x > *y) return 1;
		else if (*x < *y) return -1;
		return 0;
	}

	void sort() {
		for (int32_t i = 1; i < currentSize; i++) {
			int32_t j = i - 1;
			while (j >= 0 && arr[j] > arr[j + 1]) {
				std::swap(arr[j], arr[j + 1]);
				j--;
			}
		}
	}

	void print() {
		for (int32_t i = 0; i < currentSize; i++) {
			std::cout << arr[i];
		}
		std::cout << std::endl;
	}

	T& operator[](int32_t index) {
		return arr[index];
	}
};
