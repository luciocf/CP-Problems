// POI 2007 - Offices
// Lúcio Cardoso

// TODO Solution

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5+10;

int n;

set<int> st;

vector<int> grafo[maxn];

int bfs(int s)
{
	queue<int> fila;
	fila.push(s); st.erase(s);

	int sz = 0;

	while (!fila.empty())
	{
		int u = fila.front(); fila.pop();
		++sz;

		map<int, int> mark;
		for (auto v: grafo[u])
			mark[v] = 1;

		for (auto v: grafo[u])
		{
			auto it = st.lower_bound(v);
			if (it == st.begin()) continue;

			--it;
			if (mark[*it]) continue;

			fila.push(*it); st.erase(it);
		}

		if (grafo[u].size())
		{
			while (true)
			{
				auto it = st.upper_bound(grafo[u].back());

				if (it == st.end()) break;

				fila.push(*it); st.erase(it);
			}
		}
	}

	return sz;
}

int main(void)
{
	int m;
	scanf("%d %d", &n, &m);

	for (int i = 1; i <= n; i++)
		st.insert(i);

	for (int i = 1; i <= m; i++)
	{
		int u, v;
		scanf("%d %d", &u, &v);

		grafo[u].push_back(v);
		grafo[v].push_back(u);
	}

	for (int i = 1; i <= n; i++)
	{
		st.insert(i);

		sort(grafo[i].begin(), grafo[i].end());
	}

	vector<int> ans;

	for (int i = 1; i <= n; i++)
		if (st.find(i) != st.end())
			ans.push_back(bfs(i));

	sort(ans.begin(), ans.end());

	printf("%d\n", ans.size());
	for (auto c: ans)
		printf("%d ", c);
	printf("\n");
}
