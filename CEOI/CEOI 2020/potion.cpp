// CEOI 2020 - The Potion of Great Power
// Lúcio Cardoso

#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

typedef pair<int, int> pii;

const int maxn = 2e5+10;

int a[maxn];

vector<int> v1, v2;

struct List
{
	vector<vector<pii>> list[maxn];

	int find(int u, int v)
	{
		for (int i = 0; i < list[u].size(); i++)
			if (list[u][i].back().ss == v)
				return i;

		return -1;
	}

	void add(int u, int v, int d)
	{
		int i = find(u, v);

		if (i != -1) list[u][i].push_back({d, -1});
		else
		{
			i = find(u, -1);

			if (i != -1) list[u][i].push_back({d, v});
			else list[u].push_back(vector<pii>(1, {d, v}));
		}
	}

	void get(int u, int d, vector<int> &ans)
	{
		ans.clear();

		for (int i = 0; i < list[u].size(); i++)
		{
			if (list[u][i][0].ff > d) break;

			int x = (--upper_bound(list[u][i].begin(), list[u][i].end(), make_pair(d, maxn)))->ss;

			if (x != -1) ans.push_back(a[x]);
		}

		sort(ans.begin(), ans.end());
	}
} L;

int main(void)
{
	ios::sync_with_stdio(false); cin.tie(0);

	int n, k, m, q;
	cin >> n >> k >> m >> q;

	for (int i = 0; i < n; i++)
		cin >> a[i];

	for (int i = 1; i <= m; i++)
	{
		int u, v;
		cin >> u >> v;

		L.add(u, v, i); L.add(v, u, i);
	}

	while (q--)
	{
		int u, v, d;
		cin >> u >> v >> d;

		L.get(u, d, v1); L.get(v, d, v2);

		int ans = 1000000000;
		int ptr = 0;
 
		for (auto x: v1)
		{
			while (ptr+1 < v2.size() && v2[ptr+1] <= x)
				ptr++;
 
			if (ptr < v2.size()) ans = min(ans, abs(x-v2[ptr]));
			if (ptr+1 < v2.size()) ans = min(ans, abs(x-v2[ptr+1]));
		}

		cout << ans << endl;
	}
}
