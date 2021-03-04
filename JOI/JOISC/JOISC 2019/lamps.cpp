// JOISC 2019 - Lamps
// Lúcio Cardoso

#include <bits/stdc++.h>
 
using namespace std;
 
const int maxn = 1e6+10;
const int inf = 1e9+10;
 
char a[maxn], b[maxn];
 
int ate[maxn][2];
 
int pref[maxn][2];
 
int dp[maxn][2];
 
struct SegmentTree
{
	int tree[4*maxn];
 
	void build(int node, int l, int r)
	{
		tree[node] = inf;
		if (l == r) return;
 
		int mid = (l+r)>>1;
 
		build(2*node, l, mid); build(2*node+1, mid+1, r);
	}
 
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
		if (l > r || l > b || r < a) return inf;
		if (l >= a && r <= b) return tree[node];
 
		int mid = (l+r)>>1;
 
		return min(query(2*node, l, mid, a, b), query(2*node+1, mid+1, r, a, b));
	}
} seg[2];
 
int main(void)
{
	int n;
	scanf("%d", &n);
 
	for (int i = 1; i <= n; i++)
		scanf(" %c", &a[i]);
 
	for (int i = 1;  i <= n; i++)
		scanf(" %c", &b[i]);
 	
	for (int i = 1; i <= n; i++)
	{
		if (a[i] == '1') ate[i][0] = 0;
		else ate[i][0] = ate[i-1][0]+1;
 
		if (a[i] == '0') ate[i][1] = 0;
		else ate[i][1] = ate[i-1][1]+1;
	}
 	
 	seg[0].build(1, 0, n);
 	seg[1].build(1, 0, n);
 
 	seg[0].upd(1, 0, n, 0, b[1] == '1');
 	seg[1].upd(1, 0, n, 0, b[1] == '0');
 
	for (int i = 1; i <= n; i++)
	{
		dp[i][0] = dp[i][1] = n+1;
 
		pref[i][0] = pref[i-1][0];
		if (i > 1) pref[i][0] += (b[i] == '1' && b[i-1] == '0');
 
		pref[i][1] = pref[i-1][1];
		if (i > 1) pref[i][1] += (b[i] == '0' && b[i-1] == '1');
 
		if (a[i] == '0') dp[i][0] = pref[i][0] + seg[0].query(1, 0, n, i-ate[i][0], i-1);
		if (a[i] == '1') dp[i][1] = pref[i][1] + seg[1].query(1, 0, n, i-ate[i][1], i-1);
 
		dp[i][0] = min(dp[i][0], 1 + pref[i][0] + seg[0].query(1, 0, n, 0, i-ate[i][0]-1));
		dp[i][1] = min(dp[i][1], 1 + pref[i][1] + seg[1].query(1, 0, n, 0, i-ate[i][1]-1));
 
		seg[0].upd(1, 0, n, i, dp[i][1] - pref[i][0] + (b[i+1] == '1') - 2*(b[i] == '0' && b[i+1] == '1'));
		seg[1].upd(1, 0, n, i, dp[i][0] - pref[i][1] + (b[i+1] == '0') - 2*(b[i] == '1' && b[i+1] == '0'));
	}
 
	printf("%d\n", min(dp[n][0], dp[n][1]));
}
