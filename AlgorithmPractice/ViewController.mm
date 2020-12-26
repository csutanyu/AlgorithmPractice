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
    
    vector<string> equations;
    equations.push_back("c==c");
    equations.push_back("b==d");
    equations.push_back("x!=z");
    bool e = dps.equationsPossible(equations);
    int x;
}


@end
