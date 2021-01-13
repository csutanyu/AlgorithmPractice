//
//  Algorithms4Chapter2.hpp
//  AlgorithmPractice
//
//  Created by arvintan on 2021/1/13.
//  Copyright © 2021 arvintan. All rights reserved.
//

#ifndef Algorithms4Chapter2_hpp
#define Algorithms4Chapter2_hpp

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
 选择排序 P 156
 */
class SelectSort {
public:
    void sort(vector<int> & vec) {
        size_t N = vec.size();
        for (size_t i = 0; i < N; ++i) {
            size_t min = i;
            for (size_t j = i + 1; j < N; ++j) {
                if (vec[j] < vec[min]) {
                    min = j;
                }
            }
            int temp = vec[i];
            vec[i] = vec[min];
            vec[min] = temp;
        }
    }
};

/**
 插入排序 P157
 */
class InsertSort {
public:
    void sort(vector<int> & vec) {
        int N = (int)vec.size();
        int temp = 0;
        for (int i = 1; i < N; ++i) {
            for (int j = i; j > 0 && vec[j] < vec[j-1]; --j) {
                temp = vec[j];
                vec[j] = vec[j-1];
                vec[j-1] = temp;
            }
        }
    }
};

/**
 希尔排序 P163
 */
class ShellSort {
public:
    void sort(vector<int> & vec) {
        int N = (int)vec.size();
        int h = 1;
        while (h < N/3) {
            h = 3 * h + 1;
        }
        int temp = 0;
        while (h >= 1) {
            for (int i = h; i < N; ++i) {
                for (int j = i; j > 0 && vec[j] < vec[j-h]; j -= h) {
                    temp = vec[j];
                    vec[j] = vec[j-1];
                    vec[j-1] = temp;
                }
            }
            --h;
        }
    }
};


#endif /* Algorithms4Chapter2_hpp */
