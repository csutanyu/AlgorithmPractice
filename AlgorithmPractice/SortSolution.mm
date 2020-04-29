//
//  SortSolution.m
//  AlgorithmPractice
//
//  Created by arvintan on 2020/4/29.
//  Copyright © 2020 arvintan. All rights reserved.
//

#import "SortSolution.h"
#include <vector>
#include <string>
#include <stack>

using namespace std;


void bubbleSort(int array[], int length) {
    for (int end = length; end > 1; --end) {
        for (int begin = 0; begin < end - 1; ++begin) {
            if (array[begin] > array[begin + 1]) {
                int temp = array[begin];
                array[begin] = array[begin + 1];
                array[begin + 1] = temp;
            }
        }
    }
}

void selectSort(int array[], int length) {
    for (int index = 0; index < length; ++ index) {
        int minIndex = index;
        for (int innerIndex = index + 1; innerIndex < length; ++innerIndex) {
            if (array[innerIndex] < array[minIndex]) {
                minIndex = innerIndex;
            }
        }
        if (minIndex != index) {
            int temp = array[index];
            array[index] = array[minIndex];
            array[minIndex] = temp;
        }
    }
}


@implementation SortSolution

@end
