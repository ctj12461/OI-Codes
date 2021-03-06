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

constexpr int maxn = 200 + 10;

struct e {
    int to, next, capacity;
};

e edge[maxn * maxn * 20];
int head[maxn * maxn], uuid = 1, cur[maxn * maxn], dis[maxn * maxn];
int n, m, source, sink, nextid, sum;
int dir[4][2] = {{1, 0}, {0, 1}, {0, -1}, {-1, 0}};

void link(int x, int y, int c) {
    edge[++uuid] = {y, head[x], c};
    head[x] = uuid;
    edge[++uuid] = {x, head[y], 0};
    head[y] = uuid;
}

bool BFS() {
    memset(dis, 0, sizeof(dis));
    queue<int> q;
    q.push(source);
    dis[source] = 1;
    cur[source] = head[source];
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        for (int i = head[x], y; y = edge[i].to, i; i = edge[i].next) {
            if (edge[i].capacity <= 0 || dis[y])
                continue;
            q.push(y);
            dis[y] = dis[x] + 1;
            cur[y] = head[y];
        }
    }
    return dis[sink];
}

int DFS(int x, int a) {
    if (x == sink)
        return a;
    int res = 0;
    for (int &i = cur[x], y; y = edge[i].to, i; i = edge[i].next) {
        if (edge[i].capacity <= 0 || dis[y] != dis[x] + 1)
            continue;
        int f = DFS(y, min(edge[i].capacity, a - res));
        if (f > 0) {
            edge[i].capacity -= f;
            edge[i ^ 1].capacity += f;
            res += f;
            if (res == a)
                break;
        }
    }
    if (res != a) 
        dis[x] = 0;
    return res;
}

int Dinic() {
    int res = 0;
    while (BFS()) 
        res += DFS(source, 0x3f3f3f3f);
    return res;
}

bool vaild(int x, int y) {
    return 1 <= x && x <= n && 1 <= y && y <= m;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#endif
    using namespace IO;
    n = read();
    m = read();
    source = n * m + 1;
    sink = n * m + 2;
    nextid = sink;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            int val = read();
            link(source, (i - 1) * m + j, val);
            sum += val;
        }
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            int val = read();
            link((i - 1) * m + j, sink, val);
            sum += val;
        }
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            int val = read();
            ++nextid;
            link(source, nextid, val);
            link(nextid, (i - 1) * m + j, 0x3f3f3f3f);
            for (int k = 0; k < 4; ++k) {
                int ni = i + dir[k][0], nj = j + dir[k][1];
                if (!vaild(ni, nj))
                    continue;
                link(nextid, (ni - 1) * m + nj, 0x3f3f3f3f);
            }
            sum += val;
        }
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            int val = read();
            ++nextid;
            link(nextid, sink, val);
            link((i - 1) * m + j, nextid, 0x3f3f3f3f);
            for (int k = 0; k < 4; ++k) {
                int ni = i + dir[k][0], nj = j + dir[k][1];
                if (!vaild(ni, nj))
                    continue;
                link((ni - 1) * m + nj, nextid, 0x3f3f3f3f);
            }
            sum += val;
        }
    }
    writeln(sum - Dinic());
    return 0;
}