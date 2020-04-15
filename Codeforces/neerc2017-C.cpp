// NEERC 2017 - A - Archery Tournament
// Lúcio Cardoso

#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

typedef pair<int, int> pii;
typedef long long ll;

const int maxn = 1e6+10;
const int inf = 1e9+10;

struct Query
{
	int op, x, y;
} Q[maxn];

pii pt[maxn];

vector<int> nodes[maxn];

map<int, int> mp;
set<int> tree[4*maxn];

ll dist(pii a, pii b)
{
	return (1ll*(a.ff-b.ff)*(a.ff-b.ff) + 1ll*(a.ss-b.ss)*(a.ss-b.ss));
}

bool inside(pii p, pii c)
{
	return (dist(p, c) < 1ll*c.ss*c.ss);
}

void upd(int node, int l, int r, int a, int b, int ind)
{
	if (l > b || r < a) return;
	if (l >= a && r <= b)
	{
		tree[node].insert(ind);
		nodes[ind].push_back(node);
		return;
	}

	int mid = (l+r)>>1;

	upd(2*node, l, mid, a, b, ind); upd(2*node+1, mid+1, r, a, b, ind);
}

int query(int node, int l, int r, pii p)
{
	for (auto it: tree[node])
		if (inside(p, pt[it]))
			return it;

	if (l == r) return -1;

	int mid = (l+r)>>1;

	if (mp[p.ff] <= mid) return query(2*node, l, mid, p);
	return query(2*node+1, mid+1, r, p); 
}

int main(void)
{
	int q;
	scanf("%d", &q);

	for (int i = 1; i <= q; i++)
	{
		scanf("%d %d %d", &Q[i].op, &Q[i].x, &Q[i].y);

		mp[Q[i].x] = 0;

		if (Q[i].op == 1)
		{
			mp[Q[i].x-Q[i].y] = 0;
			mp[Q[i].x+Q[i].y] = 0;
		}
	}

	int aux = 0;
	for (auto &x: mp)
		x.second = ++aux;

	for (int i = 1; i <= q; i++)
	{
		if (Q[i].op == 1)
		{
			int x = Q[i].x, y = Q[i].y;
			pt[i] = {x, y};

			upd(1, 1, maxn-1, mp[x-y], mp[x+y], i);
		}
		else
		{
			int x = Q[i].x, y = Q[i].y;

			int ans = query(1, 1, maxn-1, {x, y});

			if (ans != -1)
			{
				for (auto nd: nodes[ans])
					tree[nd].erase(ans);
			}

			printf("%d\n", ans);
		}
	}
}
