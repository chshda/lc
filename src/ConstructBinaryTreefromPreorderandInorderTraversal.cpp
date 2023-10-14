// Source: https://oj.leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/

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
    TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder) {
        return buildTree(preorder, 0, preorder.size()-1, inorder, 0, inorder.size()-1);
    }
    TreeNode *buildTree(vector<int> &pre, int st1, int ed1, vector<int> &in, int st2, int ed2)
    {
        if (st1 > ed1) return NULL;
        
        int i;
        for (i = st2; i <= ed2 && in[i] != pre[st1]; i++) ;
        
        TreeNode *root = new TreeNode(pre[st1]);
        root->left = buildTree(pre, st1+1, st1+i-st2, in, st2, i-1);
        root->right = buildTree(pre, st1+i-st2+1, ed1, in, i+1, ed2);
        return root;
    }
};