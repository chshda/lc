// Source: https://oj.leetcode.com/problems/partition-list/

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
    ListNode *partition(ListNode *head, int x) {
        if (head == NULL || head->next == NULL) return head;
        
        ListNode dummy1(-1), dummy2(-1), *p1 = &dummy1, *p2 = &dummy2;
        while (head != NULL)
        {
            ListNode *nxt = head->next;
            if (head->val < x)
                p1->next = head, p1 = head, p1->next = NULL;
            else
                p2->next = head, p2 = head, p2->next = NULL;
            head = nxt;
        }
        p1->next = dummy2.next;
        return dummy1.next;
    }
};