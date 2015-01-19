// Source: https://oj.leetcode.com/problems/add-two-numbers/

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
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
        ListNode dummy(-1), *p = &dummy; //标记用的头结点
        
        int carry = 0; //进位
        while (l1 != NULL && l2 != NULL)
        {
            int t = l1->val + l2->val + carry;
            if (t >= 10) t -= 10, carry = 1;
            else carry = 0;
            p->next = new ListNode(t);
            p = p->next, l1 = l1->next, l2 = l2->next;
        }
        
        while (l1 != NULL) //l1较长
        {
            int t = l1->val + carry;
            if (t >= 10) t -= 10, carry = 1;
            else carry = 0;
            p->next = new ListNode(t);
            p = p->next, l1 = l1->next;
        }
        while (l2 != NULL) //l2较长
        {
            int t = l2->val + carry;
            if (t >= 10) t -= 10, carry = 1;
            else carry = 0;
            p->next = new ListNode(t);
            p = p->next, l2 = l2->next;
        }
        
        if (carry) //还有进位
            p->next = new ListNode(1);
            
        return dummy.next;
    }
};