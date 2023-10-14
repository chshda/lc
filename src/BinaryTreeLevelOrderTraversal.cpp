// Source: https://oj.leetcode.com/problems/binary-tree-level-order-traversal/

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
    vector<vector<int> > levelOrder(TreeNode *root) {
        vector<vector<int> > ans;
        if (root == NULL) return ans;
        
        queue<TreeNode *> q;
        q.push(root);
        while (!q.empty())
        {
            int len = q.size(); 
            vector<int> v;
            while (len--)
            {
                TreeNode *fr = q.front(); q.pop();
                v.push_back(fr->val);
                if (fr->left) q.push(fr->left);
                if (fr->right) q.push(fr->right);
            }
            ans.push_back(v);
        }
        return ans;
    }
};