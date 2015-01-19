// Source: https://oj.leetcode.com/problems/two-sum/

class Solution {
public:
    vector<int> twoSum(vector<int> &numbers, int target) {
        vector<int> ans;
        unordered_map<int, int> mp; //哈希表
        for (int i = 0; i < numbers.size(); ++i)
        {
            auto p = mp.find(target - numbers[i]);
            if (p != mp.end())
            {
                ans.push_back(p->second + 1); //注意是p先
                ans.push_back(i + 1);
                return ans;
            }
            mp.insert(pair<int,int>(numbers[i], i));
        }
    }
};