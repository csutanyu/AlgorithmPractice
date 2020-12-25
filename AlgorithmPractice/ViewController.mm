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
    
//    10
//    [[1,2],[3,4],[5,6],[6,7],[8,9],[7,8]]
    vector<vector<int> > dislikes(10, vector<int>(2, 0));
    dislikes[0][0] = 1;
    dislikes[0][1] = 2;
    
    dislikes[1][0] = 3;
    dislikes[1][1] = 4;
    
    dislikes[2][0] = 5;
    dislikes[2][1] = 6;
    
    dislikes[3][0] = 6;
    dislikes[3][1] = 7;
    
    dislikes[4][0] = 8;
    dislikes[4][1] = 9;
    
    dislikes[5][0] = 7;
    dislikes[5][1] = 8;
   
    dps.possibleBipartition(10, dislikes);
    
    // Do any additional setup after loading the view.
}


@end
