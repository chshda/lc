// Source: https://oj.leetcode.com/problems/clone-graph/

/**
 * Definition for undirected graph.
 * struct UndirectedGraphNode {
 *     int label;
 *     vector<UndirectedGraphNode *> neighbors;
 *     UndirectedGraphNode(int x) : label(x) {};
 * };
 */
class Solution {
public:
    UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node) {
        if (node == NULL) return NULL;
        
        map<UndirectedGraphNode *, UndirectedGraphNode*> mp; //新旧节点映射关系
        UndirectedGraphNode *newnode = new UndirectedGraphNode(node->label);
        mp[node] = newnode;
        
        queue<UndirectedGraphNode *> que;
        que.push(node);
        while (!que.empty())
        {
            UndirectedGraphNode *t = que.front(), *newt = mp[t];
            que.pop();
            
            for (auto p = t->neighbors.begin(); p != t->neighbors.end(); p++)
            {
                UndirectedGraphNode *newp;
                if (mp.find(*p) != mp.end()) newp = mp[*p];
                else
                {
                    newp = new UndirectedGraphNode((*p)->label);
                    mp[*p] = newp;
                    que.push(*p);
                }
                newt->neighbors.push_back(newp);
            }
        }
        
        return newnode;
    }
};