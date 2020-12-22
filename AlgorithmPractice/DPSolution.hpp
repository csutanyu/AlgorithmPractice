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
        
        vector<vector<pair<int, int> > > dp(len, vector<pair<int, int> >(len, pair<int, int>(0, 0)));
        vector<int> sum(len, 0);
        for (int index = len - 1; index >= 0; --index) {
            // 从i开始往后的序列之各
            // 此处的index为石头序列的序号
            sum[index] += (index + 1) < len ? (piles[index] + piles[index + 1]) :piles[index];
            
            // 只剩最后一堆时，先手可获得全部，后手可获得0
            // 此处index为M数，无论M数为多少，只有最后一堆时，先手都获得全部
            dp[len - 1][index] = pair<int, int>(piles[len - 1], 0);
        }
        
//        // 只剩最后一堆时，先手可获得全部，后手可获得0
//        for (int m = 0; m < len; ++len) {
//            dp[len - 1][m] = pair<int, int>(piles[len - 1], 0);
//        }
        
        vector<vector<int> > totalSum(len, vector<int>(0));
        for (int i = len - 2; i >= 0; --i) { // 从后往前扫描
            for (int m = 1; m <= len - i; ++m) { // 每次将M从1到总零数进行计算
                for (int x = 1; x <= min(2 * m, len - 1) /* 先手可以获取的数量x为2m与剩余零数的较小值 */; ++x) {
                    
                    //求先手获得的子串合
                    int s = 0;
                    for (int t = i; i <= i + x - 1; ++t) {
                        s += piles[t];
                    }
                    
                    int first = s + dp[i + x][max(x, m)].second;
                    int second = dp[i + x][max(x, m)].first;
                    
                    if (first > dp[i][m].first) {
                        dp[i][m].first = first;
                        dp[i][m].second = second;
                    }
                }
            }
            
            
        }
        
        return dp[0][0].first;
    }
};

#endif /* DPSolution_hpp */
