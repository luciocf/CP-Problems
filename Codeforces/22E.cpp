// CF 22E - Scheme
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

const int maxn = 1e5+10;

int n;
int f[maxn];

int in[maxn];
int comp[maxn], head[maxn], cc;

int mark[maxn];

vector<int> folha[maxn];

void dfs(int u)
{
	if (mark[f[u]] == 1)
	{
		++cc;
		comp[u] = cc, head[cc] = u;
		mark[u] = 2;
		return;
	}

	mark[u] = 1;

	if (mark[f[u]] == 0)
		dfs(f[u]);

	comp[u] = comp[f[u]];

	mark[u] = 2;
}

int main(void)
{
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &f[i]);
		in[f[i]]++;
	}

	for (int i = 1; i <= n; i++)
		if (!mark[i])
			dfs(i);

	for (int i = 1; i <= n; i++)
		if (in[i] == 0)
			folha[comp[i]].push_back(i);

	if (cc == 1 && (int)folha[1].size() == 0)
	{
		printf("0\n");
		return 0;
	}

	for (int i = 1; i <= cc; i++)
		if ((int)folha[i].size() == 0)
			folha[i].push_back(head[i]);

	vector<pii> ans;

	for (int i = 1; i <= cc; i++)
	{
		for (int j = 1; j < (int)folha[i].size(); j++)
			ans.push_back({head[i], folha[i][j]});

		if (i != cc)
			ans.push_back({head[i], folha[i+1][0]});
	}

	ans.push_back({head[cc], folha[1][0]});

	printf("%d\n", (int)ans.size());
	for (auto e: ans)
		printf("%d %d\n", e.first, e.second);
}
