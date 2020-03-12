// Codeforces 1312G - Autocompletion
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

const int maxn = 1e6+10;

int n, add;

int ans[maxn];

bool mark[maxn];

int grafo[maxn][27];

multiset<int> st;

void dfs(int u, int p)
{
	int x = 0;

	if (mark[u])
	{
		++add;

		ans[u] = (st.size() ? *st.begin() : 1e9) + add;
		ans[u] = min(ans[u], ans[p]+1);

		x = ans[u]-add+1;
		st.insert(x);
	}
	else if (u)
	{
		ans[u] = ans[p]+1;

		x = ans[u]-add;
		st.insert(x);
	}
	else st.insert(0);

	for (int i = 0; i < 26; i++)
	{
		int v = grafo[u][i];

		if (v) dfs(v, u);
	}

	st.erase(st.find(x));
}

int main(void)
{
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
	{
		int u;
		char c;
		scanf("%d %c", &u, &c);

		grafo[u][(int)(c-'a')] = i;
	}

	int k;
	scanf("%d", &k);

	vector<int> get;

	for (int i = 1; i <= k; i++)
	{
		int u;
		scanf("%d", &u);

		get.push_back(u);
		mark[u] = 1;
	}

	dfs(0, 0);

	for (auto u: get)
		printf("%d ", ans[u]);
	printf("\n");
}
