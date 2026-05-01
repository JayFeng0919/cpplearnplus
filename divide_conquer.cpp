#include "divide_conquer.h"

int QuickSort::partition(std::vector<int> &vec, int l, int r){
	int pivot = vec[r];
	while (l < r){
		while (l < r && vec[l] <= pivot){
			l++;
		}
		if (l < r){
			vec[r--] = vec[l];
		}
		while (l < r && vec[r] >= pivot){
			r--;
		}
		if (l < r){
			vec[l++] = vec[r];
		}
	}
	vec[l] = pivot;
	return l;
}

void QuickSort::quickSort(std::vector<int> &vec){
	quickSort(vec, 0, vec.size() - 1);
}

void QuickSort::quickSort(std::vector<int> &vec, int left, int right){
	if (left >= right)
		return;
	int pos = partition(vec, left, right);
	quickSort(vec, left, pos - 1);
	quickSort(vec, pos + 1, right);
}

void QuickSort::test(){
	std::vector<int> vec{4, 7, 1, 3, 9, 5, 4, 7, 37, 43, 22};
	quickSort(vec);
	for (const int &num : vec){
		std::cout << num << " ";
	}
	std::cout << "\n";
}


int QuickSelect::partition(std::vector<int>& vec, int l, int r) {
	int pivot = vec[r];
	while (l < r) {
		while (l < r && vec[l] <= pivot) {
			l++;
		}
		if (l < r) {
			vec[r--] = vec[l];
		}
		while (l < r && vec[r] >= pivot) {
			r--;
		}
		if (l < r) {
			vec[l++] = vec[r];
		}
	}
	vec[l] = pivot;
	return l;
}

int QuickSelect::min_topk(std::vector<int>& vec, int k) {
	return min_topk(vec, k, 0, vec.size() - 1);
}

int QuickSelect::min_topk(std::vector<int>& vec, int k, int l, int r) {
	int pos = partition(vec, l, r);
	if (pos == k - 1) {
		return vec[pos];
	}
	else if (pos < k - 1) {
		return min_topk(vec, k, pos + 1, r);
	}
	else {
		return min_topk(vec, k, l, pos - 1);
	}
}

int QuickSelect::max_topk(std::vector<int>& vec, int k) {
	return max_topk(vec, k, 0, vec.size() - 1);
}

int QuickSelect::max_topk(std::vector<int>& vec, int k, int l, int r) {
	int pos = partition(vec, l, r);
	if(pos == vec.size() - k) {
		return vec[pos];
	}
	else if (pos < vec.size() - k) {
		return max_topk(vec, k, pos + 1, r);
	}
	else {
		return max_topk(vec, k, l, pos - 1);
	}
}

void QuickSelect::test_min_topk() {
	std::vector<int> vec{ 4, 7, 10, 3, 9, 5, 4, 7, 37, 43, 22 };
	std::cout << min_topk(vec, 2) << "\n";
	for (int i = 0; i < 2; i++) {
		std::cout << vec[i] << " ";	
	}
	std::cout << "\n";
}

void QuickSelect::test_max_topk() {
	std::vector<int> vec{ 4, 7, 10, 3, 9, 5, 4, 7, 37, 43, 22 };
	std::cout << max_topk(vec, 3) << "\n";
	for (int i = vec.size() - 3; i < vec.size(); i++) {
		std::cout << vec[i] << " ";
	}
	std::cout << "\n";
}


void MergeSort::merge(std::vector<int>& vec, int l, int mid, int r) {
	std::vector<int> tmp;
	tmp.reserve(r - l + 1);
	int i = l, j = mid + 1;
	while (i <= mid && j <= r) {
		if (vec[i] <= vec[j]) {
			tmp.emplace_back(vec[i++]);
		}
		else {
			tmp.emplace_back(vec[j++]);
		}
	}
	while (i <= mid) {
		tmp.emplace_back(vec[i++]);
	}
	while (j <= r) {
		tmp.emplace_back(vec[j++]);
	}
	for (int k = l; k <= r; k++) {
		vec[k] = tmp[k - l];
	}
}

void MergeSort::mergesort(std::vector<int>& vec) {
	mergesort(vec, 0, vec.size() - 1);
}

void MergeSort::mergesort(std::vector<int>& vec, int l, int r) {
	if (l == r)
		return;
	int mid = l + (r - l) / 2;
	mergesort(vec, l, mid);
	mergesort(vec, mid + 1, r);
	merge(vec, l, mid, r);
}

void MergeSort::test() {
	std::vector<int> vec{ 4, 7, 1, 3, 9, 5, 4, 7, 37, 43, 22 };
	mergesort(vec);
	for (const int& num : vec) {
		std::cout << num << " ";
	}
	std::cout << "\n";
}


MergeKSortedLists::ListNode* MergeKSortedLists::mergeTwoLists(ListNode *l1, ListNode *l2){
	if (!l1)
		return l2;
	if (!l2)
		return l1;
	if (l1->val > l2->val)
		std::swap(l1, l2);
	ListNode *head = l1;
	ListNode *cur = head;
	l1 = l1->next;
	while (1){
		if (!l1){
			cur->next = l2;
			break;
		}
		if (!l2){
			cur->next = l1;
			break;
		}
		if (l1->val <= l2->val){
			cur->next = l1;
			cur = l1;
			l1 = l1->next;
		}
		else{
			cur->next = l2;
			cur = l2;
			l2 = l2->next;
		}
	}
	return head;
}

MergeKSortedLists::ListNode* MergeKSortedLists::mergeKLists(std::vector<ListNode *> &lists, int l, int r){
	if (l == r){
		return lists[l];
	}
	if (l + 1 == r){
		return mergeTwoLists(lists[l], lists[r]);
	}
	int mid = l + (r - l) / 2;
	ListNode *left = mergeKLists(lists, l, mid);
	ListNode *right = mergeKLists(lists, mid + 1, r);
	return mergeTwoLists(left, right);
}

MergeKSortedLists::ListNode *MergeKSortedLists::mergeKLists(std::vector<ListNode *> &lists){
	if (lists.empty())
		return nullptr;
	return mergeKLists(lists, 0, lists.size() - 1);
}