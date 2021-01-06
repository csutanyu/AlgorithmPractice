//
//  LinkedListSolution.hpp
//  AlgorithmPractice
//
//  Created by arvintan on 2020/12/31.
//  Copyright © 2020 arvintan. All rights reserved.
//

#ifndef LinkedListSolution_hpp
#define LinkedListSolution_hpp

#include <stdio.h>
#include "TreeSolution.hpp"
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


//Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
 

class LinkedListSolution {
    
    
public:
    /**
     定义一个函数，输入一个链表的头节点，反转该链表并输出反转后链表的头节点。

      

     示例:

     输入: 1->2->3->4->5->NULL
     输出: 5->4->3->2->1->NULL
      

     限制：

     0 <= 节点个数 <= 5000

      

     注意：本题与主站 206 题相同：https://leetcode-cn.com/problems/reverse-linked-list/

     来源：力扣（LeetCode）
     链接：https://leetcode-cn.com/problems/fan-zhuan-lian-biao-lcof
     著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
     */
    
    ListNode* reverseList(ListNode* head) {
        ListNode *cur = NULL;
        while (NULL != head) {
            ListNode *temp = head->next;
            head->next = cur;
            cur = head;
            head = temp;
        }
        return cur;
    }
    
    ListNode* reverseListRecursion(ListNode* head) {
        if (head->next == NULL) {
            return head;
        }
        
        ListNode *last = reverseListRecursion(head->next);
        head->next->next = head;
        head->next = NULL;
        return last;
    }
    
    /**
     递归反转链表的前N个节点
     输入: 1->2->3->4->5->NULL, 3
     输出: 3->2->1->4->5->NULL
     */
    ListNode* reverseNFrontListRecursion(ListNode* head, int n) {
        return doReverseNFrontListRecursion(head, n).first;
    }
    
    std::pair<ListNode*, ListNode*/*successor*/> doReverseNFrontListRecursion(ListNode* head, int n) {
        if (n == 1) {
            return std::pair<ListNode *, ListNode *>(head, head->next);
        }
        
        std::pair<ListNode *, ListNode *> last = doReverseNFrontListRecursion(head->next, n-1);
        head->next->next = head;
        head->next = last.second;
        return last;
    }
    
    /**
     92. 反转链表 II
     反转从位置 m 到 n 的链表。请使用一趟扫描完成反转。

     说明:
     1 ≤ m ≤ n ≤ 链表长度。

     示例:

     输入: 1->2->3->4->5->NULL, m = 2, n = 4
     输出: 1->4->3->2->5->NULL
     */
    ListNode* successor;
    ListNode* reverseBetween(ListNode* head, int m, int n) {
        if (m == 1) {
            return reverseFrontN(head, n);
        }
        ListNode* last = reverseBetween(head->next, m-1, n-1);
        head->next = last;
        return head;
    }
    
    ListNode* reverseFrontN(ListNode* head, int n) {
        if (n == 1) {
            successor = head->next;
            return head;
        }
        ListNode* last = reverseFrontN(head->next, n-1);
        head->next->next = head;
        head->next = successor;
        return last;
    }
};

#endif /* LinkedListSolution_hpp */
