// ICPC Pacific Northwest 2020 Regional D1 - B - Perfect Flush
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 2e5+10;
const int inf = 1e9+10;

int a[maxn];

int tree[4*maxn];

vector<int> pos[maxn];

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
	int n, k;
	scanf("%d %d", &n, &k);

	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);

		upd(1, 1, n, i, a[i]);

		pos[a[i]].push_back(i);
	}

	set<int> st;
	vector<int> ans;

	for (int i = 1; i <= k; i++)
		if (pos[i].size())
			st.insert(pos[i].back());

	int ptr = 1;
	for (int i = 1; i <= k; i++)
	{
		int x = query(1, 1, n, ptr, *st.begin());

		ans.push_back(x);

		st.erase(pos[x].back());
		for (auto p: pos[x])
			upd(1, 1, n, p, inf);

		int ind = *lower_bound(pos[x].begin(), pos[x].end(), ptr);
		ptr = ind+1;
	}

	for (auto x: ans)
		printf("%d ", x);
	printf("\n");
}
