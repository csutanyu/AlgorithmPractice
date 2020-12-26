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
            
            int firstLikeRoot = ufind(parent, firstPerson);
            int secondLikeRoot = ufind(parent, secondPerson);
            
            if (firstLikeRoot == secondLikeRoot) {
                return false;
            }
            
            int firstHateRoot = ufind(parent, firstPerson + N);
            int secondHateRoot = ufind(parent, secondPerson + N);
            
            parent[firstHateRoot] = secondLikeRoot;
            parent[secondHateRoot] = firstPerson;
        }
        return true;
    }
    
    int ufind(vector<int> &parent, int x) {
        while (parent[x] != x) {
            parent[x] = parent[parent[x]];
            x = parent[x];
        }
        return x;
    }
};

#endif /* DPSolution_hpp */
