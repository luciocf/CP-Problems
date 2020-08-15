// Codeforces 1370F2 - The Hidden Pair (Hard Version)
// Lúcio Cardoso

// Solution is the same as in editorial

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e3+10;

vector<int> grafo[maxn], nivel[maxn];

void dfs(int u, int p, int d)
{
	nivel[d].push_back(u);

	for (auto v: grafo[u])
		if (v != p)
			dfs(v, u, d+1);
}

void ask(vector<int> &V)
{
	cout << "? " << V.size();
	for (auto v: V)
		cout << " " << v;
	cout << endl;
}

int main(void)
{
	int tc;
	cin >> tc;

	while (tc--)
	{
		int n;
		cin >> n;

		for (int i = 0; i <= n; i++)
		{
			grafo[i].clear();
			nivel[i].clear();
		}

		for (int i = 1; i < n; i++)
		{
			int u, v;
			cin >> u >> v;

			grafo[u].push_back(v);
			grafo[v].push_back(u);
		}

		vector<int> V;

		for (int i = 1; i <= n; i++)
			V.push_back(i);

		ask(V);

		int r, d;
		cin >> r >> d;

		dfs(r, 0, 0);

		int ini = (d+1)/2, fim = d, u, nivel_u, v;

		while (ini <= fim)
		{
			int mid = (ini+fim)>>1;

			if (nivel[mid].size() == 0)
			{
				fim = mid-1;
				continue;
			}

			ask(nivel[mid]);

			int x, y;
			cin >> x >> y;

			if (y == d) u = x, nivel_u = mid, ini = mid+1;
			else fim = mid-1;
		}

		for (int i = 0; i <= n; i++)
			nivel[i].clear();
		
		dfs(u, 0, 0);

		ask(nivel[d]);

		int y;
		cin >> v >> y;

		cout << "! " << u << " " << v << endl;

		string larrydavid;

		cin >> larrydavid;
	}
}
