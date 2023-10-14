// Source: https://oj.leetcode.com/problems/populating-next-right-pointers-in-each-node-ii/

/**
 * Definition for binary tree with next pointer.
 * struct TreeLinkNode {
 *  int val;
 *  TreeLinkNode *left, *right, *next;
 *  TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
 * };
 */
class Solution {
public:
    void connect(TreeLinkNode *root) {
        if (root == NULL) return;
        
        if (root->left)
        {
            if (root->right)
                root->left->next = root->right;
            else
            {
                TreeLinkNode *p = root->next;
                while (p && !p->left && !p->right) p = p->next;
                if (p == NULL)   root->left->next = NULL;
                else if(p->left) root->left->next = p->left;
                else             root->left->next = p->right;
            }
        }
        if (root->right)
        {
            TreeLinkNode *p = root->next;
            while (p && !p->left && !p->right) p = p->next;
            if (p == NULL)   root->right->next = NULL;
            else if(p->left) root->right->next = p->left;
            else             root->right->next = p->right;
        }
            
        connect(root->right);
        connect(root->left);
    }
};