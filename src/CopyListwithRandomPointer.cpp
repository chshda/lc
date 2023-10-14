// Source: https://oj.leetcode.com/problems/copy-list-with-random-pointer/

/**
 * Definition for singly-linked list with a random pointer.
 * struct RandomListNode {
 *     int label;
 *     RandomListNode *next, *random;
 *     RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
 * };
 */
class Solution {
public:
    RandomListNode *copyRandomList(RandomListNode *head) {
        map<RandomListNode*, RandomListNode*> mp; //新旧节点映射关系
        RandomListNode dummy(-1), *cur = &dummy;
        
        for (RandomListNode *p = head; p != NULL; p = p->next)
        {
            RandomListNode *t = new RandomListNode(p->label);
            mp[p] = t;
            cur->next = t, cur = cur->next;
        }
        
        for (RandomListNode *p = dummy.next, *q = head; p != NULL; p = p->next, q = q->next)
            p->random = mp[q->random];
            
        return dummy.next;
    }
};