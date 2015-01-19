// Source: https://oj.leetcode.com/problems/symmetric-tree/

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
    bool f(TreeNode *left, TreeNode *right) {
        if (left == NULL && right == NULL) return true;
        if (left == NULL || right == NULL) return false;
        return left->val == right->val && f(left->left, right->right) && f(left->right, right->left);
    }
    
    bool isSymmetric(TreeNode *root) {
        return f(root, root);
    }
};