// Seletiva IOI 2014 - Intervalo
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct node
{
	int v, w, sz;
	ll soma;
	node *l, *r;

	node(int vv)
	{
		v = vv, w = rand(), sz = 1;
		soma = vv;
		l = r = NULL;
	}
};

typedef node*& node_t;

int sz(node *t) {return (t ? t->sz : 0);}
ll soma(node *t) {return (t ? t->soma : 0);}

void op(node *t)
{
	if (t)
	{
		t->sz = sz(t->l)+sz(t->r)+1;
		t->soma = soma(t->l)+soma(t->r)+1ll*t->v;
	}
}

void split(node *t, node_t l, node_t r, int pos, int add=0)
{
	if (!t) return void(l=r=NULL);

	int v = add+sz(t->l);

	if (v >= pos) split(t->l, l, t->l, pos, add), r = t;
	else split(t->r, t->r, r, pos, v+1), l = t;

	op(t);
}

void merge(node_t t, node *l, node *r)
{
	if (!l || ! r) t = (l ? l : r);
	else if (l->w > r->w) merge(l->r, l->r, r), t = l;
	else merge(r->l, l, r->l), t = r;

	op(t);
}

void insert(node_t t, int pos, int v)
{
	node *t1 = NULL, *t2 = NULL;
	node *aux = new node(v);

	split(t, t1, t2, pos);
	merge(t1, t1, aux);
	merge(t, t1, t2);

	op(t);
}

ll query(node *t, int l, int r)
{
	node *t1 = NULL, *t2 = NULL, *t3 = NULL;

	split(t, t1, t2, r+1);
	split(t1, t1, t3, l);

	ll ans = t3->soma;

	merge(t1, t1, t3);
	merge(t, t1, t2);

	return ans;
}

int main(void)
{
	int n;
	scanf("%d", &n);

	node *t = NULL;

	for (int i = 1; i <= n; i++)
	{
		int x;
		scanf("%d", &x);

		insert(t, i-1, x);
	}

	int q;
	scanf("%d", &q);

	for (int i = 1; i <= q; i++)
	{
		char op;
		scanf(" %c", &op);

		if (op == 'I')
		{
			int pos, v;
			scanf("%d %d", &pos, &v);

			insert(t, pos, v);
		}
		else
		{
			int l, r;
			scanf("%d %d", &l, &r);

			printf("%lld\n", query(t, l-1, r-1));
		}
	}
}
