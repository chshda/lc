// Source: https://oj.leetcode.com/problems/binary-tree-level-order-traversal-ii/

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
    vector<vector<int> > levelOrderBottom(TreeNode *root) {
        vector<vector<int> > ans;
        if (root == NULL) return ans;
        
        queue<TreeNode *> q;
        q.push(root);
        while (!q.empty())
        {
            int len = q.size();
            vector<int> v;
            while (len--) //此时的队列长度即为下一层的节点个数
            {
                TreeNode *t = q.front(); q.pop();
                v.push_back(t->val);
                if (t->left) q.push(t->left);
                if (t->right) q.push(t->right);
            }
            ans.push_back(v);
        }
        
        reverse(ans.begin(), ans.end());
        return ans;
    }
};