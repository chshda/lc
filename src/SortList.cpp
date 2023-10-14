// Source: https://oj.leetcode.com/problems/sort-list/

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
    ListNode *sortList(ListNode *head) {
        if (head == NULL || head->next == NULL) return head;
        
        ListNode *slow = head, *fast = head->next; //寻找中点
        while (fast != NULL && fast->next != NULL)
            fast = fast->next->next, slow = slow->next;
            
        ListNode *mid = slow->next; slow->next = NULL;
        ListNode *p1 = sortList(head), *p2 = sortList(mid);
        
        ListNode dummy(0), *p = &dummy;
        while (p1 != NULL && p2 != NULL)
            if (p1->val < p2->val) {
                p->next = p1; p = p1; p1 = p1->next;
            }
            else {
                p->next = p2; p = p2; p2 = p2->next;
            }
        if (p1 != NULL) p->next = p1;
        if (p2 != NULL) p->next = p2;
        
        return dummy.next;
    }
};