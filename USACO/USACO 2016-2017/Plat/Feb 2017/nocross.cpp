// USACO 2016/2017 - Why did the cow cross the road II
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5+10;

int n;
int pos[maxn], a[maxn];

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

int main(void)
{
	freopen("nocross.in", "r", stdin);
	freopen("nocross.out", "w", stdout);

	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
	{
		int x;
		scanf("%d", &x);

		pos[x] = i;
	}

	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);

	int ans = 0;

	for (int i = 1; i <= n; i++)
	{
		vector<int> V;

		for (int k = 4; k >= -4; k--)
			if (a[i]+k <= n && a[i]+k > 0)
				V.push_back(pos[a[i]+k]);
		
		sort(V.begin(), V.end());

		for (int j = V.size()-1; j >= 0; j--)
		{
			int y = V[j];
			int x = 1+query(1, 1, n, 1, y-1);
			
			ans = max(ans, x);
			upd(1, 1, n, y, x);
		}
	}

	printf("%d\n", ans);
}
