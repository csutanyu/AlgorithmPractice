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
};


#endif /* LeetCodeCommons_hpp */
