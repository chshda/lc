// Source: https://oj.leetcode.com/problems/convert-sorted-array-to-binary-search-tree/

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
    TreeNode *sortedArrayToBST(vector<int> &num) {
        if (num.empty()) return NULL;
        return sortedArrayToBst(0, num.size()-1, num);
    }
    TreeNode *sortedArrayToBst(int st, int ed, vector<int> &num)
    {
        if (st > ed) return NULL;
        int mid = (st + ed) / 2;
        TreeNode *root = new TreeNode(num[mid]);
        root->left = sortedArrayToBst(st, mid-1, num);
        root->right = sortedArrayToBst(mid+1, ed, num);
        return root;
    }
};