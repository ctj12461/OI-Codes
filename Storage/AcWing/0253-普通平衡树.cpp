#include <bits/stdc++.h>
using namespace std;

template <typename T, int MaxN> class Treap {
  public:
    Treap() { Seed = (int)(MaxN * 565463ll % 2147483647); }

    void insert(T key) {
        int x, y;
        split(Root, key - 1, x, y);
        Root = merge(merge(x, create(key)), y);
    }

    void remove(T key) {
        int x, y, z;
        split(Root, key, x, z);
        split(x, key - 1, x, y);
        Stack[++Top] = y;
        y = merge(Tree[y].Left, Tree[y].Right);
        Root = merge(merge(x, y), z);
    }

    int rank(T key) {
        int x, y, ans;
        split(Root, key - 1, x, y);
        ans = Tree[x].Size + 1;
        Root = merge(x, y);
        return ans;
    }

    T at(int r) {
        int root = Root;
        while (true) {
            if (Tree[Tree[root].Left].Size + 1 == r) {
                break;
            } else if (Tree[Tree[root].Left].Size + 1 > r) {
                root = Tree[root].Left;
            } else {
                r -= Tree[Tree[root].Left].Size + 1;
                root = Tree[root].Right;
            }
        }
        return Tree[root].Key;
    }

    T lower(int key) {
        int x, y, root;
        T ans;
        split(Root, key - 1, x, y);
        root = x;
        while (Tree[root].Right)
            root = Tree[root].Right;
        ans = Tree[root].Key;
        Root = merge(x, y);
        return ans;
    }

    T upper(int key) {
        int x, y, root;
        T ans;
        split(Root, key, x, y);
        root = y;
        while (Tree[root].Left)
            root = Tree[root].Left;
        ans = Tree[root].Key;
        Root = merge(x, y);
        return ans;
    }

  private:
    struct Node {
        T Key;
        int Left, Right, Size, Priority;
    } Tree[MaxN];
    int Seed, Total, Root, Top, Stack[MaxN >> 4];

    int rad() { return Seed = int(Seed * 482711ll % 2147483647); }

    int create(int key) {
        int root = Top ? Stack[Top--] : ++Total;
        Tree[root].Key = key;
        Tree[root].Size = 1;
        Tree[root].Left = Tree[root].Right = 0;
        Tree[root].Priority = rad();
        return root;
    }

    void pushup(int root) {
        Tree[root].Size =
            Tree[Tree[root].Left].Size + Tree[Tree[root].Right].Size + 1;
    }

    void split(int root, int key, int &x, int &y) {
        if (root == 0) {
            x = y = 0;
            return;
        }
        if (Tree[root].Key <= key) {
            x = root;
            split(Tree[root].Right, key, Tree[root].Right, y);
        } else {
            y = root;
            split(Tree[root].Left, key, x, Tree[root].Left);
        }
        pushup(root);
    }

    int merge(int x, int y) {
        if (x == 0 || y == 0)
            return x + y;
        if (Tree[x].Priority > Tree[y].Priority) {
            Tree[x].Right = merge(Tree[x].Right, y);
            pushup(x);
            return x;
        } else {
            Tree[y].Left = merge(x, Tree[y].Left);
            pushup(y);
            return y;
        }
    }
};

Treap<int, 100005> tree;
int n, x, opt;

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d%d", &opt, &x);
        if (opt == 1)
            tree.insert(x);
        if (opt == 2)
            tree.remove(x);
        if (opt == 3)
            printf("%d\n", tree.rank(x));
        if (opt == 4)
            printf("%d\n", tree.at(x));
        if (opt == 5)
            printf("%d\n", tree.lower(x));
        if (opt == 6)
            printf("%d\n", tree.upper(x));
    }
    return 0;
}