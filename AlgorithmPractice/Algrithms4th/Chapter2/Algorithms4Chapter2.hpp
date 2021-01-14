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

/**
 自顶向下的归并排序 P171
 */
class Merge {
public:
    void sort(vector<int> &vec) {
        vector<int> auxVec(vec);
//        mergeSort(vec, auxVec, 0, vec.size());
        
        
        /**
         自底向上归并排序
         */
        int N = (int)vec.size();
        for (int sz = 1; sz < N - 1; sz += sz) {
            for (int low = 0; low < N - 1; low += 2 * sz) {
                merge(vec, auxVec, low, low + sz - 1, min(low + 2*sz -1, N - 1));
            }
        }
    }
    
    void mergeSort(vector<int> &vec, vector<int> &temp, int low, int high) {
        if (low >= high) {
            return;
        }
        int mid = low + (high - low) / 2;
        mergeSort(vec, temp, low, mid);
        mergeSort(vec, temp, mid + 1, high);
        merge(vec, temp, low, mid, high);
    }
    
    void merge(vector<int> &vec, vector<int> &temp, int low, int mid, int high) {
        for (int i = low; i < high; ++i) {
            temp[i] = vec[i];
        }
        int i = low;
        int j = mid + 1;
        for (int k = low; k < high; ++k) {
            if (i > mid) {
                vec[k] = temp[j++];
            } else if (j > high) {
                vec[k] = temp[i++];
            } else if (temp[i] <= temp[j]) {
                vec[k] = temp[i++];
            } else {
                vec[k] = temp[j++];
            }
        }
    }
};


#endif /* Algorithms4Chapter2_hpp */
