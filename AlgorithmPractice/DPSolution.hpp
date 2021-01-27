//
//  DPSolution.hpp
//  AlgorithmPractice
//
//  Created by arvintan on 2020/12/22.
//  Copyright © 2020 arvintan. All rights reserved.
//

#ifndef DPSolution_hpp
#define DPSolution_hpp

#include "TreeSolution.hpp"
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

class DPSolution {
public:
    
    /**
     亚历克斯和李继续他们的石子游戏。许多堆石子 排成一行，每堆都有正整数颗石子 piles[i]。游戏以谁手中的石子最多来决出胜负。

     亚历克斯和李轮流进行，亚历克斯先开始。最初，M = 1。

     在每个玩家的回合中，该玩家可以拿走剩下的 前 X 堆的所有石子，其中 1 <= X <= 2M。然后，令 M = max(M, X)。

     游戏一直持续到所有石子都被拿走。

     假设亚历克斯和李都发挥出最佳水平，返回亚历克斯可以得到的最大数量的石头。

      

     示例：

     输入：piles = [2,7,9,4,4]
     输出：10
     解释：
     如果亚历克斯在开始时拿走一堆石子，李拿走两堆，接着亚历克斯也拿走两堆。在这种情况下，亚历克斯可以拿到 2 + 4 + 4 = 10 颗石子。
     如果亚历克斯在开始时拿走两堆石子，那么李就可以拿走剩下全部三堆石子。在这种情况下，亚历克斯可以拿到 2 + 7 = 9 颗石子。
     所以我们返回更大的 10。
      

     提示：

     1 <= piles.length <= 100
     1 <= piles[i] <= 10 ^ 4

     来源：力扣（LeetCode）
     链接：https://leetcode-cn.com/problems/stone-game-ii
     著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
     */
    int stoneGameII(vector<int>& piles) {
        int len = (int)piles.size();
        if (len == 0) {
            return 0;
        }
        
        vector<vector<int> > dp(len, vector<int>(len + 1, 0));
        int sum = 0;
        for (int i = len - 1; i >= 0; --i) { // 从后往前扫描
            sum += piles[i];
            for (int m = 1; m <= len; ++m) { // 每次将M从1到总零数进行计算
                if (len - i <= 2 * m) {
                    dp[i][m] = sum;
                } else {
                    for (int x = 1; x <= min(2 * m, len - 1) /* 先手可以获取的数量x为2m与剩余零数的较小值 */; ++x) {
                        dp[i][m] = max(dp[i][m], sum - dp[i + x][max(x, m)]);
                    }
                }
            }
            
            
        }
        
        return dp[0][1];
    }
    
    /**
     给定一组 N 人（编号为 1, 2, ..., N）， 我们想把每个人分进任意大小的两组。

     每个人都可能不喜欢其他人，那么他们不应该属于同一组。

     形式上，如果 dislikes[i] = [a, b]，表示不允许将编号为 a 和 b 的人归入同一组。

     当可以用这种方法将所有人分进两组时，返回 true；否则返回 false。

      

     示例 1：

     输入：N = 4, dislikes = [[1,2],[1,3],[2,4]]
     输出：true
     解释：group1 [1,4], group2 [2,3]
     示例 2：

     输入：N = 3, dislikes = [[1,2],[1,3],[2,3]]
     输出：false
     示例 3：

     输入：N = 5, dislikes = [[1,2],[2,3],[3,4],[4,5],[1,5]]
     输出：false
      

     提示：

     1 <= N <= 2000
     0 <= dislikes.length <= 10000
     dislikes[i].length == 2
     1 <= dislikes[i][j] <= N
     dislikes[i][0] < dislikes[i][1]
     对于 dislikes[i] == dislikes[j] 不存在 i != j

     来源：力扣（LeetCode）
     链接：https://leetcode-cn.com/problems/possible-bipartition
     著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
     */
    bool possibleBipartition(int N, vector<vector<int>>& dislikes) {
        //    [[1,2],[3,4],[5,6],[6,7],[8,9],[7,8]]
        vector<vector<int> > graph(N + 1, vector<int>());
        for (int i = 0; i < dislikes.size(); ++i) {
            vector<int> edge = dislikes[i];
            int firstPerson = edge[0];
            int secondPerson = edge[1];
            graph[firstPerson].push_back(secondPerson);
            graph[secondPerson].push_back(firstPerson);
        }
        
        vector<int> colorMap(N+1, 0);
        for (int i = 1; i <= N; ++i) {
            int color = colorMap[i];
            if (color != 0) {
                continue;
            }
            colorMap[i] = 1;
            queue<int> st;
            st.push(i);
            
            while (!st.empty()) {
                int p = st.front();
                st.pop();
                int currentColor = colorMap[p];
                vector<int> neighbers = graph[p];
                for (int j = 0; j < neighbers.size(); ++j) {
                    int n = neighbers[j];
                    if (colorMap[n] == currentColor) {
                        return false;
                    } else if (colorMap[n] == 0) {
                        colorMap[n] = -currentColor;
                        st.push(n);
                    }
                }
            }
        }
        return true;
    }
    
    bool possibleBipartition_unin_find(int N, vector<vector<int>>& dislikes) {
        vector<int> parent(2*N + 1, 0);
        for (int i = 0; i < 2*N + 1; ++i) {
            parent[i] = i;
        }
        
        for (int i = 0; i < dislikes.size(); ++i) {
            int firstPerson = dislikes[i][0];
            int secondPerson = dislikes[i][1];
            
            int firstLikeRoot = uf_find(parent, firstPerson);
            int secondLikeRoot = uf_find(parent, secondPerson);
            
            if (firstLikeRoot == secondLikeRoot) {
                return false;
            }
            
            int firstHateRoot = uf_find(parent, firstPerson + N);
            int secondHateRoot = uf_find(parent, secondPerson + N);
            
            parent[firstHateRoot] = secondLikeRoot;
            parent[secondHateRoot] = firstPerson;
        }
        return true;
    }
    
    int uf_find(vector<int> &parent, int x) {
        while (parent[x] != x) {
            parent[x] = parent[parent[x]];
            x = parent[x];
        }
        return x;
    }
    
