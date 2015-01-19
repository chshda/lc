// Source: https://oj.leetcode.com/problems/merge-k-sorted-lists/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    struct cmp //优先队列仿函数
    {
        bool operator()(const ListNode *a, const ListNode *b)
        {
            return a->val > b->val; //需要最小值，使用大于关系
        }
    };
    
    ListNode *mergeKLists(vector<ListNode *> &lists) {
        ListNode dummy(-1), *cur = &dummy; //辅助头结点
        
        priority_queue<ListNode *, vector<ListNode *>, cmp> que; //使用最小堆寻找最小值
        for (auto p = lists.begin(); p != lists.end(); p++)
            if (*p != NULL) //每个链表首元素入队
                que.push(*p); 
        while (!que.empty())
        {
            ListNode *fr = que.top(); que.pop(); //取出当前最小元素
            cur->next = fr, cur = cur->next;
            if (fr->next) que.push(fr->next); //放入该队列下一个元素
        }
        
        return dummy.next;
    }
};