// Source: https://oj.leetcode.com/problems/largest-number/

class Solution {
public:
    struct cmp
    {
        bool operator()(const int &a, const int &b)
        {
           string sa = to_string(a), sb = to_string(b);
           if (sa + sb > sb + sa) return 1; //需要ab > ba
           else return 0;
        }
    };
    string largestNumber(vector<int> &num) {
        sort(num.begin(), num.end(), cmp());
        string ans;
        for (int i = 0; i < num.size(); ++i)
            ans += to_string(num[i]);
        
        if (ans.find_first_not_of('0') == string::npos) //去除前导0
            ans = "0";
        else
            ans = ans.substr(ans.find_first_not_of('0'));
        return ans;
        
    }
};