// Source: https://oj.leetcode.com/problems/binary-tree-zigzag-level-order-traversal/

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
    vector<vector<int> > zigzagLevelOrder(TreeNode *root) {
        vector<vector<int> > ans;
        if (root == NULL) return ans;
        
        queue<TreeNode *> q;
        q.push(root);
        int cnt = 1, ncnt;
        while (!q.empty())
        {
            ncnt = 0;
            vector<int> v;
            while (cnt--) //当前层的节点数
            {
                TreeNode *fr = q.front(); q.pop();
                v.push_back(fr->val);
                if (fr->left)  q.push(fr->left), ncnt++;
                if (fr->right) q.push(fr->right), ncnt++;
            }
            ans.push_back(v);
            cnt = ncnt;
        }
        
        for (int i = 1; i < ans.size(); i += 2) reverse(ans[i].begin(), ans[i].end());
        return ans;
    }
};