    bool uf_union(vector<int> &parent, int x, int y) {
        int fx = uf_find(parent, x);
        int fy = uf_find(parent, y);
        if (fx != fy) {
            parent[fx] = fy;
        }
        return fx != fy;
    }
    
    bool uf_connected(vector<int> &parent, int x, int y) {
        return uf_find(parent, x) == uf_find(parent, y);
    }
    
    /**
     班上有 N 名学生。其中有些人是朋友，有些则不是。他们的友谊具有是传递性。如果已知 A 是 B 的朋友，B 是 C 的朋友，那么我们可以认为 A 也是 C 的朋友。所谓的朋友圈，是指所有朋友的集合。

     给定一个 N * N 的矩阵 M，表示班级中学生之间的朋友关系。如果M[i][j] = 1，表示已知第 i 个和 j 个学生互为朋友关系，否则为不知道。你必须输出所有学生中的已知的朋友圈总数。

      

     示例 1：

     输入：
     [[1,1,0],
      [1,1,0],
      [0,0,1]]
     输出：2
     解释：已知学生 0 和学生 1 互为朋友，他们在一个朋友圈。
     第2个学生自己在一个朋友圈。所以返回 2 。
     示例 2：

     输入：
     [[1,1,0],
      [1,1,1],
      [0,1,1]]
     输出：1
     解释：已知学生 0 和学生 1 互为朋友，学生 1 和学生 2 互为朋友，所以学生 0 和学生 2 也是朋友，所以他们三个在一个朋友圈，返回 1 。
      

     提示：

     1 <= N <= 200
     M[i][i] == 1
     M[i][j] == M[j][i]


     来源：力扣（LeetCode）
     链接：https://leetcode-cn.com/problems/friend-circles
     著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
     */
    int findCircleNum(vector<vector<int>>& M) {
        int N = (int)M.size();
        vector<int> parent(N, 0);
        for (int i = 0; i < N; ++i) {
            parent[i] = i;
        }
        
        int circles = N;
        for (int i = 0; i < N; ++i) {
            for (int j = i + 1; j < N; ++j) {
                if (M[i][j] == 1) {
                    if (uf_union(parent, i, j)) {
                        circles -= 1;
                    }
                }
                if (circles == 1) {
                    break;
                }
            }
            if (circles == 1) {
                break;
            }
        }
        return circles;
    }
    
    
    /**
     给定一个未排序的整数数组 nums ，找出数字连续的最长序列（不要求序列元素在原数组中连续）的长度。

      

     进阶：你可以设计并实现时间复杂度为 O(n) 的解决方案吗？

      

     示例 1：

     输入：nums = [100,4,200,1,3,2]
     输出：4
     解释：最长数字连续序列是 [1, 2, 3, 4]。它的长度为 4。
     示例 2：

     输入：nums = [0,3,7,2,5,8,4,6,0,1]
     输出：9
      

     提示：

     0 <= nums.length <= 104
     -109 <= nums[i] <= 109

     来源：力扣（LeetCode）
     链接：https://leetcode-cn.com/problems/longest-consecutive-sequence
     著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
     */
    
    int longestConsecutive(vector<int>& nums) {
        unordered_set<int> num_set;
        for (const int& num : nums) {
            num_set.insert(num);
        }

        int maxLength = 0;
        for (int &num : nums) {
            if (0 != num_set.count(num-1)) {
                continue;
            }
            int currentMaxLength = 0;
            int next = num;
            do {
                num_set.erase(next);
                currentMaxLength += 1;
                next += 1;
            } while (num_set.count(next));
            maxLength = max(maxLength, currentMaxLength);
            if (num_set.empty()) {
                break;
            }
        }
        return maxLength;
    }
    
    /**
     990. 等式方程的可满足性
     
     给定一个由表示变量之间关系的字符串方程组成的数组，每个字符串方程 equations[i] 的长度为 4，并采用两种不同的形式之一："a==b" 或 "a!=b"。在这里，a 和 b 是小写字母（不一定不同），表示单字母变量名。

     只有当可以将整数分配给变量名，以便满足所有给定的方程时才返回 true，否则返回 false。

      

     示例 1：

     输入：["a==b","b!=a"]
     输出：false
     解释：如果我们指定，a = 1 且 b = 1，那么可以满足第一个方程，但无法满足第二个方程。没有办法分配变量同时满足这两个方程。
     示例 2：

     输入：["b==a","a==b"]
     输出：true
     解释：我们可以指定 a = 1 且 b = 1 以满足满足这两个方程。
     示例 3：

     输入：["a==b","b==c","a==c"]
     输出：true
     示例 4：

     输入：["a==b","b!=c","c==a"]
     输出：false
     示例 5：

     输入：["c==c","b==d","x!=z"]
     输出：true
      

     提示：

     1 <= equations.length <= 500
     equations[i].length == 4
     equations[i][0] 和 equations[i][3] 是小写字母
     equations[i][1] 要么是 '='，要么是 '!'
     equations[i][2] 是 '='

     来源：力扣（LeetCode）
     链接：https://leetcode-cn.com/problems/satisfiability-of-equality-equations
     著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
     */
    
    bool equationsPossible(vector<string>& equations) {
        vector<int> parent(26, 0);
        for (int i = 0; i < 26; ++i) {
            parent[i] = i;
        }
        
        // 等式构建不并查集
        for (string &s : equations) {
            if (s[1] == '=') {
                int firstIndex = s[0] - 'a';
                int secondIndex = s[3] - 'a';
                uf_union(parent, firstIndex, secondIndex);
            }
        }
        
        // 查不等式，是否在同一个连通分支或者树中
        for (string &s : equations) {
            if (s[1] == '!') {
                int firstIndex = s[0] - 'a';
                int secondIndex = s[3] - 'a';
                if (uf_connected(parent, firstIndex, secondIndex)) {
                    return false;
                }
            }
        }
        return true;
    }
};

