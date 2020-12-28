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
    
    void doInorderTraversalNonRecursion(vector<int>& res, TreeNode* root) {
        stack<TreeNode *> tStack;
        TreeNode * cur = root;
        while (!tStack.empty() || cur != NULL) {
            if (cur != NULL) {
                tStack.push(cur);
                cur = cur->left;
            } else {
                TreeNode *top = tStack.top();
                tStack.pop();
                res.push_back(top->val);
                cur = top->right;
            }
        }
    }
    
    
    /**
     144. 二叉树的前序遍历
     给你二叉树的根节点 root ，返回它节点值的 前序 遍历。

      

     示例 1：


     输入：root = [1,null,2,3]
     输出：[1,2,3]
     示例 2：

     输入：root = []
     输出：[]
     示例 3：

     输入：root = [1]
     输出：[1]
     示例 4：


     输入：root = [1,2]
     输出：[1,2]
     示例 5：


     输入：root = [1,null,2]
     输出：[1,2]
      

     提示：

     树中节点数目在范围 [0, 100] 内
     -100 <= Node.val <= 100
      

     进阶：递归算法很简单，你可以通过迭代算法完成吗？
     */
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> res;
        nonRecursionPreorderTraversal(res, root);
        return res;
    }
    
    void recursionPreorderTraversal(vector<int> &res, TreeNode* root) {
        if (root == NULL) return;
        
        res.push_back(root->val);
        recursionPreorderTraversal(res, root->left);
        recursionPreorderTraversal(res, root->right);
    }
    
    void nonRecursionPreorderTraversal(vector<int> &res, TreeNode* root) {
        if (root == NULL) return;
        
        stack<TreeNode *> tStack;
        tStack.push(root);
        while (!tStack.empty()) {
            TreeNode *top = tStack.top();
            tStack.pop();
            res.push_back(top->val);
            if (top->right != NULL) {
                tStack.push(top->right);
            }
            if (top->left) {
                tStack.push(top->left);
            }
        }
    }
    
    /**
     145. 二叉树的后序遍历
     给定一个二叉树，返回它的 后序 遍历。

     示例:

     输入: [1,null,2,3]
        1
         \
          2
         /
        3

     输出: [3,2,1]
     进阶: 递归算法很简单，你可以通过迭代算法完成吗？

     通过次数174,128提交次数236,046
     */
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> res;
        recursionpostorderTraversal(res, root);
        
        return res;
    }
    
    void recursionpostorderTraversal(vector<int>& res, TreeNode* root) {
        if (root == NULL) return;
        
        recursionpostorderTraversal(res, root->left);
        recursionpostorderTraversal(res, root->right);
        res.push_back(root->val);
    }
    
    void nonRecursionpostorderTraversal(vector<int>& res, TreeNode* root) {
        if (root == NULL) return;
        
        stack<TreeNode *> tSt1;
        stack<TreeNode *> tSt2;
        
        TreeNode *cur = root;
        tSt1.push(root);
        
        while (!tSt1.empty()) {
            cur = tSt1.top();
            tSt1.pop();
            tSt2.push(cur);
            
            if (cur->left != NULL) {
                tSt1.push(cur->left);
            }
            if (cur->right != NULL) {
                tSt1.push(cur->right);
            }
        }
        
        while (!tSt2.empty()) {
            cur = tSt2.top();
            tSt2.pop();
            res.push_back(cur->val);
        }
    }
    
    // 通过修正的中序遍历实现
    // pre存储前一个被遍历的节点。中节点只有在没有右子树或者右子树已经被访问过了(pre=node->right)才会从栈中弹出进行访问
    void nonRecursionpostorderTraversalV2(vector<int>& res, TreeNode* root) {
        if (root == NULL) {
            return;
        }
        
        stack<TreeNode *> tStack;
        TreeNode * cur = root;
        TreeNode * pre = NULL;
        
        while (!tStack.empty() || cur != NULL) {
            if (cur != NULL) {
                tStack.push(cur);
                cur = cur->left;
            } else {
                TreeNode *top = tStack.top();
                if (top->right == NULL || pre == top->right) {
                    res.push_back(top->val);
                    tStack.pop();
                    pre = top;
                } else if (top->right != NULL) {
                    cur = top->right;
                }
            }
        }
    }
    
    /**
     102. 二叉树的层序遍历
     
     给你一个二叉树，请你返回其按 层序遍历 得到的节点值。 （即逐层地，从左到右访问所有节点）。

      

     示例：
     二叉树：[3,9,20,null,null,15,7],

         3
        / \
       9  20
         /  \
        15   7
     返回其层序遍历结果：

     [
       [3],
       [9,20],
       [15,7]
     ]
     */
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> res;
        if (root == NULL) {
            return res;
        }
        queue<TreeNode * > nodeQueue;
        nodeQueue.push(root);
        while (!nodeQueue.empty()) {
            res.push_back(vector<int>());
            size_t currentLevelSize = nodeQueue.size();
            for (int i = 0; i < currentLevelSize; ++i) {
                TreeNode *current = nodeQueue.front();
                res.back().push_back(current->val);
                nodeQueue.pop();
                if (current->left != NULL) {
                    nodeQueue.push(current->left);
                }
                if (current->right != NULL) {
                    nodeQueue.push(current->right);
                }
            }
        }
        return res;
    }
    
    /**
     107. 二叉树的层序遍历 II
     给定一个二叉树，返回其节点值自底向上的层序遍历。 （即按从叶子节点所在层到根节点所在的层，逐层从左向右遍历）

     例如：
     给定二叉树 [3,9,20,null,null,15,7],

         3
        / \
       9  20
         /  \
        15   7
     返回其自底向上的层序遍历为：

     [
       [15,7],
       [9,20],
       [3]
     ]
     */
    vector<vector<int>> levelOrderBottom(TreeNode* root) {
        vector<vector<int>> res;
        if (root == NULL) {
            return res;
        }
        queue<TreeNode * > nodeQueue;
        nodeQueue.push(root);
        while (!nodeQueue.empty()) {
            res.push_back(vector<int>());
            size_t currentLevelSize = nodeQueue.size();
            for (int i = 0; i < currentLevelSize; ++i) {
                TreeNode *current = nodeQueue.front();
                res.back().push_back(current->val);
                nodeQueue.pop();
                if (current->left != NULL) {
                    nodeQueue.push(current->left);
                }
                if (current->right != NULL) {
                    nodeQueue.push(current->right);
                }
            }
        }
        
        reverse(res.begin(), res.end());
        
        return res;
    }
};


#endif /* TreeSolution_hpp */
