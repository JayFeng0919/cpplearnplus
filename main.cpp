#include <iostream>
#include"vector.h"
#include"list.h"
#include"stack.h"
#include"queue.h"
#include"binary_search.h"
#include"sort_algorithm.h"
#include"hashtable.h"
#include"BST.h"
#include"BSTREE.h"
#include"AVL.h"
#include"backtrack.h"
#include"divide_conquer.h"

int main(){
	// testvector();
	// singly::testClink();
	// singly::testCircleLink();
	// doubly::testDoubleLink();
	// testSeqStack();
	// testLinkStack();
	// testCircleQueue();
	// testLinkQueue();
	// testBinarySearch();
	// testsort();
	// linear::testHashTable();
	// linked::testHashTable();
	// testBigData1();
	// testBST1();
	// testAVL();


	return 0;
}


// #include <iostream>
// #include <vector>
// #include <unordered_map>
// #include <unordered_set>
// using namespace std;

// struct A
// {
// 	A(int self_, int other_, int banben_)
// 		: self(self_), other(other_), banben(banben_)
// 	{
// 	}
// 	int self;
// 	int other;
// 	int banben;
// };

// bool solution(vector<A> &depends)
// {
// 	// 判断depends内是否存在循环依赖
// 	unordered_map<int, vector<int>> graph;
// 	unordered_set<int> all_nodes;
// 	for (auto &a : depends) {
// 		graph[a.self].push_back(a.other);
// 		all_nodes.insert(a.self);
// 		all_nodes.insert(a.other);
// 	}
	
// 	unordered_set<int> visiting, visited;
	
// 	auto hasCycle = [&](auto &self, int node) -> bool {
// 		if (visiting.count(node)) return true;
// 		if (visited.count(node)) return false;
// 		visiting.insert(node);
// 		for (int nei : graph[node]) {
// 			if (self(self, nei)) return true;
// 		}
// 		visiting.erase(node);
// 		visited.insert(node);
// 		return false;
// 	};
	
// 	for (int node : all_nodes) {
// 		if (visited.count(node) == 0 && hasCycle(hasCycle, node)) return true;
// 	}
// 	return false;
// }	

// int main(){
// 	int n1;
// 	cin >> n1;
// 	vector<A> depends1(n1);
// 	for (int i = 0; i < n1; i++){
// 		int self, other, banben;
// 		cin >> self >> other >> banben;
// 		depends1[i] = A(self, other, banben);
// 	}
// 	int n2;
// 	cin >> n2;
// 	vector<A> depends2(n2);
// 	for (int i = 0; i < n2; i++){
// 		int self, other, banben;
// 		cin >> self >> other >> banben;
// 		depends2[i] = A(self, other, banben);
// 	}
// 	cout << (solution(depends1) ? "false" : "true") << endl;
// 	cout << (solution(depends2) ? "false" : "true") << endl;

// 	return 0;
// }

// #include <iostream>
// #include <vector>
// #include <queue>
// #include <climits>
// using namespace std;

// int solution(vector<vector<int>> &matrix){
// 	int rows = matrix.size();
// 	if (rows == 0) return -1;  // 如果矩阵为空，返回-1
// 	int cols = matrix[0].size();
	
// 	// 检查起点和终点是否可通行（必须是0）
// 	if (matrix[0][0] != 0 || matrix[rows-1][cols-1] != 0) return -1;
	
// 	// visited[行][列][方向] 记录到达该位置和方向的最小转弯次数
// 	vector<vector<vector<int>>> visited(rows, vector<vector<int>>(cols, vector<int>(4, INT_MAX)));
	
// 	// 定义路径状态：位置(x,y)、当前方向、转弯次数
// 	struct PathState {
// 		int x, y, direction, turn_count;
// 		bool operator>(const PathState& other) const {
// 			return turn_count > other.turn_count;
// 		}
// 	};
	
// 	// 优先队列，用于找到最小转弯次数的路径
// 	priority_queue<PathState, vector<PathState>, greater<PathState>> min_heap;
	
