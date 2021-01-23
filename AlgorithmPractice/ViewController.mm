//
//  ViewController.m
//  AlgorithmPractice
//
//  Created by arvintan on 2020/4/28.
//  Copyright © 2020 arvintan. All rights reserved.
//

#import "ViewController.h"
#import "SortSolution.h"
#import "LongestPalindrome.hpp"
#import "PalindromeSolution.hpp"
#import "DPSolution.cpp"
#import "TreeSolution.hpp"
#import "Algorithms4Chapter1.hpp"
#import "Algorithms4Chapter2.hpp"
#import "LeetCodeCommons.hpp"
#include <string>
#include <vector>

using namespace std;

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    
    TreeSolution ts;
    
    
    
    Node *root = new Node(4);
    root->left = new Node(2);
    root->right = new Node(5);
    root->left->left = new Node(1);
    root->left->right = new Node(3);
    
    Node *x = ts.treeToDoublyList(root);

    vector<int> vec = {2000, 3, 200, 8, 199, 89, 90, 66,  299, 5, 1, 10, 2, 9, 20, 500};
    vector<int>::iterator begin = vec.begin();
    vector<int>::iterator it = find(begin, begin + 2, 8);
    if (it != vec.end()) {
        int x = *it;
    }
    
    HeapSort s;
    s.sort(vec);
    
    PriorityQueueInt pq;
    pq.push(3);
    pq.push(200);
    pq.push(8);
    pq.push(199);
    pq.push(89);
    pq.push(90);
    pq.push(66);
    pq.push(299);
    pq.push(5);
    pq.push(1);
    pq.push(10);
    pq.push(2);
    pq.push(9);
    pq.push(20);
    pq.push(500);
    pq.push(2000);
    vector<int> vec2;
    
    while (pq.size() > 0) {
        vec2.push_back(pq.top());
        pq.pop();
    }
    
    
//    SortSolution so = SortSolution();
    
//    int array[] = {3, 8, 5, 1, 10, 2, 9};
    
//    bubbleSort(array, sizeof(array)/sizeof(int));
//    selectSort(array, sizeof(array)/sizeof(int));
//    insertSort(array, sizeof(array)/sizeof(int));
//
//    int i = 0;
//    LongestPalindrome lp;
//    string x = lp.longestPalindrome("babad");
    
//    LonestpalindromeSolution lp;
//    int x = lp.longestPalindromeSubseq("bbbab");
    
    
    DPSolution dps;
    //        [100,4,200,1,3,2]
//    vector<int> v;
//    v.push_back(100);
//    v.push_back(4);
//    v.push_back(200);
//    v.push_back(1);
//    v.push_back(3);
//    v.push_back(2);
//
//    int c = dps.longestConsecutive(v);
    
//    ["c==c","b==d","x!=z"]
    
//    vector<string> equations;
//    equations.push_back("c==c");
//    equations.push_back("b==d");
//    equations.push_back("x!=z");
//    bool e = dps.equationsPossible(equations);
    
    //[2,3,2]
//    vector<int> rooms;
//    rooms.push_back(1);
//    rooms.push_back(2);
//    rooms.push_back(3);
//    rooms.push_back(1);
//    rooms.push_back(0);
//    rooms.push_back(0);
//    Robber robber;
//    int theMost = robber.rob2(rooms);
    
    
    
    MaxProfitSolution mps;
//    2
//    [1,2,4,2,5,7,2,4,9,0]
//    vector<int>  prices;
//    prices.push_back(1);
//    prices.push_back(2);
//    prices.push_back(4);
//    prices.push_back(2);
//    prices.push_back(5);
//    prices.push_back(7);
//    prices.push_back(2);
//    prices.push_back(4);
//    prices.push_back(9);
//    prices.push_back(0);
//
//    int maxProfit = mps.maxProfit_IV(2, prices);
    
//    bool x = mps.regexMatch("aa", "a*");
//
//
//
//    TreeSolution treeSolution;
//    TreeNode *n3 = new TreeNode();
//    n3->val = 3;
//
//    TreeNode *n2 = new TreeNode();
//    n2->val = 2;
//    n2->left = n3;
//
//    TreeNode *root = new TreeNode();
//    root->val = 1;
//    root->right = n2;
//
//    vector<int> res = treeSolution.preorderTraversal(root);
    
    CalculatorSolution cs;
//    int res = cs.calculate("1*2-3/4+5*6-7*8+9/10");
//    int res = cs.calculateIIV2("3+2*2");
    
//    int rese = cs.calculateBase(" 6-4 / 2 ");
    
//    ["FreqStack","push","push","push","push","push","push","push","push","push","push","pop","pop","pop","pop","pop","pop","pop","pop","pop","pop"]
//    [[],[5],[1],[2],[5],[5],[5],[1],[6],[1],[5],[],[],[],[],[],[],[],[],[],[]]
    FreqStack freqStk;
    freqStk.push(5);
    freqStk.push(1);
    freqStk.push(2);
    freqStk.push(5);
    freqStk.push(5);
    freqStk.push(5);
    freqStk.push(1);
    freqStk.push(6);
    freqStk.push(1);
    freqStk.push(5);
    
    vector<int> ret;
    ret.push_back(freqStk.pop());
    ret.push_back(freqStk.pop());
    ret.push_back(freqStk.pop());
    ret.push_back(freqStk.pop());
    ret.push_back(freqStk.pop());
    ret.push_back(freqStk.pop());
    ret.push_back(freqStk.pop());
    ret.push_back(freqStk.pop());
    ret.push_back(freqStk.pop());
    ret.push_back(freqStk.pop());
    
    int i = 0;
}


@end
