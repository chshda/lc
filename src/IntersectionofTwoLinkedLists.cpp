// Source: https://oj.leetcode.com/problems/intersection-of-two-linked-lists/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        if (headA == NULL || headB == NULL) return NULL;
        
        int la = 1;
        ListNode *pa = headA;
        while (pa->next != NULL) pa = pa->next, la++;
        
        int lb = 1;
        ListNode *pb = headB;
        while (pb->next != NULL) pb = pb->next, lb++;
        
        if (pa != pb) return NULL;
        
        pa = headA, pb = headB;
        if (la > lb)
            for (int i = 0; i < la-lb; i++) pa = pa->next;
        else if (la < lb)
            for (int i = 0; i < lb-la; i++) pb = pb->next;
        
        while (pa != pb) pa = pa->next, pb = pb->next;
        return pa;
    }
};