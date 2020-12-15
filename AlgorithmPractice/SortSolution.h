//
//  SortSolution.h
//  AlgorithmPractice
//
//  Created by arvintan on 2020/4/29.
//  Copyright © 2020 arvintan. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
    排序算法
    https://www.cnblogs.com/onepixel/p/7674659.html
 */

NS_ASSUME_NONNULL_BEGIN


// 冒泡排序
FOUNDATION_EXTERN void bubbleSort(int array[], int length);

// 选择排序
FOUNDATION_EXTERN void selectSort(int array[], int length);

// 选择排序
FOUNDATION_EXTERN void insertSort(int array[], int length);


struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
    
    static ListNode* createList(int array[], int length) {
        ListNode *list;
        ListNode *lastNode;
        for (int i = 0; i < length; ++i) {
            ListNode *node = new ListNode(array[i]);
            if (i == 0) {
                lastNode = node;
                list = node;
            } else {
                lastNode->next = node;
                lastNode = node;
            }
        }
        return list;
    }
};

@interface SortSolution : NSObject

@end

NS_ASSUME_NONNULL_END
