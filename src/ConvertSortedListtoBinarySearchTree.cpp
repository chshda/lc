// Source: https://oj.leetcode.com/problems/convert-sorted-list-to-binary-search-tree/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode *sortedListToBST(ListNode *head) { //O(n)
        int n = 0;
        for (ListNode *p = head; p != NULL; p = p->next) n++;
        return sortedListToBst(n, head);
    }
    TreeNode *sortedListToBst(int n, ListNode*& head)
    {
        if (n <= 0 || head == NULL) return NULL;
        int mid = n / 2;
        TreeNode *left = sortedListToBst(n/2, head);
        TreeNode *root = new TreeNode(head->val);
        head = head->next;
        root->left = left;
        root->right = sortedListToBst(n - mid - 1, head);
        return root;
    }
    
    TreeNode *sortedListToBST2(ListNode *head) { //O(nlogn)
        if (head == NULL) return NULL;
        if (head->next == NULL) return new TreeNode(head->val);
        
        ListNode *slow = head, *fast = head, *pre = NULL; //寻找中点
        while (fast && fast->next)
            pre = slow, slow = slow->next, fast = fast->next->next;
        pre->next = NULL;
        TreeNode *root = new TreeNode(slow->val);
        root->left = sortedListToBST(head);
        root->right = sortedListToBST(slow->next);
        return root;
    }
};