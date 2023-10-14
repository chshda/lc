// Source: https://oj.leetcode.com/problems/simplify-path/

class Solution {
public:
    string simplifyPath(string path) {
        stack<string> stk;
        while (!path.empty())
        {
            if (path[0] == '/') //忽略分隔符
            {
                path = path.substr(1); continue;
            }

            int id = path.find_first_of('/');
            string tem; //下个文件名
            if (id == -1) tem = path, path = "";
            else tem = path.substr(0, id), path = path.substr(id + 1);
            
            if (tem == ".") continue; //本级目录
            else if (tem == "..")     //上级目录
            {
                if (!stk.empty()) stk.pop();
            } //下级目录
            else 
                stk.push(tem);

        }
        
        string ans;
        while (!stk.empty())
            ans = "/" + stk.top() + ans, stk.pop();
            
        return ans.empty() ? "/" : ans; //只有根目录情况
    }
};