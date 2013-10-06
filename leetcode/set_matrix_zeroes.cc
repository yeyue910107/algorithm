#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    void setZeroes(vector<vector<int> > &matrix) {
        int m = matrix.size();
	    if (m == 0) return;
	    int n = matrix[0].size(), mm, nn, i, j;
	    if (n == 0) return;
	    bool flag = false;
	    for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++) {
	  	    if (matrix[i][j] == 0) {
			mm = i; nn = j;
			flag = true;
			break;
		    }
		}
		if (flag) break;
	    }
	    if (i == m && j == n)
		return;
	    for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++) {
	  	    if (matrix[i][j] == 0) {
			matrix[mm][j] = 0;
			matrix[i][nn] = 0;
		    }	
		}
	    }
	    for (i = 0; i < m; i++) {
		if (i != mm && matrix[i][nn] == 0) {
		    for (j = 0; j < n; j++) {
			if (j != nn)
			    matrix[i][j] = 0;
		    }
		}
	    }
	    for (j = 0; j < n; j++) {
		if (j != nn && matrix[mm][j] == 0) {
		    for (i = 0; i < m; i++) {
			if (i != mm)
		 	    matrix[i][j] = 0;
		    }
		}
	    }
	    for (i = 0; i < m; i++)
		matrix[i][nn] = 0;
	    for (j = 0; j < n; j++)
		matrix[mm][j] = 0;
    }
};

int main() {
    int a[4][4] = {-5,7,2147483647,3, 0,3,6,-2147483648, 8,3,-3,-6, -9,-9,8,0};
    vector<vector<int>> matrix;
    for (int i = 0; i < 4; i++) {
	vector<int> row;
	for (int j = 0; j < 4; j++)
	    row.push_back(a[i][j]);
	matrix.push_back(row);
    }
    Solution s;
    s.setZeroes(matrix);
    return 0;
}
