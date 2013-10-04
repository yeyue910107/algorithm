#include <iostream>
#include <map>
#include <ctime>
#include <cstdlib>

using namespace std;

enum { MAX = 10 };

struct RandomListNode {
     int label;
     RandomListNode *next, *random;
     RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
};

class Solution {
public:
    RandomListNode *copyRandomList(RandomListNode *head) {
        RandomListNode *newhead = NULL, *p, *q;
        map<RandomListNode*, RandomListNode*> _map;
        map<RandomListNode*, RandomListNode*>::iterator it1, it2;
        p = head;
        while (p != NULL) {
            RandomListNode *r1, *r2;
            it1 = _map.find(p);
            if (it1 == _map.end()) {
                r1 = new RandomListNode(p->label);
                _map.insert(pair<RandomListNode*, RandomListNode*>(p, r1));
            }
            else {
                r1 = it1->second;
            }
            if (p->random == NULL)
                r2 = NULL;
            else {
                it2 = _map.find(p->random);
                if (it2 == _map.end()) {
                    r2 = new RandomListNode(p->random->label);
                    _map.insert(pair<RandomListNode*, RandomListNode*>(p->random, r2));
                }
                else {
                    r2 = it2->second;
                }
            }
            if (newhead == NULL) {
                newhead = r1;
                q = newhead;
                q->random = r2;
            }
            else {
                q->next = r1;
                q = r1;
                q->random = r2;
            }
            p = p->next;
        }
		return newhead;
    }
};

int main() {
	RandomListNode *head = NULL, *p;
	RandomListNode *rdlist[MAX];
	srand((unsigned)time(0));
	for (int i = 0; i < MAX; i++) {
		RandomListNode *r = new RandomListNode(i);
		rdlist[i] = r;
	}
	for (int i = 0; i < MAX; i++) {
		if (head == NULL) {
			head = rdlist[0];
			p = head;
		}
		else {
			p->next = rdlist[i];
			p = rdlist[i];
		}
		p->random = rdlist[rand() % MAX];
	}
	RandomListNode *newhead;
	Solution s;
	newhead = s.copyRandomList(head);
	return 0;
}
