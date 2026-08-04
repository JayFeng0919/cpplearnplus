#include"backtrack.h"

void Subsets::backtrack(std::vector<std::vector<int>> &res, std::vector<int> &path, std::vector<int> &nums, int start) {
	res.push_back(path);
	for (int i = start; i < nums.size(); i++) {
		path.push_back(nums[i]);
		Subsets::backtrack(res, path, nums, i + 1);
		path.pop_back();
	}
}

std::vector<std::vector<int>> Subsets::subsets(std::vector<int> &nums) {
	std::vector<std::vector<int>> res;
	std::vector<int> path;
	Subsets::backtrack(res, path, nums, 0);
	return res;
}

void Subsets::test() {
	std::vector<int> nums{1, 2, 3};
	std::vector<std::vector<int>> res = Subsets::subsets(nums);
	for (auto &vec : res) {
		for (auto &num : vec) {
			std::cout << num << " ";
		}
		std::cout << "\n";
	}
}


void Combine::backtrack(std::vector<std::vector<int>> &res, std::vector<int> &path, int n, int k, int start, int length) {
	if (length == k) {
		res.push_back(path);
		return;
	}
	for (int i = start; i <= n; i++) {
		path.push_back(i);
		Combine::backtrack(res, path, n, k, i + 1, length + 1);
		path.pop_back();
	}
}

std::vector<std::vector<int>> Combine::combine(int n, int k) {
	std::vector<std::vector<int>> res;
	std::vector<int> path;
	Combine::backtrack(res, path, n, k, 1, 0);
	return res;
}

void Combine::test() {
	int n = 4, k = 2;
	std::vector<std::vector<int>> res = Combine::combine(n, k);
	for (auto &vec : res) {
		for (auto &num : vec) {
			std::cout << num << " ";
		}
		std::cout << "\n";
	}
}


void Permute::backtrack(std::vector<std::vector<int>> &res, std::vector<int> &path,
			   std::vector<bool> &used, std::vector<int> &nums, int length) {
	if (length == nums.size()) {
		res.push_back(path);
		return;
	}
	for (int i = 0; i < nums.size(); i++) {
		if (used[i]) {
			continue;
		}
		path.push_back(nums[i]);
		used[i] = true;
		Permute::backtrack(res, path, used, nums, length + 1);
		path.pop_back();
		used[i] = false;
	}
}

std::vector<std::vector<int>> Permute::permute(std::vector<int> &nums) {
	std::vector<std::vector<int>> res;
	std::vector<int> path;
	std::vector<bool> used(nums.size(), false);
	Permute::backtrack(res, path, used, nums, 0);
	return res;
}

void Permute::test() {
	std::vector<int> nums{1, 2, 3};
	std::vector<std::vector<int>> res = Permute::permute(nums);
	for (auto &vec : res) {
		for (auto &num : vec) {
			std::cout << num << " ";
		}
		std::cout << "\n";
	}
}