// Seletiva IOI 2018 - Bolsa de Brinquedos
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;
typedef long long ll;

const int maxn = 1e6+10;
const int inf = 1e9+10;

int n, m, k;

int a[maxn];
int cost[maxn];

int tree[4*maxn];

ll ans[maxn];

pii interv[maxn];

vector<int> pos[maxn], fim[maxn];

map<int, int> mp[maxn];

void upd(int node, int l, int r, int pos, int v)
{
	if (l == r)
	{
		tree[node] = min(tree[node], v);
		return;
	}

	int mid = (l+r)>>1;

	if (pos <= mid) upd(2*node, l, mid, pos, v);
	else upd(2*node+1, mid+1, r, pos, v);

	tree[node] = min(tree[2*node], tree[2*node+1]);
}

int query(int node, int l, int r, int a, int b)
{
	if (l > b || r < a) return inf;
	if (l >= a && r <= b) return tree[node];

	int mid = (l+r)>>1;

	return min(query(2*node, l, mid, a, b), query(2*node+1, mid+1, r, a, b));
}

int main(void)
{
	scanf("%d %d %d", &n, &m, &k);

	for (int i = 1; i <= m; i++)
		scanf("%d", &cost[i]);

	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);

		pos[a[i]].push_back(i);
		mp[a[i]][i] = (int)pos[a[i]].size();
	}

	for (int i = 1; i < 4*maxn; i++)
		tree[i] = inf;

	int q;
	scanf("%d", &q);

	for (int i = 1; i <= q; i++)
	{
		scanf("%d %d", &interv[i].first, &interv[i].second);

		fim[interv[i].second].push_back(i);
		ans[i] = 1e18+10;
	}

	for (int i = 1; i <= n; i++)
	{
		if (mp[a[i]][i] >= k)
			upd(1, 1, n, pos[a[i]][ mp[a[i]][i]-k ], cost[a[i]]);

		for (auto ind: fim[i])
		{
			int mn = query(1, 1, n, interv[ind].first, interv[ind].second);

			if (mn == inf) ans[ind] = -1;
			else ans[ind] = 1ll*k*mn;
		}
	}

	for (int i = 1; i <= q; i++)
		printf("%lld\n", ans[i]);
}
