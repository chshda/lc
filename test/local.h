#include "bits/stdc++.h"
using namespace std;

#define debug(x) cerr << #x << ": " << x << endl

int init_freopen = []() {
    freopen("data/in.txt", "r", stdin);
    freopen("data/out.txt", "w", stdout);
    freopen("data/error.txt", "w", stderr);
    return 0;
}();

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};