/**
 每年，政府都会公布一万个最常见的婴儿名字和它们出现的频率，也就是同名婴儿的数量。有些名字有多种拼法，例如，John 和 Jon 本质上是相同的名字，但被当成了两个名字公布出来。给定两个列表，一个是名字及对应的频率，另一个是本质相同的名字对。设计一个算法打印出每个真实名字的实际频率。注意，如果 John 和 Jon 是相同的，并且 Jon 和 Johnny 相同，则 John 与 Johnny 也相同，即它们有传递和对称性。

 在结果列表中，选择字典序最小的名字作为真实名字。

 示例：

 输入：names = ["John(15)","Jon(12)","Chris(13)","Kris(4)","Christopher(19)"], synonyms = ["(Jon,John)","(John,Johnny)","(Chris,Kris)","(Chris,Christopher)"]
 输出：["John(27)","Chris(36)"]
 提示：

 names.length <= 100000

 来源：力扣（LeetCode）
 链接：https://leetcode-cn.com/problems/baby-names-lcci
 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */
class TrulyMostPopularSolution {
public:
    vector<string> trulyMostPopular(vector<string>& names, vector<string>& synonyms) {
        vector<string> desc;
        unordered_map<string, string> parent;
        
        // 创建名字的并查集
        for (string &str : synonyms) {
            pair<string, string> namePairs = splitSynonymName(str);
            uf_union(parent, namePairs.first, namePairs.second);
        }
        unordered_map<string, int> nameCountsMap;
        for (string &name : names) {
            int len = (int)name.length();
            
            // 查找到名字与数字的分割'('
            int bracketBegin = 0;
            for (int i = len - 2/*最后一个')'*/; i > 0; --i) {
                if (name[i] == '(') {
                    bracketBegin = i;
                    break;
                }
            }
            // 真实名字
            string realName = name.substr(0, bracketBegin);
            // 名字频率字串
            string countStr = name.substr(bracketBegin + 1, len - bracketBegin - 2);
            // 名字频率
            int nameCount = std::stoi(countStr);
            // 同义名字的频率只以其根为结果进行存储
            string &rootName = uf_find(parent, realName);
            
            // 频率累加
            if (0 != nameCountsMap.count(rootName)) {
                nameCountsMap[rootName] = nameCount + nameCountsMap[rootName];
            } else {
                nameCountsMap[rootName] = nameCount;
            }
        }
        
        // dump名字频率率字典为字串
        std::ostringstream stringStream;
        for (auto itr = nameCountsMap.begin(); itr != nameCountsMap.end(); ++itr) {
            stringStream << itr->first;
            stringStream << "(";
            stringStream << itr->second;
            stringStream << ")";
            desc.push_back(stringStream.str());
            
            // clear
            stringStream.clear();
            stringStream.str("");
        }
        
        return desc;
    }
    
    // 划分同义名字对
    inline pair<string, string> splitSynonymName(string &x) {
        size_t len = x.length();
        int commaIndex = 0;
        for (int i = 1/*第一个字符是'('*/; i < len - 1 /*最后一个字符为')'*/; ++i) {
            if (x[i] == ',') {
                commaIndex = i;
                break;
            }
        }
        string name1 = x.substr(1/*首'('*/, commaIndex - 1);
        string name2 = x.substr(commaIndex + 1, len - (commaIndex + 1) - 1/*末尾'('*/ );
        pair<string, string> names(name1, name2);
        return names;
    }
    
    string& uf_find(unordered_map<string, string> &parent, string &x) {
        if ( 0 == parent.count(x) ) {
            parent[x] = x;
            return x;
        }
        
        while ( parent.count(x) && parent[x].compare(x) != 0 ) {
            parent[x] = parent[parent[x]];
            x = parent[x];
        }
        
        return x;
    }
    
    bool uf_union(unordered_map<string, string> &parent, string &x, string &y) {
        string &xRoot = uf_find(parent, x);
        string &yRoot = uf_find(parent, y);
        int cresult = xRoot.compare(yRoot);
        if (cresult == 0) {
            return false;
        }
        
        if (cresult < 0) {
            parent[yRoot] = xRoot;
        } else {
            parent[xRoot] = yRoot;
        }
        
        return true;
    }
    
    bool uf_connected(unordered_map<string, string> &parent, string &x, string &y) {
        string &xRoot = parent[x];
        string &yRoot = parent[y];
        
        return 0 == xRoot.compare(yRoot);
    }
};

/**
 198. 打家劫舍
 
 与 面试题 17.16. 按摩师 https://leetcode-cn.com/problems/the-masseuse-lcci/ 一样
 
 你是一个专业的小偷，计划偷窃沿街的房屋。每间房内都藏有一定的现金，影响你偷窃的唯一制约因素就是相邻的房屋装有相互连通的防盗系统，如果两间相邻的房屋在同一晚上被小偷闯入，系统会自动报警。

 给定一个代表每个房屋存放金额的非负整数数组，计算你 不触动警报装置的情况下 ，一夜之内能够偷窃到的最高金额。

  

 示例 1：

 输入：[1,2,3,1]
 输出：4
 解释：偷窃 1 号房屋 (金额 = 1) ，然后偷窃 3 号房屋 (金额 = 3)。
      偷窃到的最高金额 = 1 + 3 = 4 。
 示例 2：

 输入：[2,7,9,3,1]
 输出：12
 解释：偷窃 1 号房屋 (金额 = 2), 偷窃 3 号房屋 (金额 = 9)，接着偷窃 5 号房屋 (金额 = 1)。
      偷窃到的最高金额 = 2 + 9 + 1 = 12 。
  

 提示：

 0 <= nums.length <= 100
 0 <= nums[i] <= 400

 来源：力扣（LeetCode）
 链接：https://leetcode-cn.com/problems/house-robber
 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */
