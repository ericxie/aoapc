#include<stdio.h>
#include<string.h>
#include<iostream>
#include<algorithm>
#define maxn 100100
using namespace std;
typedef struct Node {
    int value;
    Node* next[10];
    Node() {
        value = -1;
        for (int i = 0; i < 10; i++)
            next[i] = NULL;
    }
} Node, *Tree;

int num[2][maxn];
Tree head;

void addNode(int *s, int len, int n) {
    Node* p = head;
    for (int i = 0; i < len; i++) {
        int x = s[i];
        if (p->next[x] == NULL)
            p->next[x] = new Node;
        p = p->next[x];
        if (p->value == -1)
            p->value = n;
    }
}

//计算斐波那契额数并创建字典树
void getFibAndTree() {
    head = new Node;
    head->next[1] = new Node;
    head->next[1]->value = 0;
    memset(num, 0, sizeof(num));
    num[0][0] = num[1][0] = 1;
    int b = 0, e = 1, flag = 0;
    for (int i = 2; i < 100000; i++) {
        int jw = 0;
        for (int j = b; j < e; j++) {
            int t = num[0][j] + num[1][j] + jw;
            jw = 0;
            if (t > 9)
                jw = 1;
            num[flag][j] = t % 10;
        }
        if (jw)
            num[flag][e++] = 1;
        if (e - b > 50)
            b++;
        int len = e - b;
        if (len > 40)
            len = 40;
        int cc[len];
        for (int x = 0; x < len; x++)
            cc[x] = num[flag][e - 1 - x];
        addNode(cc, len, i);
        flag = !flag;
    }
}
//搜索
int msearch(char *in) {
    int len = strlen(in);
    Node* p = head;
    for (int i = 0; i < len; i++) {
        if (p->next[in[i] - '0'] == NULL)
            return -1;
        p = p->next[in[i] - '0'];
    }
    return p->value;
}

int main() {
    getFibAndTree();
    char in[45];
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> in;
        printf("Case #%d: %d\n", i, msearch(in));
    }
}
