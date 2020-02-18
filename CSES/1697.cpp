// CSES 1697 - Chess Tournament
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5+10;

int grau[maxn];

int main(void)
{
	int n;
	scanf("%d", &n);

	multiset<pair<int, int>> st;
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &grau[i]);

		st.insert({-grau[i], i});
	}

	vector<pair<int, int>> ans;

	while (st.size() > 0)
	{
		int u = st.begin()->second;
		st.erase(st.begin());

		vector<pair<int, int>> insere;

		auto it = st.begin();

		while (true)
		{
			if (it == st.end() || grau[u] == 0) break;

			grau[u]--, grau[it->second]--;
			ans.push_back({u, it->second});

			insere.push_back({it->first+1, it->second});
			it = st.erase(it);
		}

		for (auto pp: insere)
			st.insert(pp);
	}

	for (int i = 1; i <= n; i++)
	{
		if (grau[i] != 0)
		{
			printf("IMPOSSIBLE\n");
			return 0;
		}
	}

	printf("%d\n", ans.size());
	for (auto e: ans)
		printf("%d %d\n", e.first, e.second);
}