class Robber {
public:
    int rob(vector<int>& nums) {
        int len = (int)nums.size();
        if (0 == len) return 0;
        if (1 == len) return nums[0];
        
        int preSum = nums[0];
        int curSum = max(nums[0], nums[1]);
        
        for (int i = 2; i < len; ++i) {
            int tempCur = max((preSum + nums[i]), curSum);
            preSum = curSum;
            curSum = tempCur;
        }
        return curSum;
    }
    
    
    /**
     213. 打家劫舍 II
     
     你是一个专业的小偷，计划偷窃沿街的房屋，每间房内都藏有一定的现金。这个地方所有的房屋都 围成一圈 ，这意味着第一个房屋和最后一个房屋是紧挨着的。同时，相邻的房屋装有相互连通的防盗系统，如果两间相邻的房屋在同一晚上被小偷闯入，系统会自动报警 。

     给定一个代表每个房屋存放金额的非负整数数组，计算你 在不触动警报装置的情况下 ，能够偷窃到的最高金额。

      

     示例 1：

     输入：nums = [2,3,2]
     输出：3
     解释：你不能先偷窃 1 号房屋（金额 = 2），然后偷窃 3 号房屋（金额 = 2）, 因为他们是相邻的。
     示例 2：

     输入：nums = [1,2,3,1]
     输出：4
     解释：你可以先偷窃 1 号房屋（金额 = 1），然后偷窃 3 号房屋（金额 = 3）。
          偷窃到的最高金额 = 1 + 3 = 4 。
     示例 3：

     输入：nums = [0]
     输出：0
      

     提示：

     1 <= nums.length <= 100
     0 <= nums[i] <= 1000


     来源：力扣（LeetCode）
     链接：https://leetcode-cn.com/problems/house-robber-ii
     著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
     */
    int rob2(vector<int>& nums) {
        int len = (int)nums.size();
        if (0 == len) return 0;
        if (1 == len) return nums[0];
        
        int noFirst = doRob2(nums, 1, len - 1); /*第1间不偷，从第2间开始**/
        int selectFirst = nums[0] + doRob2(nums, 2/*从第3间开始*/, len - 3/*减去第1间及与第1间相邻的末尾1间，及下一间，共3间*/);
        return max(noFirst, selectFirst);
    }
    
    int doRob2(vector<int>& nums, int pos, int len) {
        if (len <= 0) return 0;
        if (len == 1) return nums[pos];

        int pre = nums[pos];
        int cur = max(nums[pos], nums[pos + 1]);
        
        for (int index = pos + 2; index < pos + len; ++index) {
            int temp = max(cur, nums[index] + pre);
            pre = cur;
            cur = temp;
        }
        return cur;
    }
};

/**
 337. 打家劫舍 III
 在上次打劫完一条街道之后和一圈房屋后，小偷又发现了一个新的可行窃的地区。这个地区只有一个入口，我们称之为“根”。 除了“根”之外，每栋房子有且只有一个“父“房子与之相连。一番侦察之后，聪明的小偷意识到“这个地方的所有房屋的排列类似于一棵二叉树”。 如果两个直接相连的房子在同一天晚上被打劫，房屋将自动报警。

 计算在不触动警报的情况下，小偷一晚能够盗取的最高金额。

 示例 1:

 输入: [3,2,3,null,3,null,1]

      3
     / \
    2   3
     \   \
      3   1

 输出: 7
 解释: 小偷一晚能够盗取的最高金额 = 3 + 3 + 1 = 7.
 示例 2:

 输入: [3,4,5,1,3,null,1]

      3
     / \
    4   5
   / \   \
  1   3   1

 输出: 9
 解释: 小偷一晚能够盗取的最高金额 = 4 + 5 = 9.


 来源：力扣（LeetCode）
 链接：https://leetcode-cn.com/problems/house-robber-iii
 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */

class RobberSolution3 {
    unordered_map <TreeNode*, int> dp;
public:
    int rob(TreeNode* root) {
        if (root == NULL) return 0;
        
        if (root->left == NULL && root->right == NULL) {
            dp[root] = root->val;
            return root->val;
        }
        
        if (dp.count(root)) {
            return dp[root];
        }
        
        int leftGrandsons = 0;
        if (root->left != NULL) {
            leftGrandsons = rob(root->left->left) + rob(root->left->right);
        }
        int rightGradsons = 0;
        if (root->right != NULL) {
            rightGradsons = rob(root->right->left) + rob(root->right->right);
        }
        
        int selectRoot = leftGrandsons + rightGradsons + root->val;
        int noRoot = rob(root->left) + rob(root->right);
        
        int res = max(noRoot, selectRoot);
        dp[root] = res;

        return res;
    }
};

/**
 152. 乘积最大子数组
 给你一个整数数组 nums ，请你找出数组中乘积最大的连续子数组（该子数组中至少包含一个数字），并返回该子数组所对应的乘积。

  

 示例 1:

 输入: [2,3,-2,4]
 输出: 6
 解释: 子数组 [2,3] 有最大乘积 6。
 示例 2:

 输入: [-2,0,-1]
 输出: 0
 解释: 结果不能为 2, 因为 [-2,-1] 不是子数组。
 */
class MaxProduct {
    
public:
    int maxProduct(vector<int>& nums) {
        int size = (int)nums.size();
        if (size == 0) return 0;
        vector<pair<int, int>> dp(size, pair<int, int>(0, 0));
        dp[size - 1].first = nums[size - 1];
        dp[size - 1].second = nums[size - 1];
        
        int res = nums[size - 1];
        for (int i = size - 2; i >= 0; --i) {
            // 与最大值乘积
            int calFirst = nums[i] * dp[i+1].first;
            
            // 与最小值乘积
            int calSecond = nums[i] * dp[i+1].second;
            
            int curMax = max(nums[i], max(calFirst, calSecond));
            int curMin = min(nums[i], min(calFirst, calSecond));
            dp[i].first = curMax;
            dp[i].second = curMin;
            
            res = max(res, curMax);
        }
        return res;
    }
};

/**
 53. 最大子序和
 给定一个整数数组 nums ，找到一个具有最大和的连续子数组（子数组最少包含一个元素），返回其最大和。

 示例:

 输入: [-2,1,-3,4,-1,2,1,-5,4]
 输出: 6
 解释: 连续子数组 [4,-1,2,1] 的和最大，为 6。
 进阶:

 如果你已经实现复杂度为 O(n) 的解法，尝试使用更为精妙的分治法求解。
 */
class MaxSubArraySolution {
public:
    int maxSubArray(vector<int>& nums) {
        int size = (int)nums.size();
        if (size == 0) return 0;
        int curMax = nums[0];
        int theMax = nums[0];
        for (int i = 1; i < size; ++i) {
            curMax = max(curMax + nums[i], nums[i]);
            theMax = max(theMax, curMax);
        }
        return theMax;
    }
};


