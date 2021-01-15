//
//  SortTests.m
//  AlgorithmPracticeTests
//
//  Created by arvintan on 2021/1/15.
//  Copyright © 2021 arvintan. All rights reserved.
//

#import <XCTest/XCTest.h>
#import "Algorithms4Chapter2.hpp"

@interface SortTests : XCTestCase

@end

@implementation SortTests

- (void)setUp {
    // Put setup code here. This method is called before the invocation of each test method in the class.
}

- (void)tearDown {
    // Put teardown code here. This method is called after the invocation of each test method in the class.
}

- (void)testSort {
    vector<int> v1 = {2000, 400, 3, 50, 8, 7, 10, 25, 22, 19, 20, 80, 71, 77, 90, 100, 200, 199, 201, 333, 444, 440, 555, 222, 1000,};
    vector<int> v2 = {2000, 400, 3, 50, 8, 7, 10};
    QuickSort qs;
    qs.sort(v1);
    
    // This is an example of a functional test case.
    // Use XCTAssert and related functions to verify your tests produce the correct results.
}

@end
