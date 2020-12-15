//
//  ViewController.m
//  AlgorithmPractice
//
//  Created by arvintan on 2020/4/28.
//  Copyright © 2020 arvintan. All rights reserved.
//

#import "ViewController.h"
#import "SortSolution.h"


//  Definition for singly-linked list.

 
class Solution {
public:
    ListNode *createNewNode() {
        return new ListNode(0);
    }

    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode *leftNode = l1;
        ListNode *rightNode = l2;
        ListNode *lastSumNode = sum;
        while (leftNode != NULL || rightNode != NULL) {
            ListNode *currentNode = createNewNode();
            if (leftNode != NULL) {
                currentNode->val += leftNode->val;
                leftNode = leftNode->next;
            }
            if (rightNode != NULL) {
                currentNode->val += rightNode->val;
                rightNode = rightNode->next;
            }
            if (lastSumNode == NULL) {
                lastSumNode = currentNode;
            } else {
                lastSumNode->next = currentNode;
                currentNode->val += (lastSumNode->val / 10);
                lastSumNode = currentNode;
            }
        }

        if (lastSumNode->val >= 10) {
            lastSumNode->next = createNewNode();
            lastSumNode->next->val = lastSumNode->val / 10;
        }

        if (sum == NULL) {
            sum = createNewNode();
        }

        return sum;
    }
};

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    int array1[] = {2, 4, 3};
    int array2[] = {5, 6, 4};
    
    ListNode *l1 = ListNode::createList(array1, 3);
    ListNode *l2 = ListNode::createList(array2, 3);
    
    
    
//    SortSolution so = SortSolution();
    
    int array[] = {3, 8, 5, 1, 10, 2, 9};
    
//    bubbleSort(array, sizeof(array)/sizeof(int));
//    selectSort(array, sizeof(array)/sizeof(int));
    insertSort(array, sizeof(array)/sizeof(int));
    
    int i = 0;
    
    
    // Do any additional setup after loading the view.
}


@end
