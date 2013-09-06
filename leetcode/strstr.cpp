class Solution {
public:
    char *strStr(char *haystack, char *needle) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if (haystack == NULL || needle == NULL)
            return NULL;
        if (*needle == '\0')
            return haystack;
        int i, j, len1 = strlen(haystack), len2 = strlen(needle);
        for (i = 0; i + len2 <= len1; i++) {
            for (j = 0; *(needle+j) != '\0'; j++) {
                if (*(haystack+i+j) != *(needle+j))
                    break;
            }
            if (*(needle+j) == '\0')
                return haystack+i;
        }
        return NULL;
    }
};
