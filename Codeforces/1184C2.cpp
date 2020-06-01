// Codeforces 1184C2 - Heidi and the Turing Test (Medium)
// Lúcio Cardoso

// Solution is the same as in editorial

#include <bits/stdc++.h>

#define x first
#define y second

using namespace std;

typedef pair<int, int> pii;

const int maxn = 4e6+10;

struct Event
{
	int x, y1, y2;
	int tipo;
} event[maxn];

int tree[4*maxn], lazy[4*maxn];

pii pt[maxn];

bool comp(Event a, Event b)
{
	if (a.x == b.x) return a.tipo < b.tipo;
	return a.x < b.x;
}

void flush(int node, int l, int r)
{
	if (!lazy[node]) return;

	if (l != r)
	{
		lazy[2*node] += lazy[node];
		lazy[2*node+1] += lazy[node];
	}

	tree[node] += lazy[node];
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

void compress(int n)
{
	map<int, int> mp1, mp2;

	for (int i = 1; i <= n; i++)
	{
		mp1[event[i].x] = 0;
		mp2[event[i].y1] = 0;
		mp2[event[i].y2] = 0; 
	}

	int aux = 0;
	for (auto &x: mp1)
		x.second = ++aux;

	aux = 0;
	for (auto &x: mp2)
		x.second = ++aux;

	for (int i = 1; i <= n; i++)
	{
		event[i].x = mp1[event[i].x];
		event[i].y1 = mp2[event[i].y1];
		event[i].y2 = mp2[event[i].y2];
	}
}

int main(void)
{
	int n, r;
	scanf("%d %d", &n, &r);

	int m = 0;

	for (int i = 1; i <= n; i++)
	{
		scanf("%d %d", &pt[i].x, &pt[i].y);

		pt[i] = {pt[i].x-pt[i].y, pt[i].x+pt[i].y};

		event[++m] = {pt[i].x, pt[i].y, pt[i].y + 2*r, 0};
		event[++m] = {pt[i].x + 2*r, pt[i].y, pt[i].y + 2*r, 1};
	}

	compress(m);

	sort(event+1, event+m+1, comp);

	int ans = 0;

	for (int i = 1; i <= m; i++)
	{
		int add = (event[i].tipo == 0 ? 1 : -1);

		upd(1, 1, maxn-1, event[i].y1, event[i].y2, add);

		flush(1, 1, n);
		ans = max(ans, tree[1]);
	}

	printf("%d\n", ans);
}
