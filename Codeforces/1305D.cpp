// Codeforces 1305D - Kuroni and the Celebration
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e3+10;

int n;

int grau[maxn];

bool mark[maxn];

vector<int> grafo[maxn];

int main(void)
{
	cin >> n;

	for (int i = 1; i < n; i++)
	{
		int u, v;
		cin >> u >> v;

		grafo[u].push_back(v);
		grafo[v].push_back(u);

		grau[u]++, grau[v]++;
	}

	int tot = n;

	while (true)
	{
		if (tot == 1)
		{
			for (int i = 1; i <= n; i++)
			{
				if (!mark[i])
				{
					cout << "! " << i << "\n"; cout.flush();
					exit(0);
				}
			}
		}

		int a = -1, b = -1;

		for (int i = 1; i <= n; i++)
		{
			if (!mark[i] && grau[i] == 1 && a == -1)
				a = i;
			else if (!mark[i] && grau[i] == 1)
				b = i;
		}

		cout << "? " << a << " " << b << "\n"; cout.flush();

		int lca;
		cin >> lca;

		if (lca == a || lca == b)
		{
			cout << "! " << lca << "\n"; cout.flush();
			exit(0);
		}

		for (auto v: grafo[a])
			grau[v]--;
		for (auto v: grafo[b])
			grau[v]--;

		tot -= 2;
		mark[a] = mark[b] = 1;
	}
}
