// Source: https://oj.leetcode.com/problems/binary-tree-maximum-path-sum/

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
    int maxPathSum(TreeNode *root) {
        long long ans, mx;
        f(root, ans, mx);
        return ans;
    }
    void f(TreeNode *root, long long &ans, long long &mx)
    {
        if (root == NULL)
        {
            ans = mx = INT_MIN; return;
        }
        
        mx = ans = root->val;
        long long ansl, mxl; f(root->left, ansl, mxl);
        long long ansr, mxr; f(root->right, ansr, mxr);
        
        mx = mxl > mxr ? max(mx, mx+mxl) : max(mx, mx+mxr);
        ans = max(max(ansl, ansr), max(mx, mxl+mxr+root->val));
    }
};