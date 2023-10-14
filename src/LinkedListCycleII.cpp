// Source: https://oj.leetcode.com/problems/linked-list-cycle-ii/

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
    ListNode *detectCycle(ListNode *head) {
        if (head == NULL || head->next == NULL) return NULL;
        ListNode *slow = head, *fast = head;
        while (fast && fast->next)
        {
            slow = slow->next, fast = fast->next->next;
            if (slow == fast) break;
        }
        if (slow != fast) return NULL;
        else
        {
            ListNode *p1 = head, *p2 = slow;
            while (p1 != p2) p1 = p1->next, p2 = p2->next;
            return p1;
        }
    }
};