class MaxProfitSolution {
public:
    /**
     121. 买卖股票的最佳时机
     给定一个数组，它的第 i 个元素是一支给定股票第 i 天的价格。

     如果你最多只允许完成一笔交易（即买入和卖出一支股票一次），设计一个算法来计算你所能获取的最大利润。

     注意：你不能在买入股票前卖出股票。

      

     示例 1:

     输入: [7,1,5,3,6,4]
     输出: 5
     解释: 在第 2 天（股票价格 = 1）的时候买入，在第 5 天（股票价格 = 6）的时候卖出，最大利润 = 6-1 = 5 。
          注意利润不能是 7-1 = 6, 因为卖出价格需要大于买入价格；同时，你不能在买入前卖出股票。
     示例 2:

     输入: [7,6,4,3,1]
     输出: 0
     解释: 在这种情况下, 没有交易完成, 所以最大利润为 0。
     */
    int maxProfit(vector<int>& prices) {
        if (prices.size() == 0) return 0;
        
        int minNum = prices[0];
        int theMax = 0;
        for (int i = 1; i < prices.size(); ++i) {
            theMax = max(theMax, (prices[i] - minNum));
            minNum = min(minNum, prices[i]);
        }
        return theMax;
    }
    
    /**
     122. 买卖股票的最佳时机 II
     给定一个数组，它的第 i 个元素是一支给定股票第 i 天的价格。

     设计一个算法来计算你所能获取的最大利润。你可以尽可能地完成更多的交易（多次买卖一支股票）。

     注意：你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。

      

     示例 1:

     输入: [7,1,5,3,6,4]
     输出: 7
     解释: 在第 2 天（股票价格 = 1）的时候买入，在第 3 天（股票价格 = 5）的时候卖出, 这笔交易所能获得利润 = 5-1 = 4 。
          随后，在第 4 天（股票价格 = 3）的时候买入，在第 5 天（股票价格 = 6）的时候卖出, 这笔交易所能获得利润 = 6-3 = 3 。
     示例 2:

     输入: [1,2,3,4,5]
     输出: 4
     解释: 在第 1 天（股票价格 = 1）的时候买入，在第 5 天 （股票价格 = 5）的时候卖出, 这笔交易所能获得利润 = 5-1 = 4 。
          注意你不能在第 1 天和第 2 天接连购买股票，之后再将它们卖出。
          因为这样属于同时参与了多笔交易，你必须在再次购买前出售掉之前的股票。
     示例 3:

     输入: [7,6,4,3,1]
     输出: 0
     解释: 在这种情况下, 没有交易完成, 所以最大利润为 0。
      

     提示：

     1 <= prices.length <= 3 * 10 ^ 4
     0 <= prices[i] <= 10 ^ 4

     */
    
    int maxProfit_II(vector<int>& prices) {
        if (prices.size() <= 1) return 0;
        
        /**
         first 无股票，second有股票
         */
        vector<pair<int, int>> dp(prices.size(), pair<int, int>(0, 0));
        dp[0].first = 0;
        dp[0].second = -prices[0];
        
        for (int i = 1; i < prices.size(); ++i) {
            dp[i].first = max(dp[i-1].second + prices[i], dp[i-1].first);
            dp[i].second = max(dp[i-1].first - prices[i], dp[i-1].second);
        }
        
        return dp[prices.size() - 1].first;
    }
    
