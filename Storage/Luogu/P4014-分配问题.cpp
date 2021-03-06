#include <bits/stdc++.h>
using namespace std;

namespace IO {
    
inline char mygetchar() {
    static char ff[100000], *A = ff, *B = ff;
    return A == B && (B = (A = ff) + fread(ff, 1, 100000, stdin), A == B)
               ? EOF
               : *A++;
}

template <typename T = int> T read() {
    T x = 0, s = 1;
    char c = mygetchar();
    while (c < '0' || '9' < c) {
        if (c == '-')
            s = -1;
        c = mygetchar();
    }
    while ('0' <= c && c <= '9') {
        x = (x << 1) + (x << 3) + (c ^ 48);
        c = mygetchar();
    }
    return x * s;
}

template <typename T = int> void writeln(T x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    static int stk[100];
    int top = 0;
    if (x == 0)
        stk[++top] = 0;
    while (x) {
        stk[++top] = x % 10;
        x /= 10;
    }
    while (top)
        putchar(stk[top--] + '0');
    putchar('\n');
}

template <typename T = int> void writesp(T x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    static int stk[100];
    int top = 0;
    if (x == 0)
        stk[++top] = 0;
    while (x) {
        stk[++top] = x % 10;
        x /= 10;
    }
    while (top)
        putchar(stk[top--] + '0');
    putchar(' ');
}

template <typename T = int> void write(T x, char blank[]) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    static int stk[100];
    int top = 0;
    if (x == 0)
        stk[++top] = 0;
    while (x) {
        stk[++top] = x % 10;
        x /= 10;
    }
    while (top)
        putchar(stk[top--] + '0');
    putchar('\n');
    for (int i = 0; blank[i] != '\0'; ++i)
        putchar(blank[i]);
}

} // namespace IO

constexpr int maxn = 400 + 10;
constexpr int oo = 0x3f3f3f3f;

struct e {
    int to, next, capacity, weight, bak;
};

e edge[maxn * maxn];
int uuid = 1, head[maxn], dis[maxn], vis[maxn], cur[maxn];
int n, source, sink;

void link(int x, int y, int c, int w) {
    edge[++uuid] = {y, head[x], c, w, c};
    head[x] = uuid;
    edge[++uuid] = {x, head[y], 0, -w, 0};
    head[y] = uuid;
}

bool cmp(int x, int y, int type) {
    if (type == 1)
        return x <= y;
    else
        return x >= y;
}

bool SPFA(int type) {
    for (int i = 1; i <= sink; ++i)
        dis[i] = (type == 1 ? oo : -oo), vis[i] = 0;
    queue<int> q;
    q.push(source);
    dis[source] = 0;
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        cur[x] = head[x];
        vis[x] = false;
        for (int i = head[x], y; y = edge[i].to, i; i = edge[i].next) {
            if (edge[i].capacity <= 0 || cmp(dis[y], dis[x] + edge[i].weight, type))
                continue;
            dis[y] = dis[x] + edge[i].weight;
            if (vis[y])
                continue;
            vis[y] = true;
            q.push(y);
        }
    }
    return dis[sink] != (type == 1 ? oo : -oo);
}

int DFS(int x, int a, int &c) {
    if (x == sink)
        return a;
    vis[x] = true;
    int res = 0;
    for (int &i = cur[x], y; y = edge[i].to, i; i = edge[i].next) {
        if (vis[y] || edge[i].capacity <= 0 || dis[y] != dis[x] + edge[i].weight)
            continue;
        int f = DFS(y, min(edge[i].capacity, a - res), c);
        if (f > 0) {
            edge[i].capacity -= f;
            edge[i ^ 1].capacity += f;
            c += f * edge[i].weight;
            res += f;
            if (res == a)
                break;
        }
    }
    if (res == a)
        vis[x] = false;
    return res;
}

int Dinic(int type) {
    int flow = 0, cost = 0;
    while (SPFA(type))
        flow += DFS(source, oo, cost);
    return cost;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#endif
    using namespace IO;
    n = read();
    source = 4 * n + 1, sink = 4 * n + 2;
    for (int i = 1; i <= n; ++i) {
        link(source, i, 1, 0);
        link(i, i + n, 1, 0);
        link(i + 2 * n, i + 3 * n, 1, 0);
        link(i + 3 * n, sink, 1, 0);
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            int v = read();
            link(i + n, j + 2 * n, 1, v);
        }
    }
    writeln(Dinic(1));
    for (int i = 1; i <= uuid; ++i)
        edge[i].capacity = edge[i].bak;
    writeln(Dinic(2));
    return 0;
}