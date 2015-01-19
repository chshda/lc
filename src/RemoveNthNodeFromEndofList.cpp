// Source: https://oj.leetcode.com/problems/remove-nth-node-from-end-of-list/

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
    ListNode *removeNthFromEnd(ListNode *head, int n) {
        ListNode dummy(-1); //头结点
        dummy.next = head;
        
        ListNode *slow = &dummy, *fast = &dummy;
        while (n--) fast = fast->next; //题目保证n是合法的
        while (fast->next) fast = fast->next, slow = slow->next; //slow指向待删节点前一个
		
        ListNode *tem = slow->next;   //保存节点指针以供删除
        slow->next = slow->next->next;//调整指针 
        delete(tem);                  //删除节点
        return dummy.next;
    }
};