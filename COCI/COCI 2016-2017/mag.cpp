
// COCI 2016/2017 - Mag
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e6+5;

int num[maxn], P=-1, Q=-1;

int dp_down[maxn], dp_up[maxn];

vector<int> grafo[maxn];

void dfs_down(int u, int p)
{
	for (auto v: grafo[u])
	{
		if (v == p) continue;

		dfs_down(v, u);

		if (num[v] == 1) 
			dp_down[u] = max(dp_down[u], dp_down[v]+1);
	}
}

void dfs_up(int u, int p)
{
	int tam = (int)grafo[u].size();
	vector<int> pref(tam+2), suf(tam+2);

	pref[0] = suf[tam+1] = 0;

	for (int i = 1; i <= tam; i++)
	{
		int v = grafo[u][i-1];
		if (v == p) continue;

		pref[i] = pref[i-1];
		if (num[v] == 1) pref[i] = max(pref[i], dp_down[v]+1);
	}

	for (int i = tam; i >= 1; i--)
	{
		int v = grafo[u][i-1];
		if (v == p) continue;

		suf[i] = suf[i+1];
		if (num[v] == 1) suf[i] = max(suf[i], dp_down[v]+1);
	}

	int m1 = dp_up[u], m2 = 0, ans = 0;
	for (int i = 1; i <= tam; i++)
	{
		int v = grafo[u][i-1];
		if (v == p) continue;

		if (num[v] == 1)
		{
			if (dp_down[v]+1 > m1) m2 = m1, m1 = dp_down[v]+1;
			else if (dp_down[v]+1 > m2) m2 = dp_down[v]+1;
		}

		if (num[u] == 1)
			dp_up[v] = max({dp_up[u], pref[i-1], suf[i+1]})+1;
		else dp_up[v] = 0;

		dfs_up(v, u);
	}

	ans = m1+m2+1;

	long long A = 1ll*num[u]*1ll*Q;
	long long B = 1ll*ans*1ll*P;

	if (P == -1 || A < B) P = num[u], Q = ans;
}

int main(void)
{
	int n;
	cin >> n;

	for (int i = 1; i < n; i++)
	{
		int u, v;
		cin >> u >> v;

		grafo[u].push_back(v); grafo[v].push_back(u);
	}

	for (int i = 1; i <= n; i++)
		cin >> num[i];

	dfs_down(1, 0); dfs_up(1, 0);

	int g = __gcd(P, Q);

	cout << P / g << "/" << Q / g << "\n";
}
