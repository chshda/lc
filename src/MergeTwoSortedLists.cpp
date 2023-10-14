// Source: https://oj.leetcode.com/problems/merge-two-sorted-lists/

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
    ListNode *mergeTwoLists(ListNode *l1, ListNode *l2) {
        ListNode dummy(-1), *p = &dummy;
        
        while (l1 && l2)
            if (l1->val < l2->val) //l1较小
                p->next = l1, l1 = l1->next, p = p->next;
            else                   //l2较小
                p->next = l2, l2 = l2->next, p = p->next;
        
        //l1或l2剩下的元素，直接拼接到p的后面
        if (l1) p->next = l1;
        if (l2) p->next = l2;
        
        return dummy.next;
    }
};