// Source: https://oj.leetcode.com/problems/unique-binary-search-trees-ii/

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
    vector<TreeNode *> generateTrees(int n) {
        return generateTrees(1, n);
    }
    vector<TreeNode *> generateTrees(int st, int ed)
    {
        vector<TreeNode *> ans;
        
        if (st > ed)
        {
            ans.push_back(NULL);
            return ans;
        }
        
        for (int i = st; i <= ed; i++) //枚举根节点
        {
            vector<TreeNode *> left = generateTrees(st, i-1); //左子树
            vector<TreeNode *> right = generateTrees(i+1, ed);//右子树
            for (int j = 0; j < left.size(); j++)
                for (int k = 0; k < right.size(); k++)
                {
                    TreeNode *root = new TreeNode(i);
                    root->left = left[j];
                    root->right = right[k];
                    ans.push_back(root);
                }
        }
        return ans;
    }
};