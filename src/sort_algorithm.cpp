#include<iostream>
#include<string>
#include<vector>
#include"sort_algorithm.h"


void bubble_sort(int arr[], int size) {           // 最好O(n)  最坏O(n^2)  O(1)   稳定
	for (int i = 0; i < size - 1; i++) {
		bool swapped = false;
		for (int j = 0; j < size - i - 1; j++) {
			if (arr[j] > arr[j + 1]) {
				int tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
				swapped = true;
			}
		}
		if (!swapped) return;
	}
}

void select_sort(int arr[], int size) {            // 最好O(n^2)  最坏O(n^2)  O(1)  不稳定
	for (int i = 0; i < size - 1; i++) {
		int min = i;
		for (int j = i+1; j < size; j++) {
			if (arr[j] < arr[min]) {
				min = j;
			}
		}
		if (min != i) {
			int tmp = arr[i];
			arr[i] = arr[min];
			arr[min] = tmp;
		}
	}
}

void insert_sort(int arr[], int size) {            // 最好O(n)  O(n^2)   O(1)   稳定
	for (int i = 1; i < size; i++) {
		int val = arr[i];
		int j = i - 1;
		while (j >= 0 && val < arr[j]) {
			arr[j + 1] = arr[j];
			j--;
		}
		arr[j + 1] = val;
	}
}

void shell_sort(int arr[], int size) {             // O(n^2)  O(n)  O(1)  不稳定
	for (int gap = size / 2; gap > 0; gap /= 2) {
		for (int i = gap; i < size; i++) {
			int val = arr[i];
			int j = i - gap;
			while (j >= 0 && val < arr[j]) {
				arr[j + gap] = arr[j];
				j -= gap;
			}
			arr[j + gap] = val;
		}
	}
}

int partition(int arr[], int low, int high) {
	int mid = low + (high - low) / 2;
	std::swap(arr[low], arr[mid]);

	int pivot = arr[low];

	while (low < high) {
		while (low < high && arr[high] >= pivot) {
			high--;
		}
		if (low < high) {
			arr[low] = arr[high];
			low++;
		}
		while (low < high && arr[low] < pivot) {
			low++;
		}
		if (low < high) {
			arr[high] = arr[low];
			high--;
		}
	}
	arr[low] = pivot;
	return low;
}

void quick_sort(int arr[], int start, int end) {          // 最好/平均O(nlogn)  最坏O(n^2)   O(logn)  不稳定
	if (start >= end) return;
	int pivot_pos = partition(arr, start, end);
	quick_sort(arr, start, pivot_pos - 1);
	quick_sort(arr, pivot_pos + 1, end);
}

void quick_sort(int arr[], int size) {            // 外部接口
	if (size > 0) {
		quick_sort(arr, 0, size - 1);
	}
}

void merge(int arr[], int temp[], int left, int mid, int right) {
	int i = left;
	int j = mid + 1;
	int k = left;      // 临时数组的当前索引 (直接映射 arr 的下标，方便拷贝)

	// 1. 合并两个有序区间
	while (i <= mid && j <= right) {
		if (arr[i] <= arr[j]) {
			temp[k++] = arr[i++];
		}
		else {
			temp[k++] = arr[j++];
		}
	}

	// 2. 处理剩余元素
	while (i <= mid) {
		temp[k++] = arr[i++];
	}
	while (j <= right) {
		temp[k++] = arr[j++];
	}

	// 3. 将有序数据拷回原数组
	if (right >= left) {
		int copy_count = right - left + 1;
		memcpy(arr + left, temp + left, copy_count * sizeof(int));
	}
}

void merge_sort_recursive(int arr[], int temp[], int begin, int end) {
	if (begin >= end) return;
	int mid = begin + (end - begin) / 2;
	merge_sort_recursive(arr, temp, begin, mid);
	merge_sort_recursive(arr, temp, mid + 1, end);
	merge(arr, temp, begin, mid, end);
}

void merge_sort(int arr[], int size) {          // 外部接口
	if (size <= 1) return;

	int* temp = new int[size];
	merge_sort_recursive(arr, temp, 0, size - 1);

	delete[] temp;
	temp = nullptr;
}

void adjustHeap(int arr[], int i, int length) {
	int temp = arr[i];
	for (int child = 2 * i + 1; child < length; child = 2 * child + 1) {
		if (child + 1 < length && arr[child] < arr[child + 1]) {
			child++;
		}
		if (arr[child] > temp) {
			arr[i] = arr[child];
			i = child;
		}
		else {
			break;
		}
	}
	arr[i] = temp;
}

void heap_sort(int arr[], int n) {
	for (int i = n / 2 - 1; i >= 0; i--) {
		adjustHeap(arr, i, n);
	}
	for (int i = n - 1; i > 0; i--) {
		std::swap(arr[0], arr[i]);
		adjustHeap(arr, 0, i);
	}
}

void radix_sort(int arr[], int size) {
	if (size <= 1) return;
	int max_val = arr[0];
	for (int i = 1; i < size; i++) {
		if (arr[i] > max_val) {
			max_val = arr[i];
		}
	}
	int len = std::to_string(max_val).size();
	std::vector<std::vector<int>> vecs(10);
	int dev = 1;
	for (int i = 0; i < len; i++, dev *= 10) {
		for (int j = 0; j < size; j++) {
			int index = arr[j] / dev % 10;
			vecs[index].push_back(arr[j]);
		}
		int idx = 0;
		for (auto& vec : vecs) {
			for (int v : vec) {
				arr[idx++] = v;
			}
		}
		for (auto& vec : vecs) {
			vec.clear();
		}
	}
}

void testsort() {
	int arr[10];
	srand(time(NULL));
	for (int i = 0; i < 10; i++) {
		int val = rand() % 100 + 1;
		arr[i] = val;
		std::cout << val << " ";
	}
	std::cout << std::endl;
	radix_sort(arr,sizeof(arr)/sizeof(arr[0]));
	for (int val:arr) {
		std::cout << val << " ";
	}
	std::cout << std::endl;
}