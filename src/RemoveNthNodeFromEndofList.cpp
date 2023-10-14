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
        ListNode dummy(-1); //ͷ���
        dummy.next = head;
        
        ListNode *slow = &dummy, *fast = &dummy;
        while (n--) fast = fast->next; //��Ŀ��֤n�ǺϷ���
        while (fast->next) fast = fast->next, slow = slow->next; //slowָ���ɾ�ڵ�ǰһ��
		
        ListNode *tem = slow->next;   //����ڵ�ָ���Թ�ɾ��
        slow->next = slow->next->next;//����ָ�� 
        delete(tem);                  //ɾ���ڵ�
        return dummy.next;
    }
};