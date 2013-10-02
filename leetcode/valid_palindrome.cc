class Solution {
public:
    bool isPalindrome(string s) {
        if (s == "")
            return true;
        string t = "";
        for (int i = 0; i < s.size(); i++) {
            if (isalnum(s[i]))
                t += tolower(s[i]);
        }
        int i = 0, j = t.size() - 1;
        while (i < j && t[i] == t[j]) {
            i++; j--;
        }
        return (i >= j);
    }
};
