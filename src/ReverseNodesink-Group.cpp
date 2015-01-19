// Source: https://oj.leetcode.com/problems/reverse-nodes-in-k-group/

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
    ListNode *reverseKGroup(ListNode *head, int k) {
        if (head == NULL || head->next == NULL || k <= 1) return head;
        
        ListNode dummy(-1), *cur = &dummy;
        while (head != NULL)
        {
            ListNode *tail = head; //找到当前的head和tail
            for (int i = 1; tail != NULL && i < k; i++)
                tail = tail->next;
            if (tail == NULL) break;
            
            cur->next = tail, cur = head; //tail为逆转后的头结点，head则为尾节点
            ListNode *tailNext = tail->next; //保存下k个节点的起始地址
            
            ListNode *p1 = NULL, *p2 = head; //head到tail指针逆转
            while (p2 != tailNext)
            {
                ListNode *tem = p2->next;
                p2->next = p1; 
                p1 = p2, p2 = tem;
            }
            
            head = tailNext; //进入下k个节点
        }
        cur->next = head; //最后不足k个的节点顺序不变
        
        return dummy.next;
    }
};