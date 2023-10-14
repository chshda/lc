// Source: https://oj.leetcode.com/problems/find-peak-element/

class Solution {
public:
    int findPeakElement(const vector<int> &num) {
        int st = 0, ed = num.size() - 1;
        while (st < ed)
        {
            int mid = st + (ed - st) / 2;
            int l = mid > st ? mid - 1 : mid, r = mid < ed ? mid + 1 : mid;
            if (num[mid] >= num[l] && num[mid] >= num[r]) return mid;
            else if (num[l] > num[r]) ed = l;
            else st = r;
        }
        return st;
    }
};