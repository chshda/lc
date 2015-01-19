// Source: https://oj.leetcode.com/problems/reverse-linked-list-ii/

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
    ListNode *reverseBetween(ListNode *head, int m, int n) {
        ListNode dummy(-1);
        dummy.next = head;
        
        ListNode *pre = &dummy, *p = head;
        for (int i = 1; i < m; i++) //前面不变
            pre = p, p = p->next;
        
        ListNode *pm = p, *pmpre = pre, *nextp;
        for (int i = m; i <= n; i++) //翻转
        {
            nextp = p->next;
            p->next = pre;
            pre = p, p = nextp;
        }
        pmpre->next = pre, pm->next = nextp;
        
        return dummy.next;
    }
};