// 	// 方向数组：右、下、左、上
// 	int dir_x[4] = {0, 1, 0, -1};
// 	int dir_y[4] = {1, 0, -1, 0};
	
// 	// 从起点开始，初始方向可以是右(0)或下(1)，转弯次数为0
// 	min_heap.push({0, 0, 0, 0});  // 向右走
// 	min_heap.push({0, 0, 1, 0});  // 向下走
// 	visited[0][0][0] = 0;
// 	visited[0][0][1] = 0;
	
// 	while (!min_heap.empty()) {
// 		PathState current = min_heap.top();
// 		min_heap.pop();
// 		int x = current.x, y = current.y, direction = current.direction, turn_count = current.turn_count;
		
// 		// 如果到达终点，返回转弯次数
// 		if (x == rows - 1 && y == cols - 1) return turn_count;
		
// 		// 尝试四个方向移动
// 		for (int new_direction = 0; new_direction < 4; new_direction++) {
// 			int new_x = x + dir_x[new_direction];
// 			int new_y = y + dir_y[new_direction];
			
// 			// 检查新位置是否在矩阵内且可通行
// 			if (new_x >= 0 && new_x < rows && new_y >= 0 && new_y < cols && matrix[new_x][new_y] == 0) {
// 				// 计算新转弯次数：如果方向改变，转弯+1
// 				int new_turn_count = turn_count + (new_direction != direction ? 1 : 0);
				
// 				// 如果找到更小的转弯次数，更新并加入队列
// 				if (new_turn_count < visited[new_x][new_y][new_direction]) {
// 					visited[new_x][new_y][new_direction] = new_turn_count;
// 					min_heap.push({new_x, new_y, new_direction, new_turn_count});
// 				}
// 			}
// 		}
// 	}
	
// 	// 如果无法到达，返回-1
// 	return -1;
// }

// int main(){
// 	int m, n;
// 	cin >> m >> n;
// 	if(m <= 0 || m > 100) {
// 		cout<<-1 << endl;
// 		return 0;
// 	}
// 	if(n <= 0 || n > 100) {
// 		cout<<-1 << endl;
// 		return 0;
// 	}

// 	vector<vector<int>> matrix(m, vector<int>(n));
// 	for (int i = 0; i < m; i++){
// 		for (int j = 0; j < n; j++){
// 			cin >> matrix[i][j];
// 		}
// 	}

// 	cout << solution(matrix) << endl;

// 	return 0;
// }


// #include <iostream>
// #include <vector>
// #include <unordered_map>
// #include <unordered_set>
// #include <map>
// #include <set>
// #include <algorithm>
// #include <functional>
// using namespace std;

// #define ll long long

// int solution(ll E, vector<int> &damage, vector<int> &reward){
// 	int n = damage.size();
// 	vector<unordered_map<ll, int>> memo(n);
	
// 	auto dfs = [&](auto &self, int i, ll curr_E) -> int {
// 		if (i == n) return 0;
// 		if (memo[i].count(curr_E)) return memo[i][curr_E];
		
// 		int ans = self(self, i + 1, curr_E); // 不打
// 		if (curr_E > damage[i]) {
// 			ll new_E = curr_E + reward[i] - damage[i];
// 			ans = max(ans, 1 + self(self, i + 1, new_E)); // 打
// 		}
// 		memo[i][curr_E] = ans;
// 		return ans;
// 	};
	
// 	return dfs(dfs, 0, E);
// }

// int main(){
// 	ll E;
// 	cin >> E;
// 	vector<ll> tmp;
// 	ll a;
// 	while (cin >> a) {
// 		tmp.push_back(a);
// 	}
	
// 	int total = tmp.size();
// 	int num = total / 2;
	
// 	vector<int> damage(num);
// 	for (int i = 0; i < num; i++){
// 		damage[i] = tmp[i];
// 	}
// 	vector<int> reward(num);
// 	for (int i = 0; i < num; i++){
// 		reward[i] = tmp[i + num];
// 	}

// 	cout << solution(E, damage, reward) << endl;

// 	return 0;
// }
