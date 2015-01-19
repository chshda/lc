// Source: https://oj.leetcode.com/problems/binary-search-tree-iterator/

/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class BSTIterator {
public:
    BSTIterator(TreeNode *root) {
        push(root);
    }

    /** @return whether we have a next smallest number */
    bool hasNext() {
        return !stk.empty();
    }

    /** @return the next smallest number */
    int next() {
        TreeNode *top = stk.top(); stk.pop();
        push(top->right);
        return top->val;
    }
    
    void push(TreeNode *root) //根节点及左儿子入栈
    {
        if (root == NULL) return;
        while (root != NULL)
            stk.push(root), root = root->left;
    }
    
private:
    stack<TreeNode *> stk;
};

/**
 * Your BSTIterator will be called like this:
 * BSTIterator i = BSTIterator(root);
 * while (i.hasNext()) cout << i.next();
 */