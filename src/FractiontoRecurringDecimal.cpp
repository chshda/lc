// Source: https://oj.leetcode.com/problems/fraction-to-recurring-decimal/

class Solution {
public:
    string fractionToDecimal(int numerator, int denominator) {
        if (numerator == 0) return "0";
        if (denominator == 0) return to_string(INT_MAX);
        
        string ans;
        if ((numerator>0) ^ (denominator>0)) ans += '-';
        
        long long a = abs((long long)numerator), b = abs((long long)denominator);
        ans += to_string(a/b);
        a %= b;
        if (a == 0) return ans;
        ans += '.';
        
        map<int, int> mp;
        while (a != 0)
        {
            if (mp.find(a) != mp.end())
            {
                ans.insert(mp[a], "(");
                ans += ")";
                break;
            }
            
            mp[a] = ans.size();
            
            a *= 10; 
            ans += to_string(a / b);
            a %= b;
        }
        
        return ans;
    }
};