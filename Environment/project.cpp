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

struct node {
    int fail;
    map<int, int> to;
    vector<int> id;
};

constexpr int maxn = 5e4 + 10;
constexpr int maxm = 1e5 + 10;
constexpr int maxl = 1e5 + 10;

node trie[maxl * 4];
int root = 1, uuid = 1, n, m;
unordered_set<int> vis[maxn];

void insert(int pattern[], int len, int id) {
    int x = root;
    for (int i = 1; i <= len; ++i) {
        int c = pattern[i];
        if (!trie[x].to[c])
            ++trie[x].to[c];
        x = trie[x].to[c];
    }
    trie[x].id.push_back(id);
}

void preprocess(int v) {
    queue<int> q;
    q.push(root);
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        for (auto i : trie[x].to) {
            int c = i.first, y = i.second, j = 0;
            if (x == root) {
                trie[y].fail = root;
                q.push(y);
                continue;
            }
            for (j = trie[x].fail; j; j = trie[j].fail) {
                if (trie[j].to[c]) {
                    trie[y].fail = trie[j].to[c];
                    break;
                }
            }
            if (j == 0)
                trie[y].fail = root;
            q.push(y);
        }
    }
}

void match(int str[], int len, int id) {
    int x = root;
    for (int i = 1; i <= len; ++i) {
        int c = str[i];
        
    }
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("Environment/project.in", "r", stdin);
    freopen("Environment/project.out", "w", stdout);
#endif
    using namespace IO;
    return 0;
}