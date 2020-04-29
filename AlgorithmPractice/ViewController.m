//
//  ViewController.m
//  AlgorithmPractice
//
//  Created by arvintan on 2020/4/28.
//  Copyright © 2020 arvintan. All rights reserved.
//

#import "ViewController.h"
#import "SortSolution.h"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
//    SortSolution so = SortSolution();
    
    int array[] = {3, 8, 5, 1, 10, 2, 9};
    
//    bubbleSort(array, sizeof(array)/sizeof(int));
//    selectSort(array, sizeof(array)/sizeof(int));
    insertSort(array, sizeof(array)/sizeof(int));
    
    int i = 0;
    
    
    // Do any additional setup after loading the view.
}


@end
