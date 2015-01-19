// Source: https://oj.leetcode.com/problems/reorder-list/

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
    void reorderList(ListNode *head) {
        ListNode *head2 = splitList(head); //分成两段
        head2 = reverseList(head2); //后半段翻转
        head = mergeList(head, head2); //合并
    }
    
    ListNode *splitList(ListNode *head)
    {
        if (head == NULL) return head;
        
        ListNode *slow = head, *fast = head;
        while(fast && fast->next)
            slow = slow->next, fast = fast->next->next;
            
        ListNode *ret = slow->next;
        slow->next = NULL;
        return ret;
    }
    
    ListNode* reverseList(ListNode *head)
    {
        ListNode *pre = NULL, *cur = head;
        while (cur)
        {
            ListNode *tem = cur->next;
            cur->next = pre;
            pre = cur, cur = tem;
        }
        return pre;
    }
    
    ListNode* mergeList(ListNode *p1, ListNode *p2)
    {
        ListNode dummy(-1), *p = &dummy;
        while (p1 && p2)
        {
            ListNode *t1 = p1->next, *t2 = p2->next;
            p->next = p1, p1->next = p2;
            p = p2, p1 = t1, p2 = t2;
        }
        if (p1) p->next = p1;
        if (p2) p->next = p2;
        return dummy.next;
    }
};