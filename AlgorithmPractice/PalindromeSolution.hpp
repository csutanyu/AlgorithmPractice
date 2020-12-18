//
//  PalindromeSolution.hpp
//  AlgorithmPractic
//
//  Created by arvintan on 2020/4/28.
//  Copyright © 2020 arvintan. All rights reserved.
//

#ifndef PalindromeSolution_hpp
#define PalindromeSolution_hpp

#include <string>
#include <vector>


/*https://blog.csdn.net/ibelieve8013/article/details/103279661
 
 给定一个字符串s，分割s使得s的每一个子串都是回文串
 返回所有的回文分割结果。（注意：返回结果的顺序需要和输入字符串中的字母顺序一致。）
 例如:给定字符串s="aab",
 返回
   [↵    ["aa","b"],↵    ["a","a","b"]↵  ]


 Given a string s, partition s such that every substring of the partition is a palindrome.
 Return all possible palindrome partitioning of s.

 For example, given s ="aab",
 Return

   [↵    ["aa","b"],↵    ["a","a","b"]↵  ]↵
*/

using namespace std;

class PalindromeSolution {
    vector<vector<string> > result;
    vector<string> cur;
public:
    vector<vector<string>> partition(string s) {
        cur.clear();
        result.clear();
        dfs(s);
        return result;
    }
    
    void dfs(string &s) {
        if (s == ""){
            result.push_back(cur);
            return;
        }
        for (int i = 1; i <= s.length(); ++i) {
            string preStr = s.substr(0, i);
            if (isPalindrome(preStr)) {
                cur.push_back(preStr);
                string sufixStr = s.substr(i, s.length() - 1);
                dfs(sufixStr);
                cur.pop_back();
            }
        }
    }
    
    bool isPalindrome(string &s) {
        return s == string(s.rbegin(), s.rend());
    }
};


/**
 给定一个字符串 s ，找到其中最长的回文子序列，并返回该序列的长度。可以假设 s 的最大长度为 1000 。

  

 示例 1:
 输入:

 "bbbab"
 输出:

 4
 一个可能的最长回文子序列为 "bbbb"。

 示例 2:
 输入:

 "cbbd"
 输出:

 2
 一个可能的最长回文子序列为 "bb"。

  

 提示：

 1 <= s.length <= 1000
 s 只包含小写英文字母

 来源：力扣（LeetCode）
 链接：https://leetcode-cn.com/problems/longest-palindromic-subsequence
 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */
class LonestpalindromeSolution {
public:
    int longestPalindromeSubseq(string s) {
        int len = (int)s.length();

        vector<vector<int>> dp(len, vector<int>(len, 0));
        for (int i = 0; i < len; ++i) {
            dp[i][i] = 1;
        }
        
        for (int row = len - 1; row >= 0; --row) {
            for (int column = row + 1; column < len; ++column) {
                if (s[column] == s[row]) {
                    dp[row][column] = dp[row + 1][column - 1] + 2;
                } else {
                    dp[row][column] = std::max(dp[row + 1][column], dp[row][column - 1]);
                }
            }
        }
        
        return dp[0][len - 1];
    }
};


#endif /* PalindromeSolution_hpp */
