// Source: https://oj.leetcode.com/problems/remove-duplicates-from-sorted-list-ii/

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
    ListNode *deleteDuplicates(ListNode *head) {
        if (head == NULL || head->next == NULL) return head;
        
        ListNode dummy(-1); //辅助头结点
        
        ListNode *p1 = &dummy, *p2 = head; //p1为答案的末尾节点，p2为遍历的当前节点
        while (p2 != NULL)
        {
            if (p2->next == NULL || p2->val != p2->next->val)
                p1->next = p2, p1 = p1->next, p2 = p2->next;
            else //p2与下一个节点的值相同
            {
                int v = p2->val;
                while(p2 && p2->val == v) //删除所有值等于v的节点
                {
                    ListNode *tem = p2->next;
                    delete(p2);
                    p2 = tem;
                }
            }
        }
        
        p1->next = NULL; //末尾节点的next设置为NULL
        return dummy.next;
    }
};