    /**
     123. 买卖股票的最佳时机 III
     给定一个数组，它的第 i 个元素是一支给定的股票在第 i 天的价格。

     设计一个算法来计算你所能获取的最大利润。你最多可以完成 两笔 交易。

     注意: 你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。

     示例 1:

     输入: [3,3,5,0,0,3,1,4]
     输出: 6
     解释: 在第 4 天（股票价格 = 0）的时候买入，在第 6 天（股票价格 = 3）的时候卖出，这笔交易所能获得利润 = 3-0 = 3 。
          随后，在第 7 天（股票价格 = 1）的时候买入，在第 8 天 （股票价格 = 4）的时候卖出，这笔交易所能获得利润 = 4-1 = 3 。
     示例 2:

     输入: [1,2,3,4,5]
     输出: 4
     解释: 在第 1 天（股票价格 = 1）的时候买入，在第 5 天 （股票价格 = 5）的时候卖出, 这笔交易所能获得利润 = 5-1 = 4 。
          注意你不能在第 1 天和第 2 天接连购买股票，之后再将它们卖出。
          因为这样属于同时参与了多笔交易，你必须在再次购买前出售掉之前的股票。
     示例 3:

     输入: [7,6,4,3,1]
     输出: 0
     解释: 在这个情况下, 没有交易完成, 所以最大利润为 0。
     */
    // 此方法左右两个区间，基于股票最大收益2的方法
    int maxProfit_III(vector<int>& prices) {
        if (prices.size() < 2) return 0;
        
        int curLeftMinElement = INT16_MAX;
        int curLeftMaxProfit = 0;
        vector<int> leftSection(prices.size(), 0);
        for (int i = 0; i < prices.size(); ++i) {
            curLeftMaxProfit = max(curLeftMaxProfit, prices[i] - curLeftMinElement);
            leftSection[i] = curLeftMaxProfit;
            curLeftMinElement = min(curLeftMinElement, prices[i]);
        }
        
        int curRightMaxElement = INT16_MIN;
        int curRightMaxProfit = 0;
        vector<int> rightSection(prices.size(), 0);
        for (int i = (int)prices.size() - 1; i >= 0; --i) {
            curRightMaxProfit = max(curRightMaxProfit, curRightMaxElement - prices[i]);
            rightSection[i] = curRightMaxProfit;
            curRightMaxElement = max(curRightMaxElement, prices[i]);
        }
        
        // 以下可以放到第二次求右区间遍历过程中，并把rightSection去掉
        int maxTotal = 0;
        for (int i = 0; i < prices.size(); ++i) {
            maxTotal = max(maxTotal, leftSection[i] + rightSection[i]);
        }
        
        return maxTotal;
    }
    /**
     188. 买卖股票的最佳时机 IV
     给定一个整数数组 prices ，它的第 i 个元素 prices[i] 是一支给定的股票在第 i 天的价格。

     设计一个算法来计算你所能获取的最大利润。你最多可以完成 k 笔交易。

     注意：你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。

      

     示例 1：

     输入：k = 2, prices = [2,4,1]
     输出：2
     解释：在第 1 天 (股票价格 = 2) 的时候买入，在第 2 天 (股票价格 = 4) 的时候卖出，这笔交易所能获得利润 = 4-2 = 2 。
     示例 2：

     输入：k = 2, prices = [3,2,6,5,0,3]
     输出：7
     解释：在第 2 天 (股票价格 = 2) 的时候买入，在第 3 天 (股票价格 = 6) 的时候卖出, 这笔交易所能获得利润 = 6-2 = 4 。
          随后，在第 5 天 (股票价格 = 0) 的时候买入，在第 6 天 (股票价格 = 3) 的时候卖出, 这笔交易所能获得利润 = 3-0 = 3 。
      

     提示：

     0 <= k <= 109
     0 <= prices.length <= 1000
     0 <= prices[i] <= 1000
     */
    int maxProfit_IV(int k, vector<int>& prices) {
        if (prices.size() < 2) {
            return 0;
        }
        
        vector<int> increaseSections;
        
        int preMinIndex = 0;
        int preTrend = 0; // 0： 初始 & 不变，1：递增趋势 -1：递减趋势
        
        for (int i = 1; i < prices.size(); ++i) {
            int newTrend = prices[i] == prices[i-1] ? 0 : (prices[i] > prices[i-1] ? 1 : -1);
            if (newTrend == 0) { // 趋势不变
                continue;
            }
            
            if (newTrend != preTrend) {
                if (newTrend == -1) { // 上升变下降
                    // 0到-1下降，或者1到-1，由上升到下降
                    int diff = prices[i-1] - prices[preMinIndex];
                    if (i - 1 > preMinIndex && diff > 0) {
                        increaseSections.push_back(diff);
                    }
                    preMinIndex = i;
                } else { // 下降变上升
                    preMinIndex = i - 1;
                    if (i == prices.size() - 1) { // 到最后一个元素为上升趋势
                        increaseSections.push_back( prices[i] - prices[preMinIndex] );
                    }
                }
                preTrend = newTrend;
            } else { // 趋势相同
                if (newTrend == -1) {
                    preMinIndex = i;
                }
                if (newTrend == 1 && i == prices.size() - 1) { // 到最后一个元素为上升趋势
                    increaseSections.push_back( prices[i] - prices[preMinIndex] );
                }
            }
        }
        
        sort(increaseSections.begin(), increaseSections.end(), greater<int>());
        
        int sum = 0;
        for (int i = 0; i < k && i < increaseSections.size(); ++i) {
            sum += increaseSections[i];
        }
        return  sum;
    }
    
    
    /**
     给你一个字符串 s 和一个字符规律 p，请你来实现一个支持 '.' 和 '*' 的正则表达式匹配。

     '.' 匹配任意单个字符
     '*' 匹配零个或多个前面的那一个元素
     所谓匹配，是要涵盖 整个 字符串 s的，而不是部分字符串。

      
     示例 1：

     输入：s = "aa" p = "a"
     输出：false
     解释："a" 无法匹配 "aa" 整个字符串。
     示例 2:

     输入：s = "aa" p = "a*"
     输出：true
     解释：因为 '*' 代表可以匹配零个或多个前面的那一个元素, 在这里前面的元素就是 'a'。因此，字符串 "aa" 可被视为 'a' 重复了一次。
     示例 3：

     输入：s = "ab" p = ".*"
     输出：true
     解释：".*" 表示可匹配零个或多个（'*'）任意字符（'.'）。
     示例 4：

     输入：s = "aab" p = "c*a*b"
     输出：true
     解释：因为 '*' 表示零个或多个，这里 'c' 为 0 个, 'a' 被重复一次。因此可以匹配字符串 "aab"。
     示例 5：

     输入：s = "mississippi" p = "mis*is*p*."
     输出：false
      

     提示：

     0 <= s.length <= 20
     0 <= p.length <= 30
     s 可能为空，且只包含从 a-z 的小写字母。
     p 可能为空，且只包含从 a-z 的小写字母，以及字符 . 和 *。
     保证每次出现字符 * 时，前面都匹配到有效的字符
     通过次数134,265提交次数439,028

     来源：力扣（LeetCode）
     链接：https://leetcode-cn.com/problems/regular-expression-matching
     著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
     */
    bool regexMatch(string s, string p) {
        return regexMatchRecursion(s, p);
    }
    
    bool regexMatchRecursion(string &s, string &p) {
        size_t lenS = s.length();
        size_t lenP = p.length();
        if (lenP == 0) {
            return lenS == 0;
        }
        
        bool firstMatch = lenS != 0 && (s[0] == p[0] || p[0] == '.');
        
        if (p.length() > 1 && p[1] == '*') {
//            return isMatch(s, p.substr(2)) /* skip x* completely */ ||
//                            (firstMatch && isMatch(s.substr(1), p));
            string subP = p.substr(2, lenP - 2);
            bool skipStarMatch = regexMatchRecursion(s, subP);
            bool starMoreTimes = false;
            if (firstMatch) {
                string subS = s.substr(1, lenS - 1);
                starMoreTimes = regexMatchRecursion(subS, p);
            }
            return skipStarMatch || starMoreTimes;
        } else {
            if (!firstMatch) return false;
            
            string subS = lenS > 0 ? s.substr(1, lenS - 1) : "";
            string subP = lenP > 0 ? p.substr(1, lenP - 1) : "";
            
            return regexMatchRecursion(subS, subP);
        }
    }
};

