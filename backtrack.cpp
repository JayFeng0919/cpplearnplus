#include"backtrack.h"

void func(std::vector<int>& v, std::vector<int> x, int i, int size) {
	if (i == size) {
		for (int j = 0; j < size; j++) {
			if(x[j] == 1){
				std::cout << v[j] << " ";
			}
		}
		std::cout << std::endl;
	}
	else{
		x[i] = 1;
		func(v, x, i + 1, size);
		x[i] = 0;
		func(v, x, i + 1, size);
	}
}

void test_backtrack() {
	std::vector<int> x(3, -1);
	std::vector<int> v{ 1,2,3 };
	auto size = v.size();
	func(v, x, 0, size);
}