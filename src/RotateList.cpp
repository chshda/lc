// Source: https://oj.leetcode.com/problems/rotate-list/

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
    ListNode *rotateRight(ListNode *head, int k) {
        if (head == NULL) return NULL;
        
        int len = 1; //链表长度
        ListNode *last = head; //最后一个节点
        while (last->next != NULL) last = last->next, len++;
        
        k %= len; 
        if (k == 0) return head;
        
        ListNode *slow = head, *fast = head;
        for (int i = 0; i <= k; i++) //slow位置0，fast位置k+1
            fast = fast->next;
        while (fast != NULL)         //slow位置n-k-1，fast位置n
            fast = fast->next, slow = slow->next;
        
        ListNode *ans = slow->next; //slow的next为新的头
        slow->next = NULL;
        last->next = head;
        return ans;
    }
};