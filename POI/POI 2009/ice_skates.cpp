// POI 2009 - Ice Skates
// Lúcio Cardoso

// Solution: https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/Olympiad/POI/POI-09-Ice_Skates.txt

#include <bits/stdc++.h>

using namespace std;

const int maxn = 2e5+10;

typedef long long ll;

struct Node
{
	ll tot;
	ll pref, suf;
	ll mx;
} tree[4*maxn];

int n, m, k, d;

void comb(int node)
{
	tree[node].tot = tree[2*node].tot+tree[2*node+1].tot;

	tree[node].pref = max(tree[2*node].pref, tree[2*node].tot+tree[2*node+1].pref);

	tree[node].suf = max(tree[2*node+1].suf, tree[2*node+1].tot+tree[2*node].suf);

	tree[node].mx = max({tree[2*node].mx, tree[2*node].suf+tree[2*node+1].pref, tree[2*node+1].mx});
}

void build(int node, int l, int r)
{
	if (l == r)
	{
		tree[node] = {-k, -k, -k, -k};
		return;
	}

	int mid = (l+r)>>1;

	build(2*node, l, mid); build(2*node+1, mid+1, r);

	comb(node);
}

void upd(int node, int l, int r, int pos, int v)
{
	if (l == r)
	{
		tree[node].tot += 1ll*v;
		tree[node].pref += 1ll*v, tree[node].suf += 1ll*v;
		tree[node].mx += 1ll*v;
		return;
	}

	int mid = (l+r)>>1;

	if (pos <= mid) upd(2*node, l, mid, pos, v);
	else upd(2*node+1, mid+1, r, pos, v);

	comb(node);
}

int main(void)
{
	scanf("%d %d %d %d", &n, &m, &k, &d);

	build(1, 1, n);

	for (int i = 1; i <= m; i++)
	{
		int pos, v;
		scanf("%d %d", &pos, &v);

		upd(1, 1, n, pos, v);

		if (tree[1].mx <= 1ll*k*d) printf("TAK\n");
		else printf("NIE\n");
	}
}
