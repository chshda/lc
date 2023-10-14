// Source: https://oj.leetcode.com/problems/sum-root-to-leaf-numbers/

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
    int sumNumbers(TreeNode *root) {
        if (root == NULL) return 0;
        
        int q = 0, ans = 0;
        f(root, q, ans);
        return ans;
    }
    void f(TreeNode *root, int q, int &ans)
    {
        if (root->left && root->right)
            f(root->left, q*10+root->val, ans),
            f(root->right, q*10+root->val, ans);
        else if (root->left)
            f(root->left, q*10+root->val, ans);
        else if (root->right)
            f(root->right, q*10+root->val, ans);
        else
            ans += q*10 + root->val;
    }
};