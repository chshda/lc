// Source: https://oj.leetcode.com/problems/binary-tree-postorder-traversal/

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
    vector<int> postorderTraversal(TreeNode *root) { //栈模拟递归
        vector<int> ans;
        if (root == NULL) return ans;
        
        stack<TreeNode *> s;
        s.push(root);
        while (!s.empty())
        {
            TreeNode *t = s.top(); s.pop(); 
            if (t->left) s.push(t->left); //左儿子先
            if (t->right) s.push(t->right);
            ans.push_back(t->val);
        }
        
        reverse(ans.begin(), ans.end()); //翻转
        return ans;
    }
    
    vector<int> postorderTraversal2(TreeNode *root) { //递归
        vector<int> ans, l, r;
        if (root == NULL) return ans;
        
        if (root->left) l = postorderTraversal(root->left);
        if (root->right) r = postorderTraversal(root->right);
        
        for (int i = 0; i < l.size(); i++) ans.push_back(l[i]);
        for (int i = 0; i < r.size(); i++) ans.push_back(r[i]);
        ans.push_back(root->val);
        return ans;
    }
};