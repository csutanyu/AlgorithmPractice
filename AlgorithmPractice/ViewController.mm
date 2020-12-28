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


#include <string>
#include <vector>

using namespace std;

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
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
    
    
    
//    MaxProfitSolution mps;
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
    
    TreeSolution treeSolution;
    TreeNode *n3 = new TreeNode();
    n3->val = 3;
    
    TreeNode *n2 = new TreeNode();
    n2->val = 2;
    n2->left = n3;
    
    TreeNode *root = new TreeNode();
    root->val = 1;
    root->right = n2;
    
    vector<int> res = treeSolution.inorderTraversal(root);
    
    int x;
}


@end
