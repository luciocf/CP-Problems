// USP Try-Outs 2017 - Coprimes
// Lúcio Cardoso

// Solution uses parallel binary search with the inclusion-exclusion principle to find, for each i,
// the largest j < i such that a[i] and a[j] are coprime. Then, checking the answer requires only a max query
// in a range.

#include <bits/stdc++.h>

using namespace std;

const int maxn = 5e5+10;

struct SegmentTree
{
	int tree[4*maxn];

	void upd(int node, int l, int r, int pos, int v)
	{
		if (l == r)
		{
			tree[node] = v;
			return;
		}	

		int mid = (l+r)>>1;

		if (pos <= mid) upd(2*node, l, mid, pos, v);
		else upd(2*node+1, mid+1, r, pos, v);

		tree[node] = max(tree[2*node], tree[2*node+1]);
	}

	int query(int node, int l, int r, int a, int b)
	{
		if (l > b || r < a) return 0;
		if (l >= a && r <= b) return tree[node];

		int mid = (l+r)>>1;

		return max(query(2*node, l, mid, a, b), query(2*node+1, mid+1, r, a, b));
	}
} seg;

int n;
int a[maxn];

int spf[maxn];

int bsL[maxn], bsR[maxn], bsMid[maxn], bsLast[maxn];
int qtd[maxn], ans[maxn];
vector<int> atmid[maxn];

int freq[maxn];

void sieve(void)
{
	for (int i = 1; i < maxn; i++)
		spf[i] = i;

	for (int i = 2; i < maxn; i++)
		if (spf[i] == i)
			for (int j = 2*i; j < maxn; j += i)
				if (spf[j] == j)
					spf[j] = i;
}

vector<int> get_p(int x)
{
	vector<int> p;
	while (x > 1)
	{
		if (!p.size() || p.back() != spf[x])
			p.push_back(spf[x]);

		x /= spf[x];
	}

	return p;
}

void upd(int x)
{
	vector<int> p = get_p(x);

	int sz = p.size();

	for (int mask = 1; mask < (1<<sz); mask++)
	{
		int prod = 1;

		for (int i = 0; i < sz; i++)
			if (mask&(1<<i))
				prod *= p[i];

		freq[prod]++;
	}
}

int get(int x)
{
	vector<int> p = get_p(x);

	int sz = p.size();
	int ans = 0;

	for (int mask = 1; mask < (1<<sz); mask++)
	{
		int prod = 1;

		for (int i = 0; i < sz; i++)
			if (mask&(1<<i))
				prod *= p[i];

		if (__builtin_popcount(mask)%2) ans += freq[prod];
		else ans -= freq[prod];
	}

	return ans;
}

void init(void)
{
	for (int i = 1; i < maxn; i++)
	{
		freq[i] = qtd[i] = 0;
		atmid[i].clear();
	}
}

void bs(void)
{
	bool flag = 1;

	for (int i = 1; i <= n; i++)
	{
		bsL[i] = 1, bsR[i] = i-1;
		bsLast[i] = 1;
	}

	while (flag)
	{
		flag = 0;
		init();

		for (int i = 2; i <= n; i++)
		{
			if (bsL[i] > bsR[i]) bsLast[i] = 0;

			if (bsL[i] < bsR[i] || bsLast[i])
			{
				flag = 1;

				bsMid[i] = (bsL[i] + bsR[i])>>1;
				atmid[bsMid[i]].push_back(i);
			}
		}


		for (int i = 1; i <= n; i++)
		{
			for (auto j: atmid[i])
				qtd[j] = -get(a[j]);

			upd(a[i]);
			if (i == 1) continue;

			if (bsL[i] < bsR[i] || bsLast[i])
			{
				if (bsL[i] == bsR[i]) bsLast[i] = 0;

				qtd[i] += get(a[i]);

				if (qtd[i] >= i - bsMid[i] + 1) bsR[i] = bsMid[i]-1;
				else ans[i] = bsMid[i], bsL[i] = bsMid[i]+1;
			}
		}
	}
}

int main(void)
{
	sieve();

	int m;
	scanf("%d %d", &n, &m);

	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);

	bs();

	for (int i = 1; i <= n; i++)
		seg.upd(1, 1, n, i, ans[i]);

	for (int i = 1; i <= m; i++)
	{
		int l, r;
		scanf("%d %d", &l, &r);

		if (seg.query(1, 1, n, l, r) >= l) printf("S\n");
		else printf("N\n");
	}
}
