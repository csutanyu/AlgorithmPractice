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
#if 0
        vector<int> auxVec(vec.size(), 0);
        mergeSort(vec, auxVec, 0, vec.size() - 1);
#else
        mergSortBottom(vec);
#endif
    }
    
    void mergSortBottom(vector<int> &vec) {
        vector<int> auxVec(vec.size(), 0);
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
        for (int i = low; i <= high; ++i) {
            temp[i] = vec[i];
        }
        int i = low;
        int j = mid + 1;
        for (int k = low; k <= high; ++k) {
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

/**
 快速排序 P182
 */
class QuickSort {
    
public:
    void sort(vector<int> &vec) {
#if 0
        quickSort(vec, 0, (int)(vec.size() - 1));
#else
        quick3way(vec, 0, (int)vec.size() - 1);
#endif
    }
    
    /**
     三向切分的快速排序 P189
     */
    void quick3way(vector<int> &vec, int low, int high) {
        if (low >= high) {
            return;
        }
        int val = vec[low];
        int lt = low;
        int gt = high;
        int i = lt;
        while (i <= gt) {
            if (vec[i] < val) {
                swap(vec[i], vec[lt]);
                ++lt;
                ++i;
            } else if (vec[i] > val) {
                swap(vec[i], vec[gt]);
                --gt;
                ++i;
            } else {
                ++i;
            }
        }
        quick3way(vec, low, lt - 1);
        quick3way(vec, gt + 1, high);
    }
    
    void quickSort(vector<int> &vec, int low, int high) {
        if (low >= high) {
            return;
        }
        int j = partition(vec, low, high);
        quickSort(vec, low, j - 1);
        quickSort(vec, j + 1, high);
    }
    
    int partition(vector<int> &vec, int low, int high) {
        int val = vec[low];
        int i = low;
        int j = high+1;
        
        while (true) {
            while (vec[++i] < val) {
                if (i == high) {
                    break;
                }
            }
            while (vec[--j] > val) {
                if (j == low) {
                    break;
                }
            }
            if (i >= j) {
                break;
            }
<<<<<<< HEAD
            swap(vec[j], vec[i]);
        }
        swap(vec[low], vec[j]);
=======
            swap(vec[i], vec[j]);
        }
        swap(vec[j], vec[low]);
>>>>>>> 修复 快速排序 P182
        
        return j;
    }
};


#endif /* Algorithms4Chapter2_hpp */
