// Seletiva IOI 2015 - Estação
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 2e5+10;

int n, m;

int grau[maxn];

int cor[maxn];

bool mark[maxn];

vector<int> grafo[maxn], grafoT[maxn];

vector<int> topo;

set<int> st1, st2;

void dfs(int u)
{
	mark[u] = 1;

	for (auto v: grafo[u])
		if (!mark[v])
			dfs(v);

	topo.push_back(u);
}

void init(void)
{
	memset(cor, 0, sizeof cor);

	st1.clear(), st2.clear();

	for (int i = 2; i <= 2*n; i++)
		st1.insert(i), st2.insert(i);
}

int solve(int flag)
{
	init();

	if (flag == 1) st1.insert(1);
	else st2.insert(1);

	int ans = 0;

	for (auto u: topo)
	{
		int C;

		if ((flag == 1 && u%2) || (flag == 2 && u%2 == 0)) C = 1;
		else C = 2;

		for (auto v: grafoT[u])
		{
			if (u%2) C = max(C, *(st1.lower_bound(cor[v])));
			else C = max(C, *(st2.lower_bound(cor[v])));
		}

		cor[u] = C;
		ans = max(ans, C);

		if (u%2 && st2.find(C) != st2.end()) st2.erase(C);
		else if (u%2 == 0 && st1.find(C) != st1.end()) st1.erase(C);
	}

	return ans;
}

int main(void)
{
	scanf("%d %d", &n, &m);

	for (int i = 1; i <= m; i++)
	{
		int u, r, v;
		scanf("%d %d %d", &u, &r, &v);

		if (r == 1)
		{
			grafo[u].push_back(v), grau[v]++;
			grafoT[v].push_back(u);
		}
		else
		{
			grafo[v].push_back(u), grau[u]++;
			grafoT[u].push_back(v);
		}
	}

	if (n == 1)
	{
		printf("1\n");
		return 0;
	}

	for (int i = 1; i <= 2*n; i++)
		if (grau[i] == 0)
			dfs(i);

	reverse(topo.begin(), topo.end());

	printf("%d\n", min(solve(1), solve(2)));
}
