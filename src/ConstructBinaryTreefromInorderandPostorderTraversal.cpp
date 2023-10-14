// Source: https://oj.leetcode.com/problems/construct-binary-tree-from-inorder-and-postorder-traversal/

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
    TreeNode *buildTree(vector<int> &inorder, vector<int> &postorder)
    {
        return buildTree(inorder, 0, inorder.size()-1, postorder, 0, inorder.size()-1);
    }
    TreeNode *buildTree(vector<int> &in, int st1, int ed1, vector<int> &post, int st2, int ed2)
    {
        if (st1 > ed1) return NULL;
        
        int i;
        for (i = st1; i <= ed1 && in[i] != post[ed2]; i++) ;

        TreeNode *root = new TreeNode(post[ed2]);
        root->left = buildTree(in, st1, i-1, post, st2, st2+i-1-st1);
        root->right = buildTree(in, i+1, ed1, post, st2+i-st1, ed2-1);
        return root;
    }
};