// JOI Spring Camp 2017 - Port Facility
// Lúcio Cardoso

// Solution: https://codeforces.com/blog/entry/51010

#include <bits/stdc++.h>

using namespace std;

const int maxn = 2e6+10;
const int inf = 1e9+10;
const int mod = 1e9+7;

int n;
int l[maxn], r[maxn];

int cor[maxn], comp[maxn];

int back[maxn];

int tree[2][4*maxn];

vector<int> one, zero;

void build(int node, int l, int r)
{
	if (l == r)
	{
		tree[0][node] = inf;
		tree[1][node] = -inf;
		return;
	}

	int mid = (l+r)>>1;

	build(2*node, l, mid); build(2*node+1, mid+1, r);

	tree[0][node] = min(tree[0][2*node], tree[0][2*node+1]);
	tree[1][node] = max(tree[1][2*node], tree[1][2*node+1]);
}

void upd(int node, int l, int r, int pos, int v, int k)
{
	if (l == r)
	{
		tree[k][node] = v;
		return;
	}

	int mid = (l+r)>>1;

	if (pos <= mid) upd(2*node, l, mid, pos, v, k);
	else upd(2*node+1, mid+1, r, pos, v, k);

	tree[0][node] = min(tree[0][2*node], tree[0][2*node+1]);
	tree[1][node] = max(tree[1][2*node], tree[1][2*node+1]);
}

int query(int node, int l, int r, int a, int b, int k)
{
	if (l > b || r < a) return (k == 0 ? inf : -inf);
	if (l >= a && r <= b) return tree[k][node];

	int mid = (l+r)>>1;

	int p1 = query(2*node, l, mid, a, b, k), p2 = query(2*node+1, mid+1, r, a, b, k);

	if (!k) return min(p1, p2);
	return max(p1, p2);
}

void dfs(int u, int C, int cc)
{
	comp[u] = cc, cor[u] = C;

	while (true)
	{
		int x = query(1, 1, 2*n, l[u]+1, r[u]-1, 0);
		if (x >= l[u]) break;

		upd(1, 1, 2*n, r[back[x]], inf, 0);
		upd(1, 1, 2*n, l[back[x]], -inf, 1);

		dfs(back[x], (!C ? 1 : 0), cc);
	}

	while (true)
	{
		int x = query(1, 1, 2*n, l[u]+1, r[u]-1, 1);
		if (x <= r[u]) break;

		upd(1, 1, 2*n, r[back[x]], inf, 0);
		upd(1, 1, 2*n, l[back[x]], -inf, 1);

		dfs(back[x], (!C ? 1 : 0), cc);
	}
}

bool cmp(int a, int b)
{
	return l[a] < l[b];
}

bool ok(bool k)
{
	stack<int> stk;

	if (!k)
	{
		for (auto i: zero)
		{
			while (stk.size() && l[i] > stk.top())
				stk.pop();

			if (stk.size() && stk.top() > l[i] && stk.top() < r[i])
				return 0;

			stk.push(r[i]);
		}
	}
	else
	{
		for (auto i: one)
		{
			while (stk.size() && l[i] > stk.top())
				stk.pop();

			if (stk.size() && stk.top() > l[i] && stk.top() < r[i])
				return 0;

			stk.push(r[i]);
		}
	}

	return 1;
}

int main(void)
{
	scanf("%d", &n);

	build(1, 1, 2*n);

	for (int i = 1; i <= n; i++)
	{
		scanf("%d %d", &l[i], &r[i]);

		back[l[i]] = back[r[i]] = i;
		upd(1, 1, 2*n, r[i], l[i], 0);
		upd(1, 1, 2*n, l[i], r[i], 1);
	}

	int cc = 0;
	for (int i = 1; i <= n; i++)
	{
		if (!comp[i])
		{
			upd(1, 1, 2*n, r[i], inf, 0);
			upd(1, 1, 2*n, l[i], -inf, 1);
			dfs(i, 0, ++cc);
		}
	}

	for (int i = 1; i <= n; i++)
	{
		if (cor[i] == 0) zero.push_back(i);
		else one.push_back(i);
	}

	sort(zero.begin(), zero.end(), cmp);
	sort(one.begin(), one.end(), cmp);

	if (!ok(0) || !ok(1))
	{
		printf("0\n");
		return 0;
	}

	int ans = 1;
	for (int i = 1; i <= cc; i++)
		ans = (ans*2)%mod;

	printf("%d\n", ans);
}
