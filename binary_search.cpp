#include<iostream>
#include"binary_search.h"

int binarySearch(int arr[], int size, int val) {       // O(logn)
	int left = 0;
	int right = size - 1;

	while (left <= right) {
		int mid = left + (right - left) / 2;
		if (arr[mid] == val)
			return mid;
		else if (arr[mid] > val)
			right = mid - 1;
		else
			left = mid + 1;
	}
	return -1;
}

int binarySearch(int arr[], int left, int right, int val) {
	if (left > right) return -1;
	int mid = left + (right - left) / 2;
	if (arr[mid] == val) {
		return mid;
	}
	else if (arr[mid] > val) {
		return binarySearch(arr, left, mid - 1, val);
	}
	else {
		return binarySearch(arr, mid + 1, right, val);
	}
}

void testBinarySearch() {
	int arr[] = { 2,4,7,9,13,15,78,567,678 };
	std::cout << binarySearch(arr, sizeof(arr) / sizeof(arr[0]), 78) << std::endl;
	std::cout << binarySearch(arr, 0, sizeof(arr) / sizeof(arr[0]), 78) << std::endl;
}