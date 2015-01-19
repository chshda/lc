// Source:  https://oj.leetcode.com/problems/flatten-binary-tree-to-linked-list/

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
    void flatten(TreeNode *root) { //深度优先搜索
        if (root == NULL) return;
        
        vector<TreeNode *> v, s;
        s.push_back(root); //深搜栈
        while (!s.empty())
        {
            TreeNode *t = s.back();
            s.pop_back(); v.push_back(t);
            if (t && t->right) s.push_back(t->right);
            if (t && t->left) s.push_back(t->left);
        }
        
        for (int i = 0; i < v.size(); i++)
        {
            v[i]->left = NULL;
            v[i]->right = i == v.size()-1 ? NULL : v[i+1];
        }
    }
    
    void flatten2(TreeNode *root) { //递归
        if (root == NULL) return;
        
        TreeNode *left = root->left ? root->left : NULL;
        TreeNode *right = root->right ? root->right : NULL;
        root->left = root->right = NULL;
        
        if (left)
        {
            flatten(left);
            root->right = left;
        }
        if (right)
        {
            flatten(right);
            TreeNode *tem = root; 
            while (tem->right) tem = tem->right;
            tem->right = right;
        }
    }
};