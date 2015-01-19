// Source: https://oj.leetcode.com/problems/path-sum/

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
    bool hasPathSum(TreeNode *root, int sum) {
        if (root == NULL) return false;
        
        sum -= root->val;
        if (root->left == NULL && root->right == NULL)
            return sum == 0;
        
        if (root->left && hasPathSum(root->left, sum)) return true;
        if (root->right && hasPathSum(root->right, sum)) return true;
        return false;
    }
};