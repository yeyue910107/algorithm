class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        int len1 = s1.size(), len2 = s2.size(), len3 = s3.size();
        if (len1 + len2 != len3)
            return false;
        s1 = "0"+s1;
        s2 = "0"+s2;
        s3 = "0"+s3;
        memset(flag, -1, sizeof(flag));
        flag[0][0] = 1;
        return match(s1, s2, s3, len1, len2, len3);
    }
private:
    int flag[256][256];
    int match(string s1, string s2, string s3, const int k1, const int k2, const int k3) {
        if (flag[k1][k2] != -1)
            return flag[k1][k2];
        if (k1 > 0 && s1[k1] == s3[k3]) {
            if (match(s1, s2, s3, k1-1, k2, k3-1))
                return flag[k1][k2] = 1;
        }
        if (k2 > 0 && s2[k2] == s3[k3]) {
            if (match(s1, s2, s3, k1, k2-1, k3-1))
                return flag[k1][k2] = 1;
        }
        return flag[k1][k2] = 0;
    }
};
