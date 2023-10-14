// Source: https://oj.leetcode.com/problems/longest-common-prefix/

class Solution {
public:
    string longestCommonPrefix(vector<string> &strs) {
        if (strs.size() == 0) return "";
        
        string ans;
        for (int i = 0; i < strs[0].length(); i++)
        {
            for (int j = 1; j < strs.size(); j++)
                if (strs[j].length()-1 < i || strs[j][i] != strs[0][i]) //长度不够或元素不等
                    return ans;
            ans.push_back(strs[0][i]);
        }
        return ans;
    }
};