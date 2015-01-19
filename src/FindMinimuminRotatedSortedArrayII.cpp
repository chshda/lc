// Source: https://oj.leetcode.com/problems/find-minimum-in-rotated-sorted-array-ii/

class Solution {
public:
    int findMin(vector<int> &num) {
        int st = 0, ed = num.size() - 1;
        while (st < ed && num[st] >= num[ed])
        {
            int mid = st + (ed - st) / 2;
            if (num[mid] > num[st])
                st = mid + 1;
            else if(num[mid] < num[st])
                ed = mid;
            else 
                st++;
        }
        return num[st];
    }
    
    int findMin2(vector<int> &num) {
        return *min_element(num.begin(), num.end());
    }
};