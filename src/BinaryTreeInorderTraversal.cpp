// Source: https://oj.leetcode.com/problems/binary-tree-inorder-traversal/

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
    vector<int> inorderTraversal(TreeNode *root) {
        vector<int> ans;
        
        stack<TreeNode *> s;
        TreeNode *p = root;
        while (p != NULL || !s.empty())
        {
            if (p != NULL)
            {
                s.push(p);
                p = p->left;
            }
            else
            {
                p = s.top();
                s.pop();
                ans.push_back(p->val);
                p = p->right;
            }
        }
        return ans;
    }
    
    vector<int> inorderTraversal2(TreeNode *root) {
        vector<int> ans, left, right;
        if (root == NULL) return ans;
        
        left = inorderTraversal(root->left);
        right = inorderTraversal(root->right);
        for (int i = 0; i < left.size(); i++) ans.push_back(left[i]);
        ans.push_back(root->val);
        for (int i = 0; i < right.size(); i++) ans.push_back(right[i]);
        return ans;
    }
};