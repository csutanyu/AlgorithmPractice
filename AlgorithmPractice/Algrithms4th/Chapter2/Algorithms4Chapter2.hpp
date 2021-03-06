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
#include "TreeSolution.hpp"

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
 已知在最坏的情况下shell排序的比较次数 和 N的3/2次方成正比
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
#warning TODO: P192 2.3.22 快 速 三 向 切 分。(J. Bently，D. McIlroy)
    
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
            swap(vec[j], vec[i]);
        }
        swap(vec[low], vec[j]);
        
        return j;
    }
};

class PriorityQueueInt {
    vector<int> _pq;
    int _capacity;
    int _size;
public:
    PriorityQueueInt(int capacity = 20):_capacity(capacity), _pq(capacity, 0), _size(0) {
    }
    
    void push(int x) {
        _pq[++_size] = x;
        swim(_size);
    }
    
    int top() {
        return _pq[1];
    }
    
    void pop() {
        _pq[1] = _pq[_size];
        _pq[_size] = 0;
        --_size;
        sink(1);
    }
    
    int size(void) {
        return _size;
    }
    
private:
    
    inline bool less(int i, int j) {
        return _pq[i] < _pq[j];
    }
    
    void swim(int k) {
        while (k > 1 && less(k/2, k)) {
            swap(_pq[k/2], _pq[k]);
            k = k/2;
        }
    }
    
    void sink(int k) {
        while (2 * k <= _size) {
            int j = 2 * k;
            if (j + 1 <= _size && less(j, j + 1)) {
                ++j;
            }
            if (less(j, k)) {
                break;
            }
            swap(_pq[j], _pq[k]);
            k = j;
        }
    }
};

#warning  TODO: P203  2.4.4.6 索引优先队列


/**
 P205  2.4.5 堆排序
 P208  2.4.5.3 先下沉后上浮：
 大多数在下沉排序期间重新插入堆的元素会被直 接加入到堆底。Floyd 在 1964 年观察发现，我们正 好可以通过免去检查元素是否到达正确位置来节省时 间。在下沉中总是直接提升较大的子结点直至到达堆 底，然后再使元素上浮到正确的位置。这个想法几乎 可以将比较次数减少一半——接近了归并排序所需的 比较次数(随机数组)。这种方法需要额外的空间， 因此在实际应用中只有当比较操作代价较高时才有用 (例如，当我们在将字符串或者其他键值较长类型的 结果 元素进行排序时)。
 */
class HeapSort {
public:
    void sort(vector<int> &vec) {
        int N = (int)(vec.size());
        if (N <= 1) {
            return;
        }
        
        // 注意：这里与用堆实现优先队列不一样的是，这里数组的0下标有元素，因此这种情况下，一个元素 i 的2个儿子节点应该是 2 * i + 1 和 2 * i + 2
        for (int i = (N - 2) / 2; i >= 0; --i) {
            sink(vec, i, N - 1);
        }
        while (N > 1) {
            swap(vec[0], vec[N-1]);
            --N;
            sink(vec, 0, N - 1);
        }
    }
    
    void sink(vector<int> &vec, int i, int maxIndex) {
        while (2 * i + 1 <= maxIndex) {
            int k = 2 * i + 1;
            if (k + 1 <= maxIndex && vec[k] < vec[k+1]) {
                ++k;
            }
            if (vec[i] > vec[k]) {
                break;
            }
            swap(vec[i], vec[k]);
            i = k;
        }
    }
};



/*
 剑指 Offer 55 - II. 平衡二叉树
 输入一棵二叉树的根节点，判断该树是不是平衡二叉树。如果某二叉树中任意节点的左右子树的深度相差不超过1，那么它就是一棵平衡二叉树。

  

 示例 1:

 给定二叉树 [3,9,20,null,null,15,7]

     3
    / \
   9  20
     /  \
    15   7
 返回 true 。

 示例 2:

 给定二叉树 [1,2,2,3,3,null,null,4,4]

        1
       / \
      2   2
     / \
    3   3
   / \
  4   4
 返回 false 。
 https://leetcode-cn.com/problems/ping-heng-er-cha-shu-lcof/
  */
class BinaryTreeSolution {
public:
    bool isBalanced(TreeNode* root) {
#if 0
        unordered_map<TreeNode *, int> heights;
        unordered_map<TreeNode *, bool> balances;
        return isBalanced(root, heights, balances);
#else
        int ret = calculateHeight(root);
        return ret >= 0;
#endif
    }

    int calculateHeight(TreeNode *root) {
        if (root == NULL) return 0;
        int left = calculateHeight(root->left);
        if (left < 0) return left;
        int right = calculateHeight(root->right);
        if (right < 0) return right;

        bool isBalanced = abs(left - right) <= 1;
        return isBalanced ? max(left, right) + 1 : -1;
    }
    
    bool isBalanced(TreeNode* root, unordered_map<TreeNode *, int> &heights, unordered_map<TreeNode *, bool> &balances) {
        if (root == NULL) {
            return true;
        }
        if (balances.count(root) != 0) {
            return balances[root];
        }

        bool left = isBalanced(root->left, heights, balances);
        if (!left) {
            balances[root] = false;
            return left;
        }
        
        bool right = isBalanced(root->right, heights, balances);
        if (!right) {
            balances[root] = false;
            return right;
        }
        
        int hLeft = 0;
        if (NULL != root->left) {
            hLeft = heights[root->left];
        }
        int hRight = 0;
        if (NULL != root->right) {
            hRight = heights[root->right];
        }
        bool isBalanced = abs(hLeft - hRight) <= 1;
        balances[root] = isBalanced;
        heights[root] = max(hLeft, hRight) + 1;

        return isBalanced;
    }
};

#endif /* Algorithms4Chapter2_hpp */