/**
 给你一个变量对数组 equations 和一个实数值数组 values 作为已知条件，其中 equations[i] = [Ai, Bi] 和 values[i] 共同表示等式 Ai / Bi = values[i] 。每个 Ai 或 Bi 是一个表示单个变量的字符串。

 另有一些以数组 queries 表示的问题，其中 queries[j] = [Cj, Dj] 表示第 j 个问题，请你根据已知条件找出 Cj / Dj = ? 的结果作为答案。

 返回 所有问题的答案 。如果存在某个无法确定的答案，则用 -1.0 替代这个答案。

  

 注意：输入总是有效的。你可以假设除法运算中不会出现除数为 0 的情况，且不存在任何矛盾的结果。

  

 示例 1：

 输入：equations = [["a","b"],["b","c"]], values = [2.0,3.0], queries = [["a","c"],["b","a"],["a","e"],["a","a"],["x","x"]]
 输出：[6.00000,0.50000,-1.00000,1.00000,-1.00000]
 解释：
 条件：a / b = 2.0, b / c = 3.0
 问题：a / c = ?, b / a = ?, a / e = ?, a / a = ?, x / x = ?
 结果：[6.0, 0.5, -1.0, 1.0, -1.0 ]
 示例 2：

 输入：equations = [["a","b"],["b","c"],["bc","cd"]], values = [1.5,2.5,5.0], queries = [["a","c"],["c","b"],["bc","cd"],["cd","bc"]]
 输出：[3.75000,0.40000,5.00000,0.20000]
 示例 3：

 输入：equations = [["a","b"]], values = [0.5], queries = [["a","b"],["b","a"],["a","c"],["x","y"]]
 输出：[0.50000,2.00000,-1.00000,-1.00000]
  

 提示：

 1 <= equations.length <= 20
 equations[i].length == 2
 1 <= Ai.length, Bi.length <= 5
 values.length == equations.length
 0.0 < values[i] <= 20.0
 1 <= queries.length <= 20
 queries[i].length == 2
 1 <= Cj.length, Dj.length <= 5
 Ai, Bi, Cj, Dj 由小写英文字母与数字组成


 来源：力扣（LeetCode）
 链接：https://leetcode-cn.com/problems/evaluate-division
 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */
class LeatCode399Division {
public:

    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
        /**
         构造并查集
         */
        UnionFind uf;
        for (int i = 0; i < equations.size(); ++i) {
            vector<string> equation = equations[i];
            uf.unite(equation[0], equation[1], values[i]);
        }

        vector<double> ret(queries.size(), -1.0);
        for (int i = 0; i < queries.size(); ++i) {
            vector<string> equation = queries[i];
            string left = equation[0];
            string right = equation[1];
            
            if (!uf.hasKey(left) || !uf.hasKey(right)) {
                ret[i] = -1.0;
                continue;;
            }
            
            ret[i] = uf.connected(left, right);
        }
        return ret;
    }
    
    class UnionFind {
    public:
        typedef unordered_map<string, string> ParentType;
        typedef unordered_map<string, double> WeightType;
        
        ParentType parents;
        WeightType weights;
        
        bool hasKey(string &k) {
            return parents.count(k) > 0;
        }
        
        string find(string &x) {
            if (parents.count(x) == 0) { // 还没有在并查集中
                parents[x] = x;
                weights[x] = 1.0;
            }
            /**
             自己用栈，比递归要耗时长，在leetcode中超时
             */
#if 0
            stack<string> stk;
            string temp = x;
            while (parents[temp].compare(temp) != 0) {
                stk.push(temp);
                temp = parents[temp];
            }
            while (!stk.empty()) {
                temp = stk.top();
                string &originParent = parents[temp];
                parents[temp] = parents[originParent];
                weights[temp] = weights[temp] * weights[originParent];
            }
#else
            // 递归
            if (parents[x].compare(x) != 0) {
                string originParent = parents[x];
                string root = find(originParent);
                parents[x] = root;
                weights[x] = weights[originParent] * weights[x];
            }
#endif
            return parents[x];
        }
        
        void unite(string &x, string &y, double value) {
            string rootx = find(x);
            string rooty = find(y);
            if (rootx == rooty) {
                return;
            }
            
            parents[rootx] = rooty;
            weights[rootx] = (weights[y] * value) / weights[x];
            
            // 这里明显x的parent不是根，则将其指向根
            // 根据find的定义，rootx就是x的parent, 以下的if语句应该总是成立才对，但是如果不要if语句，则leetcode会判为错误，不知为何？
            if (parents[x].compare(rootx) == 0) {
                parents[x] = rooty;
                weights[x] = weights[x] * weights[rootx];
            }
        }
        
        double connected(string &x, string &y) {
            string rootx = find(x);
            string rooty = find(y);
            if (rootx != rooty) {
                return -1;
            }
            return weights[x] / weights[y];
        }
    };
    
    vector<double> calcEquationWFS(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
        unordered_map<string, int> variables;
        int nvars = 0;
        size_t n = equations.size();
        for (size_t i = 0; i < n; ++i) {
            string &var1 = equations[i][0];
            string &var2 = equations[i][1];
            if (variables.find(var1) == variables.end()) {
                variables[var1] = nvars++;
            }
            if (variables.find(var2) == variables.end()) {
                variables[var2] = nvars++;
            }
        }
        
        vector<vector<pair<int, double>>> edges(nvars);
        for (size_t i = 0; i < n; ++i) {
            int var1 = variables[equations[i][0]];
            int var2 = variables[equations[i][1]];
            edges[var1].push_back(make_pair(var2, values[i]));
            edges[var2].push_back(make_pair(var1, (1.0/values[i])));
        }
        
        n = queries.size();
        vector<double> ret(n, -1);
        for (size_t i = 0; i < n; ++i) {
            string &varName1 = queries[i][0];
            string &varName2 = queries[i][1];
            if (variables.find(varName1) == variables.end() || variables.find(varName2) == variables.end()) {
                ret[i] = -1;
                continue;;
            }
            
            int var1 = variables[varName1];
            int var2 = variables[varName2];
            if (var1 == var2) {
                ret[i] = 1.0;
                continue;
            }
            
            queue<int> points;
            points.push(var1);
            vector<double> weights(nvars, -1); // 以当前var1点开始，到所有其他点连通点的累积权值
            weights[var1] = 1.0; // 自己到自己的可能会为1.0
            while (!points.empty() && weights[var2] < 0) {
                int current =  points.front();
                points.pop();
                for (const pair<int, double> &adjoin : edges[current]) {
                    if (weights[adjoin.first] < 0) { // 从当前var1出发没有访问过
                        weights[adjoin.first] = adjoin.second * weights[current];
                        points.push(adjoin.second);
                    }
                }
            }
            ret[i] = weights[var2];
        }
        return ret;
    }
    
    vector<double> calcEquationFloyd(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
        size_t n = equations.size();
        int nvars = 0;
        unordered_map<string, int> variables;
        for (int i = 0; i < n; ++i) {
            string &va = equations[i][0];
            string &vb = equations[i][1];
            if (variables.find(va) == variables.end()) {
                variables[va] = nvars++;
            }
            if (variables.find(vb) == variables.end()) {
                variables[vb] = nvars++;
            }
        }
        
        vector<vector<double>> graph(nvars, vector<double>(nvars, -1.0));
        for (int i = 0; i < n; ++i) {
            int va = variables[equations[i][0]];
            int vb = variables[equations[i][1]];
            graph[va][vb] = values[i];
            graph[vb][va] = 1.0/values[i];
        }
        
        for (int k = 0; k < nvars; ++k) {
            for (int i = 0; i < nvars; ++i) {
                for (int j = 0; j < nvars; ++j) {
                    if (graph[i][k] > 0 && graph[k][j] > 0) {
                        graph[i][j] = graph[i][k] * graph[k][j];
                    }
                }
            }
        }
        
        vector<double> ret;
        
        for (const auto& q: queries) {
            double result = -1;
            if (variables.find(q[0]) != variables.end() && variables.find(q[1]) != variables.end()) {
                int va = variables[q[0]];
                int vb = variables[q[1]];
                if (graph[va][vb] > 0) {
                    result = graph[va][vb];
                }
            }
            ret.push_back(result);
        }
        return ret;
    }
};

