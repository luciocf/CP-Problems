// Codeforces 1494D - Dogeforces
// Lúcio Figueiredo

#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

const int maxn = 510;

pii a[maxn][maxn];

int v[maxn];

vector<int> anc[maxn];

int main(void)
{
	int n;
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			int x;
			scanf("%d", &x);

			a[i][j] = {x, j};

			if (j == i) v[i] = x;
		}

		sort(a[i]+1, a[i]+n+1);
	}

	int id = n;

	for (int i = 1; i <= n; i++)
	{
		int qtd = 0;

		for (int j = n; j > 1; j--)
		{
			if (j == n || a[i][j].first != a[i][j+1].first)
			{
				++qtd;

				int k = a[i][j].second;

				if (qtd > anc[i].size())
				{
					id++;

					anc[i].push_back(id);
					v[id] = a[i][j].first;
				}

				for (int k = j; k > 1; k--)
					if (qtd > anc[a[i][k].second].size())
						anc[a[i][k].second].push_back(id);
			}
		}
	}

	printf("%d\n", id);

	for (int i = 1; i <= id; i++)
		printf("%d ", v[i]);
	printf("\n");

	set<pii> st;

	for (int i = 1; i <= n; i++)
	{
		reverse(anc[i].begin(), anc[i].end());

		st.insert({i, anc[i][0]});

		for (int j = 1; j < anc[i].size(); j++)
			st.insert({anc[i][j-1], anc[i][j]});
	}

	printf("%d\n", anc[1].back());
	for (auto pp: st)
		printf("%d %d\n", pp.first, pp.second);
}
