// BOI 2017 - Political Development
// Lúcio Cardoso

// Solution is the same as: https://github.com/Triplem5ds/Competitve-Programming/blob/master/Olympiad/Baltic%2017-PoliticalDevelopment.cc

#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

const int maxn = 5e4+10;

int n, k;

set<int> grafo[maxn], grafo_rev[maxn];

int main(void)
{
	scanf("%d %d", &n, &k);

	for (int i = 0; i < n; i++)
	{
		int d;
		scanf("%d", &d);

		for (int j = 0; j < d; j++)
		{
			int v;
			scanf("%d", &v);

			grafo[i].insert(v);
			grafo_rev[v].insert(i);
		}
	}

	set<pii> st;

	for (int i = 0; i < n; i++)
		st.insert({grafo[i].size(), i});

	int ans = 0;

	while (st.size())
	{
		int u = st.begin()->second;
		st.erase(st.begin());

		vector<int> V;
		for (auto v: grafo[u])
			V.push_back(v);

		for (int mask = 0; mask < 1<<((int)V.size()); mask++)
		{
			bool ok = 1;

			for (int i = 0; i < (int)V.size(); i++)
			{
				if (!(mask&(1<<i))) continue;

				for (int j = 0; j < (int)V.size(); j++)
				{
					if (i == j || !(mask&(1<<j))) continue;

					if (grafo[V[i]].find(V[j]) == grafo[V[i]].end())
					{
						ok = 0;
						break;
					}
				}

				if (!ok) break;
			}

			if (ok) ans = max(ans, __builtin_popcount(mask));
		}

		for (auto v: grafo_rev[u])
		{
			if (st.find({grafo[v].size(), v}) == st.end()) continue;

			st.erase({grafo[v].size(), v});

			grafo[v].erase(u);

			st.insert({grafo[v].size(), v});
		}
	}

	printf("%d\n", ans+1);
}
