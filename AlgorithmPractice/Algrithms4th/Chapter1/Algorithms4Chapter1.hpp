//
//  Algorithms4Chapter1.hpp
//  AlgorithmPractice
//
//  Created by arvintan on 2021/1/10.
//  Copyright © 2021 arvintan. All rights reserved.
//

#ifndef Algorithms4Chapter1_hpp
#define Algorithms4Chapter1_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include <map>
#include <stack>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <sstream>
#include <iostream>
#include <iosfwd>
#include <float.h>

using namespace std;

class Algorithms4Chapter1 {
public:
    
};

/**
 704. 二分查找
 给定一个 n 个元素有序的（升序）整型数组 nums 和一个目标值 target  ，写一个函数搜索 nums 中的 target，如果目标值存在返回下标，否则返回 -1。


 示例 1:

 输入: nums = [-1,0,3,5,9,12], target = 9
 输出: 4
 解释: 9 出现在 nums 中并且下标为 4
 示例 2:

 输入: nums = [-1,0,3,5,9,12], target = 2
 输出: -1
 解释: 2 不存在 nums 中因此返回 -1
  

 提示：

 你可以假设 nums 中的所有元素是不重复的。
 n 将在 [1, 10000]之间。
 nums 的每个元素都将在 [-9999, 9999]之间。
 通过次数86,752提交次数155,615
 */
/**
 算法4 P28
 */
class BinarySearchSolution {
public:
    int search(vector<int>& nums, int target) {
        int n = (int)nums.size();
        
        int ret = -1;
        int left = 0;
        int right = n - 1;
        
        while (left <= right) {
            int mid = left + (right - left)/2;
            if (nums[mid] < target) {
                left = mid + 1;
            } else if (nums[mid] > target) {
                right = mid - 1;
            } else {
                ret = mid;
                break;
            }
        }
        
        return ret;
    }
};

#endif /* Algorithms4Chapter1_hpp */
