// Source: https://oj.leetcode.com/problems/anagrams/

class Solution {
public:
    vector<string> anagrams(vector<string> &strs) {
        map<string, int> mp;
        vector<string> ans;
        for (int i = 0; i < strs.size(); i++)
        {
            string tem = strs[i];
            sort(tem.begin(), tem.end()); //排序，使anagrams变得一样
            if (mp.find(tem) == mp.end())
                mp[tem] = i;
            else
            {
                if (mp[tem] >= 0) //已有anagrams，保存第一个
                    ans.push_back(strs[mp[tem]]), mp[tem] = -1; 
                ans.push_back(strs[i]);
            }
        }
        return ans;
    }
};