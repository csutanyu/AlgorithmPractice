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

/**
 算法4第一章节 1.3.1.7 算术表达式求值
 */
class CalculatorSolution {
public:
    /**
      227. 基本计算器 II
      实现一个基本的计算器来计算一个简单的字符串表达式的值。

      字符串表达式仅包含非负整数，+， - ，*，/ 四种运算符和空格  。 整数除法仅保留整数部分。

      示例 1:

      输入: "3+2*2"
      输出: 7
      示例 2:

      输入: " 3/2 "
      输出: 1
      示例 3:

      输入: " 3+5 / 2 "
      输出: 5
      说明：

      你可以假设所给定的表达式都是有效的。
      请不要使用内置的库函数 eval。
      https://leetcode-cn.com/problems/basic-calculator-ii/
     */
    int calculate(string s) {
        stack<int> operands;
        stack<char> operators;
        size_t len = s.length();
        int i = 0;
        while (i < len) {
            if (isdigit(s[i])) {
                pair<int, int> result = nextOperand(s, i);
                operands.push(result.first);
                i = result.second;
            } else if (isspace(s[i])) {
                ++i;
                continue;
            } else { // 操作符 + - * /
                char curOp = s[i];
                if (!operators.empty()) { // 不第一个操作符
                    char preOp = operators.top();
                    while ( comparePriority(preOp, curOp) >= 0) {
                        operatorTopTwoOperands(operands, preOp);
                        operators.pop();
                        if (operators.size() > 0) {
                            preOp = operators.top();
                        } else {
                            break;
                        }
                    }
                }
                operators.push(curOp);
                ++i;
            }
        }
        while (!operators.empty()) {
            operatorTopTwoOperands(operands, operators.top());
            operators.pop();
        }
        
        return operands.top();
    }
    
    inline int operatorTopTwoOperands(stack<int> &operands, char &opt) {
        int right = operands.top();
        operands.pop();
        int left = operands.top();
        operands.pop();
        int result = 0;
        switch (opt) {
            case '+': {
                result = left + right;
                break;
            }
            case '-': {
                result = left - right;
                break;
            }
            case '*': {
                result = left * right;
                break;
            }
            case '/': {
                result = left / right;
                break;
            }
            default:
                break;
        }
        operands.push(result);
        
        return result;
    }
    
    /**
        大于 1， 小于-1， 相等0
     */
    inline int comparePriority(char &op1, char &op2) {
        if (op1 == op2) {
            return 0;
        }
        if (op1 == '+' || op1 == '-') {
            if (op2 == '+' || op2 == '-') {
                return 0;
            } else {
                return -1;
            }
        } else {
            if (op2 == '*' || op2 == '/') {
                return 0;
            } else {
                return 1;
            }
        }
    }
    
    inline pair<int, int> nextOperand(string &s, int begin) {
        int ret = 0;
        while (isdigit(s[begin])) {
            ret = ret * 10 + (int)(s[begin] - '0');
            ++begin;
        }
        return make_pair(ret, begin);
    }
    
    /**
     227. 基本计算器 II
     */
    int calculateIIV2(string s) {
        int ret = 0;
        stack<int> nums;
        size_t n = s.length();
        int i = 0;
        char lastOp = '+';
        while (i < n) {
            if (isspace(s[i])) {
                ++i;
                continue;
            }
            if (isdigit(s[i])) {
                int temp = 0;
                while (isdigit(s[i])) {
                    temp = temp * 10 + (int)(s[i] - '0');
                    ++i;
                }
                if (lastOp == '+') {
                    nums.push(temp);
                } else if (lastOp == '-') {
                    nums.push(-temp);
                } else {
                    int calResult = calculateTwoNums(lastOp, nums.top(), temp);
                    nums.pop();
                    nums.push(calResult);
                }
            } else {
                lastOp = s[i];
                ++i;
            }
        }
        while (!nums.empty()) {
            ret += nums.top();
            nums.pop();
        }
        
        return ret;
    }
    
    inline int calculateTwoNums(char &op, int &x, int &y) {
        if (op == '*') {
            return x * y;
        } else if (op == '/') {
            return x / y;
        } else if (op == '+') {
            return x + y;
        } else {
            return x - y;
        }
    }
};

#endif /* Algorithms4Chapter1_hpp */
