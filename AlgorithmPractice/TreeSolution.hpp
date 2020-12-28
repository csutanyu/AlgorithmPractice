//
//  TreeSolution.hpp
//  AlgorithmPractice
//
//  Created by arvintan on 2020/12/28.
//  Copyright © 2020 arvintan. All rights reserved.
//

#ifndef TreeSolution_hpp
#define TreeSolution_hpp

#include <stdio.h>

#include <stdio.h>
#include <string>
#include <vector>
#include <map>
#include <stack>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <sstream>
#include <iostream>
#include <iosfwd>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class TreeSolution {
    
public:

    /**
     94. 二叉树的中序遍历
     给定一个二叉树的根节点 root ，返回它的 中序 遍历。
     */
    
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> res;
        doInorderTraversalRecursion(res, root);
        return res;
    }
    
    void doInorderTraversalRecursion(vector<int>& res, TreeNode* root) {
        if (root == NULL) {
            return;
        }
        doInorderTraversalRecursion(res, root->left);
        res.push_back(root->val);
        doInorderTraversalRecursion(res, root->right);
    }
};


#endif /* TreeSolution_hpp */
