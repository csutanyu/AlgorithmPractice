//
//  LeetCodeCommons.hpp
//  AlgorithmPractice
//
//  Created by arvintan on 2021/1/11.
//  Copyright © 2021 arvintan. All rights reserved.
//

#ifndef LeetCodeCommons_hpp
#define LeetCodeCommons_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include <map>
#include <stack>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <string>
#include <sstream>
#include <iostream>
#include <iosfwd>
#include <float.h>

using namespace std;

/**
 1202. 交换字符串中的元素
 给你一个字符串 s，以及该字符串中的一些「索引对」数组 pairs，其中 pairs[i] = [a, b] 表示字符串中的两个索引（编号从 0 开始）。

 你可以 任意多次交换 在 pairs 中任意一对索引处的字符。

 返回在经过若干次交换后，s 可以变成的按字典序最小的字符串。

  

 示例 1:

 输入：s = "dcab", pairs = [[0,3],[1,2]]
 输出："bacd"
 解释：
 交换 s[0] 和 s[3], s = "bcad"
 交换 s[1] 和 s[2], s = "bacd"
 示例 2：

 输入：s = "dcab", pairs = [[0,3],[1,2],[0,2]]
 输出："abcd"
 解释：
 交换 s[0] 和 s[3], s = "bcad"
 交换 s[0] 和 s[2], s = "acbd"
 交换 s[1] 和 s[2], s = "abcd"
 示例 3：

 输入：s = "cba", pairs = [[0,1],[1,2]]
 输出："abc"
 解释：
 交换 s[0] 和 s[1], s = "bca"
 交换 s[1] 和 s[2], s = "bac"
 交换 s[0] 和 s[1], s = "abc"
  

 提示：

 1 <= s.length <= 10^5
 0 <= pairs.length <= 10^5
 0 <= pairs[i][0], pairs[i][1] < s.length
 s 中只含有小写英文字母
 通过次数15,312提交次数32,588

 */
class SmallestStringWithSwapsSolution {
public:
    string smallestStringWithSwaps(string s, vector<vector<int>>& pairs) {
        int len = (int)s.length();
        
        // 初始化并查集
        vector<int> parent(len, 0);
        for (int i = 0; i < len; ++i) {
            parent[i] = i;
        }
        
        // 构造并查集
        for (vector<int> &pair : pairs) {
            uf_union(parent, pair[0], pair[1]);
        }
         
        unordered_map<int/*index*/, vector<char>> hasMap;
        for (int i = 0; i < len; ++i) {
            int root = uf_find(parent, i);
            if (!hasMap.count(root)) {
                hasMap[root] = vector<char>();
            }
            hasMap[root].push_back(s[i]);
        }
        
        for (auto& [x, vec] : hasMap) {
            sort(vec.begin(), vec.end(), greater<int>());
        }

        ostringstream ostream;
        for (int i = 0; i < len; ++i) {
            int root = uf_find(parent, i);
            ostream << hasMap[root].back();
            hasMap[root].pop_back();
        }
        string ret = ostream.str();
        return ret;
    }
    
    string smallestStringWithSwapsV2(string s, vector<vector<int>>& pairs) {
        int len = (int)s.length();
        
        // 初始化并查集
        vector<int> parent(len, 0);
        for (int i = 0; i < len; ++i) {
            parent[i] = i;
        }
        
        // 构造并查集
        for (vector<int> &pair : pairs) {
            uf_union(parent, pair[0], pair[1]);
        }
         
        unordered_map<int/*index*/, priority_queue<char, vector<char>, greater<char> > > hasMap;
        for (int i = 0; i < len; ++i) {
            int root = uf_find(parent, i);
            if (!hasMap.count(root)) {
                hasMap[root] = priority_queue<char, vector<char>, greater<char> >();
            }
            hasMap[root].push(s[i]);
        }
        
        ostringstream ostream;
        for (int i = 0; i < len; ++i) {
            int root = uf_find(parent, i);
            ostream << hasMap[root].top();
            hasMap[root].pop();
        }
        string ret = ostream.str();
        return ret;
    }
    
    int uf_find(vector<int> &parent, int x) {
        while (parent[x] != x) {
            parent[x] = parent[parent[x]];
            x = parent[x];
        }
        return parent[x];
    }
    
    void uf_union(vector<int> &parent, int x, int y) {
        int rootx = uf_find(parent, x);
        int rooty = uf_find(parent, y);
        if (rootx == rooty) {
            return;
        }
        parent[rootx] = rooty;
    }
    
    bool uf_connected(vector<int> &parent, int x, int y) {
        return parent[x] == parent[y];
    }
    
    
    
