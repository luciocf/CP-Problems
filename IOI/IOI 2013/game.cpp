// IOI 2013 - Game
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int n, m;

struct Node {
    int w, ind;
    ll v, g;
    Node *l, *r;

    Node() {
        l = r = NULL;
        v = 0LL, g = 0LL, ind = -1;
        w = rand();
    }
};

typedef Node*& node_t;

struct Node2d {
    Node *f;
    Node2d *l, *r;

    Node2d() {
        f = NULL;
        l = r = NULL;
    }
};

Node2d *root = new Node2d;

ll gcd(ll X, ll Y) 
{
    long long tmp;
    while (X != Y && Y != 0) 
    {
        tmp = X;
        X = Y;
        Y = tmp % Y;
    }
    return X;
}

ll get(Node *t)
{
    if (!t) return 0LL;
    return t->g;
}

void operation(Node *t)
{
    if (!t) return;
    t->g = gcd( gcd(t->v, get(t->l)), get(t->r));
}

ll find(node_t t, int v, ll k)
{
    if (!t) return -1LL;

    if (t->ind == v)
    {
        if (k != -1) t->v = k, operation(t);
        return t->v;
    }
    else if (t->ind > v)
    {
        ll x = find(t->l, v, k);
        if (x != -1 && k != -1) operation(t);
        return x;
    }
    else
    {
        ll x = find(t->r, v, k);
        if (x != -1 && k != -1) operation(t);
        return x;
    }
}

void split(Node *t, node_t l, node_t r, int pos)
{
    if (!t) return void(l=r=NULL);

    if (pos < t->ind)
        split(t->l, l, t->l, pos), r = t;
    else
        split(t->r, t->r, r, pos), l = t;
    operation(t);
}

void merge(node_t t, Node *l, Node *r)
{
    if (l == NULL)
        t = r;
    else if (r == NULL)
        t = l;
    else if (l->w >= r->w)
        merge(l->r, l->r, r), t = l;
    else
        merge(r->l, l, r->l), t = r;
    operation(t);
}

void upd_y(node_t t, Node *left, Node *right, int pos, ll v)
{
    Node *tl = NULL, *tm = NULL, *tr = NULL;

    ll vl = find(left, pos, -1), vr = find(right, pos, -1);

    if (vl != -1) v = gcd(vl, v);
    if (vr != -1) v = gcd(vr, v);

    ll x = find(t, pos, v);

    if (x == -1)
    {
        Node *aux = new Node;
        aux->v = v, aux->ind = pos, aux->g = v;

        split(t, tl, tr, pos-1);
        merge(tl, tl, aux);
        merge(t, tl, tr);
    }
}

void upd_x(Node2d *nx, int lx, int rx, int x, int y, ll v)
{
    if (lx != rx)
    {
        int mx = (lx+rx)/2;
        if (x <= mx)
        {
            if (nx->l == NULL) nx->l = new Node2d;
            upd_x(nx->l, lx, mx, x, y, v);
        }
        else
        {
            if (nx->r == NULL) nx->r = new Node2d;
            upd_x(nx->r, mx+1, rx, x, y, v);
        }
    }
    upd_y(nx->f, (nx->l==NULL)?NULL:nx->l->f, (nx->r==NULL)?NULL:nx->r->f, y, v);
}

ll query_y(node_t t, int l, int r)
{
    if (!t) return 0LL;

    Node *tl = NULL, *tm = NULL, *tr = NULL;

    split(t, tl, tm, l-1);
    split(tm, t, tr, r);

    ll ans = 0LL;
    if (t) ans = t->g;
    merge(tm, tl, t);
    merge(t, tm, tr);
    return ans;
}

ll query_x(Node2d *nx, int tlx, int trx, int lx, int rx, int ly, int ry)
{
    if (nx == NULL || lx > rx) return 0LL;
    if (tlx == lx && trx == rx) return query_y(nx->f, ly, ry);

    int mx = (tlx+trx)/2;

    ll p1 = query_x(nx->l, tlx, mx, lx, min(rx, mx), ly, ry);
    ll p2 = query_x(nx->r, mx+1, trx, max(lx, mx+1), rx, ly, ry);

    return gcd(p1, p2);
}

void init(int R, int C)
{
    n = R, m = C;
    return;
}

void update(int P, int Q, long long K)
{
    upd_x(root, 0, n-1, P, Q, K);
}

long long calculate(int P, int Q, int U, int V)
{
    return query_x(root, 0, n-1, P, U, Q, V);
}
