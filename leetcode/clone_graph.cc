#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <queue>

using namespace std;

struct UndirectedGraphNode {
    int label;
    vector<UndirectedGraphNode *> neighbors;
    UndirectedGraphNode(int x) : label(x) {};
 };

class Solution {
public:
    UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node) {
        if (node == NULL) return NULL;
        map<UndirectedGraphNode*, UndirectedGraphNode*> _map;
        set<UndirectedGraphNode*> flag;
        queue<UndirectedGraphNode*> q;
        q.push(node);
        UndirectedGraphNode* _node = new UndirectedGraphNode(node->label);
        _map.insert(pair<UndirectedGraphNode*, UndirectedGraphNode*>(node, _node));

        while (!q.empty()) {
            UndirectedGraphNode* p = q.front(), *pp = _map[p];
            q.pop();
            if (flag.find(p) != flag.end())
                continue;
            flag.insert(p);
            for (int i = 0; i < p->neighbors.size(); i++) {
                map<UndirectedGraphNode*, UndirectedGraphNode*>::iterator it = _map.find(p->neighbors[i]);
                if (it == _map.end()) {
                    UndirectedGraphNode *pn = new UndirectedGraphNode(p->neighbors[i]->label);
                    _map.insert(pair<UndirectedGraphNode*, UndirectedGraphNode*>(p->neighbors[i], pn));
                    pp->neighbors.push_back(pn);
                }
                else pp->neighbors.push_back(it->second);
                q.push(p->neighbors[i]);
            }
        }
        return _node;
    }
};

int main() {
    vector<UndirectedGraphNode*> v;
    for (int i = 0; i < 3; i++) {
        v.push_back(new UndirectedGraphNode(i));
    }
    v[0]->neighbors.push_back(v[1]);
    v[0]->neighbors.push_back(v[2]);
    v[1]->neighbors.push_back(v[2]);
    v[2]->neighbors.push_back(v[2]);
    Solution s;
    UndirectedGraphNode *node = s.cloneGraph(v[0]);
    return 0;
}
