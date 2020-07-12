// Infoarena - Paintball
// Lúcio Cardoso

// Solution is the same as in: https://github.com/stefdasca/CompetitiveProgramming/blob/master/Infoarena/paintball.cpp

#include <bits/stdc++.h>
 
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
 
using namespace std;
 
const int maxn = 1e6+1;
 
int n;
int f[maxn];
int grau[maxn];
 
int comp[maxn], cc;
int cnt_leaf[maxn], sz[maxn];
 
bool mark[maxn];
 
inline void dfs(int u)
{
	mark[u] = 1;
 
	if (mark[f[u]] && !comp[f[u]])
	{
		comp[u] = ++cc;
		++sz[comp[u]], cnt_leaf[comp[u]] += (!grau[u]);
		return;
	}
 
	if (!comp[f[u]]) dfs(f[u]);
 
	comp[u] = comp[f[u]];
	++sz[comp[u]], cnt_leaf[comp[u]] += (!grau[u]);
}
 
inline int get_min(void)
{
	int ans = 0;
	queue<int> leaf;
 
	for (int i = 1; i <= n; i++)
	{
		if (!grau[i])
			leaf.push(i);
 
		mark[i] = 0;
	}
 
	while (leaf.size())
	{
		int u = leaf.front(); leaf.pop();
		mark[u] = 1, sz[comp[u]]--;
 
		if (mark[f[u]]) continue;
 
		ans++, mark[f[u]] = 1;
		sz[comp[u]]--;
 
		if (!mark[f[f[u]]])
		{
			grau[f[f[u]]]--;
			if (!grau[f[f[u]]]) leaf.push(f[f[u]]);
		}
	}
 
	for (int i = 1; i <= cc; i++)
		ans += (sz[i]+1)/2;
 
	return ans;
}
 
inline int get_max(void)
{
	int ans = n;
 
	for (int i = 1; i <= cc; i++)
	{
		if (cnt_leaf[i] == 0 && sz[i] > 1)
			ans--;
		else
			ans -= cnt_leaf[i];
	}
 
	return ans;
}
 
int main(void)
{
	ios::sync_with_stdio(0);
    cin.tie(nullptr);

	freopen("paintball.in", "r", stdin);
	freopen("paintball.out", "w", stdout);
 
	cin >> n;
 
	for (int i = 1; i <= n; i++)
	{
		cin >> f[i];
		grau[f[i]]++;
	}
 
	for (int i = 1; i <= n; i++)
		if (!mark[i])
			dfs(i);
 
	int mx = get_max();
	int mn = get_min();
	cout << mn << " " << mx << "\n";
}
