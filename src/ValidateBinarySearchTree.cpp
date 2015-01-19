// Source: https://oj.leetcode.com/problems/validate-binary-search-tree/

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
    bool isValidBST(TreeNode *root) { //非递归，判断中序遍历是否有序
        vector<int> v;
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
                v.push_back(p->val);
                p = p->right;
            }
        }
        
        for (int i = 1; i < v.size(); i++)
            if (v[i-1] >= v[i]) return false;
        return true;
    }
    
    bool isValidBST2(TreeNode *root) { //递归
        if (root == NULL) return true;
        
        if (root->left)
        {
            if (!isValidBST(root->left)) return false;
            if (getminmax(root->left, true) >= root->val) return false;
        }
        if (root->right)
        {
            if (!isValidBST(root->right)) return false;
            if (getminmax(root->right, false) <= root->val) return false;
        }
        return true;
    }
    int getminmax(TreeNode *root, bool flag)
    {
        int ans = root->val;
        if (root->left) ans = flag ? max(ans, getminmax(root->left, flag)) : min(ans, getminmax(root->left, flag));
        if (root->right) ans = flag ? max(ans, getminmax(root->right, flag)) : min(ans, getminmax(root->right, flag));
        return ans;
    }
};