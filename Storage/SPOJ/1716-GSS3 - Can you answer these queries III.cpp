#include <bits/stdc++.h>
using namespace std;

const int maxn = 101000;

struct node {
    int l, r, sum, ans, lans, rans;
};

node tree[maxn * 4];
int a[maxn];
int n, m;

void pushup(node &nt, node lt, node rt) {
    nt.sum = nt.ans = nt.lans = nt.ans = 0;
    nt.sum = lt.sum + rt.sum;
    nt.lans = max(lt.lans, lt.sum + rt.lans);
    nt.rans = max(rt.rans, rt.sum + lt.rans);
    nt.ans = max(max(lt.ans, rt.ans), lt.rans + rt.lans);
}

void build(int x, int l, int r) {
    tree[x].l = l;
    tree[x].r = r;
    if (l == r) {
        tree[x].sum = tree[x].lans = tree[x].rans = tree[x].ans = a[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(x << 1, l, mid);
    build(x << 1 | 1, mid + 1, r);
    pushup(tree[x], tree[x << 1], tree[x << 1 | 1]);
}

void modify(int x, int p, int v) {
    if (tree[x].l == tree[x].r && tree[x].l == p) {
        tree[x].sum = tree[x].lans = tree[x].rans = tree[x].ans = v;
        return;
    }
    int mid = tree[x].l + tree[x].r >> 1;
    if (p <= mid)
        modify(x << 1, p, v);
    else
        modify(x << 1 | 1, p, v);
    pushup(tree[x], tree[x << 1], tree[x << 1 | 1]);
}

node query(int x, int l, int r) {
    if (l <= tree[x].l && tree[x].r <= r) {
        return tree[x];
    }
    int mid = (tree[x].l + tree[x].r) >> 1;
    if (l <= mid && mid < r) {

        node lt = query(x << 1, l, r);
        node rt = query(x << 1 | 1, l, r);
        node nt;
        pushup(nt, lt, rt);
        return nt;
    } else if (l <= mid) {
        return query(x << 1, l, r);
    } else {
        return query(x << 1 | 1, l, r);
    }
}

template <typename T> T read() {
    int x = 0, f = 1;
    char c = getchar();
    while (!isdigit(c)) {
        if (c == '-')
            f *= -1;
        c = getchar();
    }
    while (isdigit(c)) {
        x = (x << 1) + (x << 3) + c - '0';
        c = getchar();
    }
    return x * f;
}

int main() {
    n = read<int>();
    for (int i = 1; i <= n; ++i) {
        a[i] = read<int>();
    }
    build(1, 1, n);
    m = read<int>();
    for (int i = 1; i <= m; ++i) {
        int o = read<int>(), x = read<int>(), y = read<int>();
        if (o == 0)
            modify(1, x, y);
        else
            printf("%d\n", query(1, x, y).ans);
    }
    return 0;
}