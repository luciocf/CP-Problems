// BOI 2015 - Network
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 5e5+10;

typedef pair<int, int> pii;

int leaf[maxn], tt;

vector<int> grafo[maxn];

void dfs(int u, int p)
{
	for (auto v: grafo[u])
	{
		if (v == p) continue;
		dfs(v, u);
	}

	if (grafo[u].size() == 1) leaf[++tt] = u;
}

int main(void)
{
	int n;
	cin >> n;

	for (int i = 1; i < n; i++)
	{
		int u, v;
		cin >> u >> v;

		grafo[u].push_back(v);
		grafo[v].push_back(u);
	}

	int root;
	for (int i = 1; i <= n; i++)
		if (grafo[i].size() > 1) root = i;

	dfs(root, 0);

	int ans = (tt+1)/2;

	cout << ans << "\n";
	for (int i = 1; i < ans; i++)
		cout << leaf[i] << " " << leaf[i+ans] << "\n";

	if (tt&1) cout << leaf[ans] << " " << leaf[1] << "\n";
	else cout << leaf[ans] << " " << leaf[tt] << "\n";
}
