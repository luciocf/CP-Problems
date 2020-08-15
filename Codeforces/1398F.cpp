// Codeforces 1398F - Controversial Rounds
// Lúcio Cardoso

// Solution is the same as in editorial, however finding next[] with a segment tree

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e6+10;

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

	int get(int node, int l, int r, int pos, int k)
	{
		if (r < pos || tree[node] < k) return -1;
		if (l == r) return l;

		int mid = (l+r)>>1;

		int p1 = get(2*node, l, mid, pos, k);

		if (p1 == -1) return get(2*node+1, mid+1, r, pos, k);
		return p1;
	}
} seg;

string s;

int pref[2][maxn];

int mx[maxn];

bool ok(int pos, int k)
{
	int sa = pref[0][pos+k-1] - (pos == 0 ? 0 : pref[0][pos-1]);
	int sb = pref[1][pos+k-1] - (pos == 0 ? 0 : pref[1][pos-1]);

	return ((sa == 0) || (sb == 0));
}

int main(void)
{
	ios::sync_with_stdio(false); cin.tie(0);

	int n;
	cin >> n;

	cin >> s;

	if (s[0] == '0') pref[0][0] = 1;
	if (s[0] == '1') pref[1][0] = 1;

	for (int i = 1; i < n; i++)
	{
		pref[0][i] = pref[0][i-1] + (s[i] == '0');
		pref[1][i] = pref[1][i-1] + (s[i] == '1');
	}

	for (int i = 0; i < n; i++)
	{
		int ini = 1, fim = n-i;
		mx[i] = 1;

		while (ini <= fim)
		{
			int mid = (ini+fim)>>1;

			if (ok(i, mid)) mx[i] = mid, ini = mid+1;
			else fim = mid-1;
		}

		seg.upd(1, 0, n-1, i, mx[i]);
	}

	for (int i = 1; i <= n; i++)
	{
		int pos = 0, ans = 0;

		while (true)
		{
			int p = seg.get(1, 0, n-1, pos, i);

			if (p == -1) break;

			++ans;
			pos = p+i;
		}

		printf("%d ", ans);
	}
	printf("\n");
}
