#include <iostream>
#include <fstream>
#include <queue>
#include <algorithm>

using namespace std;
const int MAX = 128;
int cases, m, n, startx, starty, endx, endy, res;
int s[MAX][MAX];
bool visit[MAX][MAX];
int dp[MAX][MAX];
const int dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1, 0};

struct Point {
    int x, y, step, power;
    Point() {}
    Point(int x, int y) : x(x), y(y) { step = 0; power = 0; }
    Point(int x, int y, int step, int power) : x(x), y(y), step(step), power(power) { }
};

bool bfs() {
    queue<Point> q;
    int minstep = -1;
    q.push(Point(startx, starty, 0, s[startx][starty]));
    while (!q.empty()) {
        Point cur = q.front();
        q.pop();
        
        int x = cur.x, y = cur.y, step = cur.step, power = cur.power;
        visit[x][y] = true;
        
        for (int i = 0; i < 4; i++) {
            int xx = x + dx[i], yy = y + dy[i];
            if (xx < 0 || xx >= m || yy < 0 || yy >= n || visit[xx][yy] || s[xx][yy] == -1)
                continue;
            if (minstep != -1 && step > minstep)
                break;
            if (xx == endx && yy == endy) {
                if (minstep == -1)
                    minstep = step;
                res = max(res, power + s[xx][yy]);
            }
            if (power + s[xx][yy] < dp[xx][yy])
                continue;
            dp[xx][yy] = power + s[xx][yy];
            q.push(Point(xx, yy, step + 1, power + s[xx][yy]));
        }
    }
    return (res == -1) ? false : true;
}

int main() {
    fstream in, out;
    in.open("in.txt", ios::in);
    out.open("out.txt", ios::out);
    
    in >> cases;
    for (int i = 1; i <= cases; i++) {
        in >> m >> n;
        in >> startx >> starty >> endx >> endy;
        memset(visit, false, sizeof(visit));
        for (int j = 0; j < m; j++) {
            for (int k = 0; k < n; k++) {
                in >> s[j][k];
                dp[j][k] = INT_MIN;
            }
        }
        res = -1;
        bool flag = false;
        if (s[startx][starty] != -1 && s[endx][endy] != -1) {
            if (bfs())
                flag = true;
        }
        if (flag)
            out << "Case #" << i << ": " << res << "\r\n";
        else
            out << "Case #" << i << ": " << "Mission Impossible." << "\r\n";
    }
    in.close();
    out.close();
    
    return 0;
}
