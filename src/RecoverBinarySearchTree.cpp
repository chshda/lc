// Source: https://oj.leetcode.com/problems/recover-binary-search-tree/

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
    TreeNode *p1 = NULL, *p2 = NULL, *pre = NULL;
    void inorder(TreeNode *root)
    {
        if (root == NULL) return;
        
        inorder(root->left);
        
        if (pre && pre->val > root->val)
        {
            if (p1 == NULL) p1 = pre, p2 = root;
            else p2 = root;
        }
        
        pre = root;
        inorder(root->right);
    }
    void recoverTree(TreeNode *root) {
        inorder(root);
        swap(p1->val, p2->val);
    }

    // O(n) space，交换中序遍历中乱序的两个数字
    void inorder(TreeNode *root, vector<TreeNode *> &v)
    {
        if (root == NULL) return;
        inorder(root->left, v);
        v.push_back(root);
        inorder(root->right, v);
    }
    void recoverTree2(TreeNode *root) {
        vector<TreeNode *> v;
        inorder(root, v);
        
        TreeNode *p1 = NULL, *p2 = NULL;
        for (int i = 0; i < v.size() - 1; i++)
        {
            if (v[i]->val > v[i+1]->val)
            {
                if (p1 == NULL)
                    p1 = v[i], p2 = v[i+1];
                else
                    p2 = v[i+1];
            }
        }
        
        swap(p1->val, p2->val);
    }
};