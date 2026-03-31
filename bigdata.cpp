#include "bigdata.h"

// 第一个重复元素
void testBigData1(){
    std::vector<int> vec;
    srand(time(0));
    for (int i = 0; i < 10000; i++){
        vec.push_back(rand() % 1000); // 生成0-999之间的随机数
    }

    std::unordered_set<int> set;
    for (const auto& num : vec){
        if (set.find(num) != set.end()){
            std::cout << "第一个重复元素是: " << num << std::endl;
            return;
        }
        set.insert(num);
    }
    std::cout << "没有重复元素" << std::endl;
}


// 找所有重复元素及其出现次数
void testBigData2(){
    std::vector<int> vec;
    srand(time(0));
    for (int i = 0; i < 10000; i++){
        vec.push_back(rand() % 1000); // 生成0-999之间的随机数
    }
    std::unordered_map<int, int> countMap;
    for(const auto& num : vec){
        countMap[num]++;
    }
    for(const auto& pair : countMap){
        if(pair.second > 1){
            std::cout << "元素: " << pair.first << " 出现次数: " << pair.second << std::endl;
        }
    }
}


// 位图
void testBigData3(){
    std::vector<int> vec{12, 78, 90, 78, 123, 8, 9};
    int max = vec[0];
    for(int i=1; i<vec.size(); i++){
        if(vec[i] > max){
            max = vec[i];
        }
    }
    int* bitmap = new int[max/32 + 1](); // 初始化位图
    std::unique_ptr<int[]> bitmapPtr(bitmap); // 使用智能指针管理内存
    for(const auto& num : vec){
        int index = num / 32;
        int offset = num % 32;
        if(bitmap[index] & (1 << offset)){
            std::cout << "元素 " << num << " 已经存在" << std::endl;
        } 
        else {
            bitmap[index] |= (1 << offset); // 设置对应位
        }
    }
}


// topK问题
void testBigData4(){
    std::vector<int> vec;
    srand(time(0));
    for (int i = 0; i < 10000; i++){
        vec.push_back(rand() % 1000); // 生成0-999之间的随机数
    }

    std::priority_queue<int> q; // 大顶堆
    int k = 5;
    for (int i = 0; i < k;++i){
        q.push(vec[i]);
    }
    for (int i = k;i<vec.size();++i){
        if(vec[i] < q.top()){
            q.pop();
            q.push(vec[i]);
        }
    }
    while (!q.empty()) {
        std::cout << q.top() << " ";
        q.pop();
    }
    std::cout << std::endl;
}