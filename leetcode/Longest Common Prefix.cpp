class Solution {
public:
    string longestCommonPrefix(vector<string> &strs) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if (strs.size() == 0)
            return "";
        string res;
        int k, i;
        for (k = 0; k < strs[0].size(); k++) {
            int c = strs[0][k];
            for (i = 0; i < strs.size(); i++) {
                if (strs[i][k] == '\0' || strs[i][k] != c)
                    return res;
            }
            if (i == strs.size())
                res.append(1, c);
        }
        return res;
    }
};
