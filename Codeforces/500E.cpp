// Codeforces 500E - New Year Domino
// Lúcio Cardoso

#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

typedef pair<int, int> pii;

const int maxn = 2e5+10;

struct Query
{
	int l, r, ind;
} query[maxn];

int n;
int x[maxn], l[maxn];

int pai[maxn], peso[maxn], mx[maxn], st[maxn];

int ans[maxn];

int suf[maxn];

void init(void)
{
	for (int i = 1; i <= n; i++)
		pai[i] = i, peso[i] = 1, mx[i] = x[i]+l[i], st[i] = i;
}

int Find(int x)
{
	if (pai[x] == x) return x;
	return pai[x] = Find(pai[x]);
}

void Join(int a, int b)
{
	a = Find(a), b = Find(b);
	if (a == b) return;

	if (peso[a] < peso[b]) swap(a, b);

	pai[b] = a, peso[a] += peso[b];

	if (x[st[a]] > x[st[b]]) st[a] = st[b];

	mx[a] = max(mx[a], mx[b]);
}

bool comp(Query a, Query b) {return a.l < b.l;}

int main(void)
{
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
		scanf("%d %d", &x[i], &l[i]);

	init();

	int q;
	scanf("%d", &q);

	for (int i = 1; i <= q; i++)
	{
		scanf("%d %d", &query[i].l, &query[i].r);
		query[i].ind = i;
	}

	sort(query+1, query+q+1, comp);

	int aux = q;

	stack<pii> stk;

	for (int i = n; i >= 1; i--)
	{
		while (!stk.empty() && stk.top().ff <= mx[Find(i)])
		{
			Join(stk.top().ss, i);
			stk.pop();
		}

		if (stk.empty()) suf[i] = 0;
		else suf[i] = suf[stk.top().ss] + stk.top().ff - mx[Find(i)];

		stk.push({x[st[Find(i)]], st[Find(i)]});

		while (true)
		{
			if (aux == 0 || query[aux].l < i) break;

			ans[query[aux].ind] = suf[st[Find(i)]] - suf[st[Find(query[aux].r)]];
			aux--;
		}
	}

	for (int i = 1; i <= q; i++)
		printf("%d\n", ans[i]);
}
