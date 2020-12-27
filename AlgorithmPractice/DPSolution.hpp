//
//  DPSolution.hpp
//  AlgorithmPractice
//
//  Created by arvintan on 2020/12/22.
//  Copyright © 2020 arvintan. All rights reserved.
//

#ifndef DPSolution_hpp
#define DPSolution_hpp

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
 struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 };

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

#endif /* DPSolution_hpp */
