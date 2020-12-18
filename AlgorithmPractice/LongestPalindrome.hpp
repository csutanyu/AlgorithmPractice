//
//  LongestPalindrome.h
//  AlgorithmPractice
//
//  Created by arvintan on 2020/12/15.
//  Copyright © 2020 arvintan. All rights reserved.
//

#ifndef LongestPalindrome_hpp
#define LongestPalindrome_hpp

#include <string>
#include <vector>

//https://leetcode-cn.com/problems/longest-palindromic-substring/solution/zhong-xin-kuo-san-dong-tai-gui-hua-by-liweiwei1419/
//给定一个字符串 s，找到 s 中最长的回文子串。你可以假设 s 的最大长度为 1000。
//
//示例 1：
//
//输入: "babad"
//输出: "bab"
//注意: "aba" 也是一个有效答案。
//示例 2：
//
//输入: "cbbd"
//输出: "bb"
//

using namespace std;

class LongestPalindrome {
public:
    string longestPalindrome(string s) {
      if (s.length() < 2) {
          return s;
      }
      size_t length = s.length();
      int begin = 0;
      int end = 0;
      int max = 1;
      vector<int> dpMap(length);
      for (int j = 0; j < length; ++j) {
          for (int i = 0; i < j; ++i) {
              if (j - i <= 2) {
                  dpMap[i] = (s[i] == s[j] ? 1 : 0);
              } else {
                  dpMap[i] = ((dpMap[i+1] == 1) && (s[i] == s[j])) ? 1 : 0;
              }
              if (dpMap[i] == 1 && j - i  + 1 > max) {
                  max = j - i + 1;
                  begin = i;
                  end = j;
              }
          }
      }
      return s.substr(begin, max);
  }
    
    inline bool isHuiwen(string &s, int beginIndex, int lastIndex) {
        bool huiwen = true;
        while (beginIndex < lastIndex ) {
            if (s[beginIndex] != s[lastIndex]) {
                huiwen = false;
            }
            ++beginIndex;
            --lastIndex;
        }
        return huiwen;
    }
};
#endif