/**
 228. 汇总区间
 给定一个无重复元素的有序整数数组 nums 。

 返回 恰好覆盖数组中所有数字 的 最小有序 区间范围列表。也就是说，nums 的每个元素都恰好被某个区间范围所覆盖，并且不存在属于某个范围但不属于 nums 的数字 x 。

 列表中的每个区间范围 [a,b] 应该按如下格式输出：

 "a->b" ，如果 a != b
 "a" ，如果 a == b
  

 示例 1：

 输入：nums = [0,1,2,4,5,7]
 输出：["0->2","4->5","7"]
 解释：区间范围是：
 [0,2] --> "0->2"
 [4,5] --> "4->5"
 [7,7] --> "7"
 示例 2：

 输入：nums = [0,2,3,4,6,8,9]
 输出：["0","2->4","6","8->9"]
 解释：区间范围是：
 [0,0] --> "0"
 [2,4] --> "2->4"
 [6,6] --> "6"
 [8,9] --> "8->9"
 示例 3：

 输入：nums = []
 输出：[]
 示例 4：

 输入：nums = [-1]
 输出：["-1"]
 示例 5：

 输入：nums = [0]
 输出：["0"]
 https://leetcode-cn.com/problems/summary-ranges/
 */
class SummaryRangesSolution {
public:
    vector<string> summaryRanges(vector<int>& nums) {
        vector<string> ret;
        size_t n = nums.size();
        int i = 0;
        while (i < n) {
            int low = i;
            while (i+1 < n && nums[i+1] == nums[i] + 1) {
                ++i;
            }
            int high = i;
            string temp = to_string(nums[low]);
            if (low < high) {
                temp.append("->");
                temp.append(to_string(nums[high]));
            }
            ret.push_back(move(temp));
            
            ++i; // 不要忘记
        }
        
        return ret;
    }
};

/**
 1480. 一维数组的动态和
 给你一个数组 nums 。数组「动态和」的计算公式为：runningSum[i] = sum(nums[0]…nums[i]) 。

 请返回 nums 的动态和。

  

 示例 1：

 输入：nums = [1,2,3,4]
 输出：[1,3,6,10]
 解释：动态和计算过程为 [1, 1+2, 1+2+3, 1+2+3+4] 。
 示例 2：

 输入：nums = [1,1,1,1,1]
 输出：[1,2,3,4,5]
 解释：动态和计算过程为 [1, 1+1, 1+1+1, 1+1+1+1, 1+1+1+1+1] 。
 示例 3：

 输入：nums = [3,1,2,10,1]
 输出：[3,4,6,16,17]
  

 提示：

 1 <= nums.length <= 1000
 -10^6 <= nums[i] <= 10^6
.https://leetcode-cn.com/problems/running-sum-of-1d-array/
 */
class ArrayRunningSolution {
public:
    vector<int> runningSum(vector<int>& nums) {
        int N = nums.size();
        vector<int> dp(N, 0);
        if(N > 0) {
            dp[0] = nums[0];
        }
        for (int i = 1; i < nums.size(); ++i) {
            dp[i] = dp[i-1] + nums[i];
        }
        return dp;
    }
};

/**
 剑指 Offer 59 - I. 滑动窗口的最大值
 给定一个数组 nums 和滑动窗口的大小 k，请找出所有滑动窗口里的最大值。

 示例:

 输入: nums = [1,3,-1,-3,5,3,6,7], 和 k = 3
 输出: [3,3,5,5,6,7]
 解释:

   滑动窗口的位置                最大值
 ---------------               -----
 [1  3  -1] -3  5  3  6  7       3
  1 [3  -1  -3] 5  3  6  7       3
  1  3 [-1  -3  5] 3  6  7       5
  1  3  -1 [-3  5  3] 6  7       5
  1  3  -1  -3 [5  3  6] 7       6
  1  3  -1  -3  5 [3  6  7]      7
  

 提示：

 你可以假设 k 总是有效的，在输入数组不为空的情况下，1 ≤ k ≤ 输入数组的大小。

 注意：本题与主站 239 题相同：https://leetcode-cn.com/problems/sliding-window-maximum/

.https://leetcode-cn.com/problems/hua-dong-chuang-kou-de-zui-da-zhi-lcof/
 */

class MaxSlidingWindowSolution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        int N = nums.size();
        vector<int> dp(N, 0);
        if (N == 0) return dp;
        if (N < k) return dp; //错误情况

        for (int i = 0; i < N; ++i) {
            dp[i] = nums[i];
        }
        for (int wd = 2; wd <= k; ++wd) {
            for (int i = 0; i <= N - wd; ++i) {
                dp[i] = max(dp[i], dp[i+1]);
            }
        }

        vector<int> res(dp.begin(), (dp.begin() + N - k + 1));
        return res;
    }
};
#endif /* DPSolution_hpp */
