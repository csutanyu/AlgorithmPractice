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


@interface SortSolution : NSObject

@end

NS_ASSUME_NONNULL_END
