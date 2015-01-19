// Source: https://oj.leetcode.com/problems/balanced-binary-tree/

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
    bool isBalanced(TreeNode *root)
    {
        int depth;
        return isBalanced(root, depth);
    }
    bool isBalanced(TreeNode *root, int &depth)
    {
        if (root == NULL) 
        {
            depth = 0; return true;
        }
        
        int l, r;
        if (!isBalanced(root->left, l)) return false;
        if (!isBalanced(root->right, r)) return false;
        if (l - r > 1 || l - r < -1) return false;
        depth = max(l, r) + 1;
        return true;
    }

    int depth(TreeNode *root)
    {
        if (root == NULL) return 0;
        return max(depth(root->left), depth(root->right)) + 1;
    }
    bool isBalanced2(TreeNode *root) {
        if (root == NULL) return true;
        int l = depth(root->left), r = depth(root->right);
        return abs(l-r) <= 1 && isBalanced(root->left) && isBalanced(root->right);
    }
};