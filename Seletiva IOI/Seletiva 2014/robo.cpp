// Seletiva IOI 2014 - Robô
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

const int maxn = 2e5+10;

int tree[4*maxn], lazy[4*maxn];
pii range[maxn];

int ans[maxn];

void flush(int node, int l, int r)
{
	if (!lazy[node]) return;

	if (l != r)
		lazy[2*node] = lazy[2*node+1] = lazy[node];

	tree[node] = lazy[node];
	lazy[node] = 0;
}

void upd(int node, int l, int r, int a, int b, int v)
{
	flush(node, l, r);
	if (l > b || r < a) return;

	if (l >= a && r <= b)
	{
		lazy[node] = v;
		flush(node, l, r);
		return;
	}

	int mid = (l+r)>>1;

	upd(2*node, l, mid, a, b, v); upd(2*node+1, mid+1, r, a, b, v);

	tree[node] = max(tree[2*node], tree[2*node+1]);
}

int main(void)
{
	int y, x;
	scanf("%d %d", &y, &x);
	y++;

	for (int i = 1; i < x; i++)
	{
		scanf("%d %d", &range[i].first, &range[i].second);
		range[i].first++, range[i].second++;
	}

	upd(1, 1, y, 1, y, x+1);

	for (int i = x; i > 1; i--)
	{
		upd(1, 1, y, range[i-1].first, range[i-1].second, i);

		if (tree[1] == x+1) ans[i] = 1;
		else ans[i] = 2+ans[tree[1]];

	}

	if (tree[1] == x+1) printf("1\n");
	else printf("%d\n", 2+ans[tree[1]]);
}
