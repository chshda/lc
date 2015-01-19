// Source: https://oj.leetcode.com/problems/binary-tree-preorder-traversal/

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
    vector<int> preorderTraversal(TreeNode *root) { //栈模拟递归
        vector<int> ans;
        if (root == NULL) return ans;
        
        stack<TreeNode *> s;
        s.push(root);
        while (!s.empty())
        {
            TreeNode *t = s.top(); 
            s.pop(); ans.push_back(t->val);
            if (t->right) s.push(t->right); //右儿子先
            if (t->left) s.push(t->left);
        }
        return ans;
    }
    
    vector<int> preorderTraversal2(TreeNode *root) { //递归
        vector<int> ans, tem;
        if (root == NULL) return ans;
        
        ans.push_back(root->val);
        
        tem = preorderTraversal(root->left);
        for (int i = 0; i < tem.size(); i++) ans.push_back(tem[i]);
        
        tem = preorderTraversal(root->right);
        for (int i = 0; i < tem.size(); i++) ans.push_back(tem[i]);
        
        return ans;
    }
};