#include"dynamic_programming.h"

int maxSubArray(std::vector<int>& nums){
    int max_sum = nums[0];
    int cur_sum = 0;
    for(const int& num : nums){
        cur_sum = std::max(cur_sum + num, num);
        max_sum = std::max(max_sum, cur_sum);
    }
    return max_sum;
}
