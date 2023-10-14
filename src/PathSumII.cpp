// Source: https://oj.leetcode.com/problems/path-sum-ii/

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
    vector<vector<int> > pathSum(TreeNode *root, int sum) {
        vector<vector<int> > ans, temans;
        if (root == NULL) return ans;
        
        sum -= root->val;
        if (root->left == NULL && root->right == NULL)
        {
            if (sum == 0)
            {
                vector<int> v; v.push_back(root->val);
                ans.push_back(v); 
                return ans;
            }
        }
        
        if (root->left)
        {
            temans = pathSum(root->left, sum);
            for (int i = 0; i < temans.size(); i++)
            {
                vector<int> v; v.push_back(root->val);
                v.insert(v.end(), temans[i].begin(), temans[i].end());
                ans.push_back(v);
            }
        }
        
        if (root->right)
        {
            temans = pathSum(root->right, sum);
            for (int i = 0; i < temans.size(); i++)
            {
                vector<int> v; v.push_back(root->val);
                v.insert(v.end(), temans[i].begin(), temans[i].end());
                ans.push_back(v);
            }
        }
        
        return ans;
    }
};