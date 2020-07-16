// Codeforces 1380F - Strange Addition
// Lúcio Cardoso

// Solution is the same as in editorial

#include <bits/stdc++.h>
 
using namespace std;
 
const int maxn = 5e5+10;
const int mod = 998244353;
 
struct Node
{
	int notBoth, notL, notR, all;
};
 
int qtd[100];
int a[maxn];
 
struct SegmentTree
{
	Node tree[4*maxn];
 
	void merge(int node, int l, int r)
	{
		int mid = (l+r)>>1;
		int x = (a[mid] == 1 ? qtd[10*a[mid]+a[mid+1]] : 0);
 
		tree[node].notBoth = (1ll*tree[2*node].notL*tree[2*node+1].notR)%mod;
		tree[node].notBoth = (1ll*tree[node].notBoth + ((mid-l+1 >= 2 && r-mid >= 2) ? 1ll*x*(1ll*tree[2*node].notBoth*tree[2*node+1].notBoth)%mod : 0))%mod;
 
		tree[node].notL = (1ll*tree[2*node].notL*tree[2*node+1].all)%mod;
		tree[node].notL = (1ll*tree[node].notL + ((mid-l+1 >= 2 && r-mid >= 1) ? 1ll*x*(1ll*tree[2*node].notBoth*tree[2*node+1].notL)%mod : 0))%mod;
 
		tree[node].notR = (1ll*tree[2*node].all*tree[2*node+1].notR)%mod;
		tree[node].notR = (1ll*tree[node].notR + ((mid-l+1 >= 1 && r-mid >= 2) ? 1ll*x*(1ll*tree[2*node].notR*tree[2*node+1].notBoth)%mod : 0))%mod;
 
		tree[node].all = (1ll*tree[2*node].all*tree[2*node+1].all)%mod;
		tree[node].all = (1ll*tree[node].all + ((mid-l+1 >= 1 && r-mid >= 1) ? 1ll*x*(1ll*tree[2*node].notR*tree[2*node+1].notL)%mod : 0))%mod;
	}
 
	void build(int node, int l, int r)
	{
		if (l == r)
		{
			tree[node] = {1, 1, 1, a[l]+1};
			return;
		}
 
		int mid = (l+r)>>1;
 
		build(2*node, l, mid); build(2*node+1, mid+1, r);
 
		merge(node, l, r);
	}
 
	void upd(int node, int l, int r, int pos, int v)
	{
		if (l == r)
		{
			tree[node] = {1, 1, 1, v+1};
			return;
		}
 
		int mid = (l+r)>>1;
 
		if (pos <= mid) upd(2*node, l, mid, pos, v);
		else upd(2*node+1, mid+1, r, pos, v);
 
		merge(node, l, r);
	}
} seg;
 
 
int main(void)
{
	int n, m;
	scanf("%d %d", &n, &m);
 
	for (int i = 0; i <= 9; i++)
		for (int j = 0; j <= 9; j++)
			qtd[i+j]++;
 
	for (int i = 1; i <= n; i++)
	{
		char c;
		scanf(" %c", &c);
 
		a[i] = (int)(c-'0');
	}
 
	seg.build(1, 1, n);
 
	while (m--)
	{
		int c, d;
		scanf("%d %d", &c, &d);
 
		a[c] = d;
		seg.upd(1, 1, n, c, d);
 
		printf("%d\n", seg.tree[1].all);
	}
}
