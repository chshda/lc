// Source: https://oj.leetcode.com/problems/text-justification/

class Solution {
public:
    vector<string> fullJustify(vector<string> &words, int L) {
        vector<string> ans;
        for (int i = 0, j = 0, sum = 0; j < words.size(); j++) //i为起点单词，j为终点单词
        {
            sum += words[j].size() + 1; //当前单词所占长度，包括一个空格
            if (j == words.size() - 1) //到达末尾
            {
                string tem = words[i]; //从左到右摆放
                for (int k = i + 1; k <= j; k++) tem += " " + words[k];
                tem += string(L - tem.size(), ' '); //补充空格
                ans.push_back(tem);
            }
            else if (sum + words[j+1].size() > L) //加上下一个单词的话长度会超，输出一行
            {
                sum = L - (sum - (j - i + 1)); //空格数
                int num = j - i; //单词数-1，间隙数
                if (num == 0) //只有一个单词需要额外讨论
                {
                    ans.push_back(words[i] + string(L - words[i].size(), ' '));
                }
                else
                {
                    int a = sum / num, b = sum % num; //平均每个单词后接a个空格，前b个单词的空格长度多1
                    string tem;
                    for (int k = i; k < i + b; k++) tem += words[k] + string(a + 1, ' ');
                    for (int k = i + b; k < j; k++) tem += words[k] + string(a, ' ');
                    tem += words[j];
                    ans.push_back(tem);
                }
                i = j + 1, sum = 0; //设置新的起点和长度
            }
        }
        return ans;
    }
};