#include<cstdio>
#include<cstdlib>
#include<iostream>
using std::cin;
using std::cout;
using std::endl;

const int maxn = 100000 + 10;
int left[maxn]; // 存储结点的前驱
int right[maxn]; // 存储结点的后继
int n, m, inv;
void init() {
    for (int i = 0; i < maxn - 1; i++) right[i] = i + 1;
    for (int i = 1; i <= maxn - 1; i++) left[i] = i - 1;
}
void link(int x, int y) {
    // 连接x->y
    if (inv == 0) { right[x] = y; left[y] = x; }
    else { left[x] = y; right[y] = x; }
}
void printLink() {
    int head, curr;
    if (inv == 0) head = 0;
    else head = n + 1;
    cout << "当前链表:";
    if (inv == 0) curr = right[head];
    else curr = left[head];
    while (curr <= n && curr > 0) {
        cout << curr << " ";
        head = curr;
        if (inv == 0) curr = right[head];
        else curr = left[head];
    }
    cout << std::endl;
}
int main() {
    int kcase = 1;
    while (cin >> n >> m) {
        inv = 0;
        init(); 
        int cmd, x, y;
        for (int i = 0; i < m; i++) {
            cin >> cmd;
            int px, lx, py, ly;
            if (cmd != 4) {
                cin >> x >> y;
                px = left[x], lx = right[x]; // 前驱和后继
                py = left[y], ly = right[y];
                if (inv) { // 若已经经历过翻转了，则前驱后继需要翻转
                    int t = px; px = lx; lx = t;
                    t = py; py = ly; ly = t;
                }
                //printf("px=%d,lx=%d,py=%d,ly=%d\n", px, lx, py, ly);
            }
            switch (cmd) {
            case 1: {
                if (py == x) break;
                link(px, lx);// 删除x
                link(py, x); link(x, y);// 插入x到y的左边
                break;
            }
            case 2: {
                if (ly == x) break;
                link(px, lx);// 删除x
                link(y, x); link(x, ly);// 插入x到y的右边
                break;
            }
            case 3: {
                // 相邻交换需要特判
                if (py == x) {
                    link(px, y); link(y, x); link(x, ly);
                    break;
                }
                else if (px == y) {
                    link(py, x); link(x, y); link(y, lx);
                    break;
                }
                link(px, y); link(y, lx);
                link(py, x); link(x, ly); // 交换x和y
                break;
            }   
            case 4: 
                inv = !inv; break;
            }// switch
            //printLink();
        }
        int head;
        if (inv) head = n + 1;
        else head = 0;
        long long sum = 0;
        int pos = 0, curr;
        while (pos < n) {
            if(inv == 0) curr = right[head]; 
            else curr = left[head];
            pos++;
            if (pos & 1) sum += curr;
            head = curr;
        }
        printf("Case %d: %lld\n", kcase,sum);
        kcase++;
    }

    return 0;
}