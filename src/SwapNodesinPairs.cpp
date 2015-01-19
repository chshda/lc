// Source: https://oj.leetcode.com/problems/swap-nodes-in-pairs/

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
    ListNode *swapPairs(ListNode *head) {
        if (head == NULL || head->next == NULL) return head; //0个或1个元素
        
        ListNode *ans = head->next; //新的头结点
        
        ListNode *p1 = head, *p2 = head->next;
        while (p1 != NULL && p2 != NULL)
        {
            ListNode *t1 = p2->next, *t2 = t1 ? t1->next : NULL;
            p1->next = t2 ? t2 : t1, p2->next = p1; //t2为空时p1->next应为t1
            p1 = t1, p2 = t2;
        }
        return ans;
    }
};