// Codeforces 369E - Valera and Queries
// Lúcio Cardoso

// Use merge sort tree where values in position r are the indices l such that interval (l, r) exists
// Then, query becomes finding amount of points in a range with value <= v (where v is one of the points given)

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e6+10;

int n, m;

vector<int> pos[maxn], tree[4*maxn];

void build(int node, int l, int r)
{
	if (l == r)
	{
		for (auto p: pos[l])
			tree[node].push_back(p);
		return;
	}

	int mid = (l+r)>>1;

	build(2*node, l, mid); build(2*node+1, mid+1, r);

	merge(tree[2*node].begin(), tree[2*node].end(), tree[2*node+1].begin(), tree[2*node+1].end(), back_inserter(tree[node]));
}

int query(int node, int l, int r, int a, int b, int v)
{
	if (l > b || r < a) return 0;

	if (l >= a && r <= b)
	{
		auto it = upper_bound(tree[node].begin(), tree[node].end(), v);
		return (int)(it-tree[node].begin());
	}

	int mid = (l+r)>>1;

	return query(2*node, l, mid, a, b, v)+query(2*node+1, mid+1, r, a, b, v);
}

int main(void)
{
	scanf("%d %d", &n, &m);

	for (int i = 1; i <= n; i++)
	{
		int l, r;
		scanf("%d %d", &l, &r);

		pos[r].push_back(l);
	}

	for (int i = 1; i < maxn; i++)
		sort(pos[i].begin(), pos[i].end());

	build(1, 1, maxn-1);

	for (int i = 1; i <= m; i++)
	{
		int c;
		scanf("%d", &c);

		vector<int> V;

		for (int j = 1; j <= c; j++)
		{
			int x;
			scanf("%d", &x);

			V.push_back(x);
		}

		int ans = 0;

		for (int j = 0; j < (int)V.size()-1; j++)
		{
			int l = V[j], r = V[j+1]-1;
			if (l > r) continue;

			ans += query(1, 1, maxn-1, l, r, l);
		}

		ans += query(1, 1, maxn-1, V.back(), maxn-1, V.back());
		printf("%d\n", ans);
	}
}
