// Source: https://oj.leetcode.com/problems/majority-element/

class Solution {
public:
    int majorityElement(vector<int> &num) {
        int t, cnt = 0;
        for (auto p = num.begin(); p != num.end(); p++)
            if (cnt == 0 || *p == t) cnt++, t = *p;
            else cnt--;
        return t;
    }
    
    int majorityElement2(vector<int> &num) {
        nth_element(num.begin(), num.begin() + (num.size()-1)/2, num.end());
        return *(num.begin() + (num.size()-1)/2);
    }
};