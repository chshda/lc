// Source: https://oj.leetcode.com/problems/find-minimum-in-rotated-sorted-array/

class Solution {
public:
    int findMin(vector<int> &num) {
        int st = 0, ed = num.size() - 1;
        while (st < ed && num[st] >= num[ed])
        {
            int mid = st + (ed - st) / 2;
            if (num[st] <= num[mid]) st = mid+1;
            else ed = mid;
        }
        return num[st];
    }
    
    int findMin2(vector<int> &num) {
        return *min_element(num.begin(), num.end());
    }
};