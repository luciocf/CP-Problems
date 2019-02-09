// JOI Open Contest 2014 - Fortune Telling 2
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 2e5+5;

typedef long long ll;

int num[2][maxn], query[maxn];

vector<int> tree[4*maxn];

void build(int node, int l, int r)
{
	if (l == r)
	{
		tree[node].push_back(query[l]);
		return;
	}

	int mid = (l+r)>>1;

	build(2*node, l, mid); build(2*node+1, mid+1, r);

	int a = 2*node, b = 2*node+1;
	merge(tree[a].begin(), tree[a].end(), tree[b].begin(), tree[b].end(), back_inserter(tree[node]));
}

int query_pos(int node, int l, int r, int a, int b)
{
	if (l == r) 
		return ((tree[node][0] >= a && tree[node][0] < b) ? l : -1);

	int mid = (l+r)>>1;

	if (tree[2*node+1].back() < a)
		return query_pos(2*node, l, mid, a, b);

	if (*(lower_bound(tree[2*node+1].begin(), tree[2*node+1].end(), a)) < b)
		return query_pos(2*node+1, mid+1, r, a, b);

	return query_pos(2*node, l, mid, a, b);
}

int query_qtd(int node, int l, int r, int a, int b, int vv)
{
	if (a > b) return 0;
	if (l > b || r < a) return 0;

	if (l >= a && r <= b) 
		return (tree[node].end()-lower_bound(tree[node].begin(), tree[node].end(), vv));

	int mid = (l+r)>>1;

	return (query_qtd(2*node, l, mid, a, b, vv)+query_qtd(2*node+1, mid+1, r, a, b, vv));
}

int main(void)
{
	ios::sync_with_stdio(false); cin.tie(0);

	int n, k;
	cin >> n >> k;

	for (int i = 1; i <= n; i++)
		cin >> num[0][i] >> num[1][i];

	for (int i = 1; i <= k; i++)
		cin >> query[i];

	build(1, 1, k);

	ll ans = 0LL;
	for (int i = 1; i <= n; i++)
	{
		int A = max(num[0][i], num[1][i]), B = min(num[0][i], num[1][i]);
		int last = query_pos(1, 1, k, B, A);

		if (last == -1)
		{
			int qtd = query_qtd(1, 1, k, 1, k, num[0][i]);

			if (qtd%2 == 0) ans += (ll)num[0][i];
			else ans += (ll)num[1][i];
		}
		else
		{
			int qtd = query_qtd(1, 1, k, last+1, k, A);

			if (qtd%2 == 0) ans += (ll)A;
			else ans += (ll)B;
		}
	}

	cout << ans << "\n";
}
