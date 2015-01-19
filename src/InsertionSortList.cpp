// Source: https://oj.leetcode.com/problems/insertion-sort-list/

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

    ListNode *insertionSortList(ListNode *head) {
        if (head == NULL || head->next == NULL) return head;
        
        ListNode *newhead = NULL;
        while (head != NULL)
        {
            ListNode *current = head;
            head = head->next;
            
            if (newhead == NULL || current->val < newhead->val) //插入到开头
                current->next = newhead, newhead = current;
            else
            {
                for (ListNode *p = newhead; p != NULL; p = p->next) //插入到p后
                    if (p->next == NULL || current->val < p->next->val)
                    {
                        current->next = p->next, p->next = current;
                        break;
                    }
            }
        }
        
        return newhead;
    }
};