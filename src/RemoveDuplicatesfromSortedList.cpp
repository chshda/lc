// Source: https://oj.leetcode.com/problems/remove-duplicates-from-sorted-list/

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
        for (ListNode *p = head; p && p->next;)
            if (p->val == p->next->val) //p和下一个节点值相同
            {
                ListNode *tem = p->next->next; //保存下下个节点
                delete p->next; //删除下一个节点
                p->next = tem; //修改指针，继续遍历
            }
            else
                p = p->next;
        return head;
    }
};