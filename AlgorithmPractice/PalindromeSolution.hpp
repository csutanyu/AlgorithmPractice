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



#endif /* PalindromeSolution_hpp */
