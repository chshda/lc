// Source: https://oj.leetcode.com/problems/gas-station/

class Solution {
public:
    int canCompleteCircuit(vector<int> &gas, vector<int> &cost) {
        if (gas.empty() || cost.empty() || gas.size() != cost.size()) return 0;
        
        int total = 0, sum = 0, start = 0;
        for (int i = 0; i < gas.size(); i++)
        {
            total += gas[i] - cost[i];
            if (sum < 0) //不能到达i
            {
                sum = gas[i] - cost[i];
                start = i;
            }
            else
            {
                sum += gas[i] - cost[i];
            }
        }
        return total >= 0 ? start : -1; //总和非负则存在
    }
};