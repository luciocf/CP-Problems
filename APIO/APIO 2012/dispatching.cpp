// APIO 2012 - Dispatching
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5+10;

typedef long long ll;

struct node {
    int w, sz;
    ll soma, v;
    node *l, *r;

    node() {
        w = rand();
        v = soma = 0LL;
        l = r = NULL;
    }
};

typedef node*& node_t;

node *t[MAXN];

ll l[MAXN], num[MAXN], m, ans;

vector<int> grafo[MAXN];

int size(node *t)
{
    return t ? t->sz : 0;
}

void upd_size(node *t)
{
    if (t) t->sz = 1+size(t->l)+size(t->r);
}

ll get(node *t)
{
    return (t ? t->soma : 0LL);
}

void op(node *t)
{
    upd_size(t);
    t->soma = t->v+get(t->l)+get(t->r);
}

void split(node *t, node_t l, node_t r, int v)
{
    if (!t) return void(l=r=NULL);

    if (t->v > v) split(t->l, l, t->l, v), r = t;
    else split(t->r, t->r, r, v), l = t;

    op(t);
}

void merge(node_t t, node *l, node *r)
{
    if (!l) t = r;
    else if (!r) t = l;
    else if (l->w >= r->w) merge(l->r, l->r, r), t = l;
    else merge(r->l, l, r->l), t = r;

    op(t);
}

void insert(node_t t, int v)
{
    node *l = NULL, *r = NULL;
    node *aux = new node;
    aux->v = v, aux->soma = v;

    split(t, l, r, v);
    merge(l, l, aux);
    merge(t, l, r);

    op(t);
}

void push(node_t t1, node_t t2)
{
    if (!t2) return;
    insert(t1, t2->v);
    push(t1, t2->l); push(t1, t2->r);
    delete t2;
    t2 = NULL;
}

int query(node *t, ll x)
{
    if (!t) return 0;

    if (get(t->l) <= x)
    {
        if (get(t->l)+t->v <= x) return 1+size(t->l)+query(t->r, x-get(t->l)-t->v);
        else return size(t->l);
    }
    return query(t->l, x);
}

void DFS(int u, int p)
{
    insert(t[u], num[u]);
    for (auto v: grafo[u])
    {
        if (v == p) continue;

        DFS(v, u);

        if (size(t[v]) > size(t[u])) push(t[v], t[u]);
        else push(t[u], t[v]);

        if (!t[u]) swap(t[u], t[v]), delete(t[v]), t[v] = NULL;
    }
    ans = max(ans, l[u]*query(t[u], m));
}

int main(void)
{
    ios::sync_with_stdio(false); cin.tie(0);

    int n;
    cin >> n >> m;

    int root;
    for (int i = 1; i <= n; i++)
    {
        int p;
        cin >> p >> num[i] >> l[i];

        grafo[i].push_back(p); grafo[p].push_back(i);
        if (!p) root = i;
    }

    for (int i = 1; i <= n; i++) t[i] = NULL;

    DFS(root, 0);

    cout << ans << "\n";
}