    /**
     1722. 执行交换操作后的最小汉明距离
     给你两个整数数组 source 和 target ，长度都是 n 。还有一个数组 allowedSwaps ，其中每个 allowedSwaps[i] = [ai, bi] 表示你可以交换数组 source 中下标为 ai 和 bi（下标从 0 开始）的两个元素。注意，你可以按 任意 顺序 多次 交换一对特定下标指向的元素。

     相同长度的两个数组 source 和 target 间的 汉明距离 是元素不同的下标数量。形式上，其值等于满足 source[i] != target[i] （下标从 0 开始）的下标 i（0 <= i <= n-1）的数量。

     在对数组 source 执行 任意 数量的交换操作后，返回 source 和 target 间的 最小汉明距离 。

      

     示例 1：

     输入：source = [1,2,3,4], target = [2,1,4,5], allowedSwaps = [[0,1],[2,3]]
     输出：1
     解释：source 可以按下述方式转换：
     - 交换下标 0 和 1 指向的元素：source = [2,1,3,4]
     - 交换下标 2 和 3 指向的元素：source = [2,1,4,3]
     source 和 target 间的汉明距离是 1 ，二者有 1 处元素不同，在下标 3 。
     示例 2：

     输入：source = [1,2,3,4], target = [1,3,2,4], allowedSwaps = []
     输出：2
     解释：不能对 source 执行交换操作。
     source 和 target 间的汉明距离是 2 ，二者有 2 处元素不同，在下标 1 和下标 2 。
     示例 3：

     输入：source = [5,1,2,4,3], target = [1,5,4,2,3], allowedSwaps = [[0,4],[4,2],[1,3],[1,4]]
     输出：0
      

     提示：

     n == source.length == target.length
     1 <= n <= 105
     1 <= source[i], target[i] <= 105
     0 <= allowedSwaps.length <= 105
     allowedSwaps[i].length == 2
     0 <= ai, bi <= n - 1
     ai != bi
     通过次数2,068提交次数5,228
     https://leetcode-cn.com/problems/minimize-hamming-distance-after-swap-operations/
     */
    int minimumHammingDistance(vector<int>& source, vector<int>& target, vector<vector<int>>& allowedSwaps) {
        int len = (int)source.size();
        
        // 初始化并查集
        vector<int> parent(len, 0);
        for (int i = 0; i < len; ++i) {
            parent[i] = i;
        }
        
        // 构造并查集
        for (vector<int> &pair : allowedSwaps) {
            uf_union(parent, pair[0], pair[1]);
        }
         
        unordered_map<int/*index*/, unordered_multiset<int>> hasMap;
        for (int i = 0; i < len; ++i) {
            int rootIndex = uf_find(parent, i);
            if (hasMap.count(rootIndex) == 0) {
                hasMap[rootIndex] = unordered_multiset<int>();
            }
            hasMap[rootIndex].insert(source[i]);
        }
        
        int distanceCount = 0;
        for (int i = 0; i < len; ++i) {
            int rootIndex = uf_find(parent, i);
            auto& uset = hasMap[rootIndex];
            auto it = uset.find(target[i]);
            if (it == uset.end()) {
                ++distanceCount;
            } else {
                uset.erase(it);
            }
        }
        
        return distanceCount;
    }
};

/**
 895. 最大频率栈
 实现 FreqStack，模拟类似栈的数据结构的操作的一个类。

 FreqStack 有两个函数：

 push(int x)，将整数 x 推入栈中。
 pop()，它移除并返回栈中出现最频繁的元素。
 如果最频繁的元素不只一个，则移除并返回最接近栈顶的元素。
  

 示例：

 输入：
 ["FreqStack","push","push","push","push","push","push","pop","pop","pop","pop"],
 [[],[5],[7],[5],[7],[4],[5],[],[],[],[]]
 输出：[null,null,null,null,null,null,null,5,7,5,4]
 解释：
 执行六次 .push 操作后，栈自底向上为 [5,7,5,7,4,5]。然后：

 pop() -> 返回 5，因为 5 是出现频率最高的。
 栈变成 [5,7,5,7,4]。

 pop() -> 返回 7，因为 5 和 7 都是频率最高的，但 7 最接近栈顶。
 栈变成 [5,7,5,4]。

 pop() -> 返回 5 。
 栈变成 [5,7,4]。

 pop() -> 返回 4 。
 栈变成 [5,7]。
  

 提示：

 对 FreqStack.push(int x) 的调用中 0 <= x <= 10^9。
 如果栈的元素数目为零，则保证不会调用  FreqStack.pop()。
 单个测试样例中，对 FreqStack.push 的总调用次数不会超过 10000。
 单个测试样例中，对 FreqStack.pop 的总调用次数不会超过 10000。
 所有测试样例中，对 FreqStack.push 和 FreqStack.pop 的总调用次数不会超过 150000。
  

 通过次数3,664提交次数7,587
 https://leetcode-cn.com/problems/maximum-frequency-stack/
 */
class FreqStack {
    int maxFrequency;
    unordered_map<int, int> valueToFrequency;
    unordered_map<int, stack<int>> frequencyToValues;
public:
    FreqStack() {
        maxFrequency = 0;
    }
    
    void push(int x) {;
        int currentFreq = 0;
        if (valueToFrequency.find(x) != valueToFrequency.end()) {
            currentFreq = valueToFrequency[x];
        }
        
        valueToFrequency[x] = ++currentFreq;;
        
        if (frequencyToValues.find(currentFreq) == frequencyToValues.end()) {
            frequencyToValues[currentFreq] = stack<int>();
        }
        frequencyToValues[currentFreq].push(x);
        maxFrequency = max(maxFrequency, currentFreq);
    }
    
    int pop() {
//        if (maxFrequency == 0) {
//            return 0;
//        }
        
        stack<int> &stk = frequencyToValues[maxFrequency];
        int ret = stk.top();
        stk.pop();
        valueToFrequency[ret] = valueToFrequency[ret] - 1;
        if (stk.empty()) {
            --maxFrequency;
        }
        return ret;
    }
};



#endif /* LeetCodeCommons_hpp */
