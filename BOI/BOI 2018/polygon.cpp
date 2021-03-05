// BOI 2018 - Love Polygon
// Lúcio Cardoso

#include <bits/stdc++.h>
 
using namespace std;
 
const int maxn = 1e5+10;
 
int f[maxn];
 
int comp[maxn], nivel[maxn], cc;
int ini[maxn], fim[maxn];
int mark[maxn];
 
bool done[maxn], done2[maxn], incycle[maxn];
 
vector<int> all[maxn];
 
void dfs(int u)
{
	mark[u] = 1;
 
	if (mark[f[u]] == 1)
	{
		comp[u] = ++cc;
		mark[u] = 2;
		ini[cc] = f[u], fim[cc] = u;
		return;
	}
 
	if (!mark[f[u]]) dfs(f[u]);
 
	comp[u] = comp[f[u]], mark[u] = 2;
	nivel[u] = nivel[f[u]]+1;
}
 
int solve_ciclo(int c)
{
	if (f[fim[c]] == fim[c]) return 0;
 
	for (auto u: all[c])
		done2[u] = done[u];
 
	int ans = 0;
 
	if (f[ini[c]] == fim[c]) ans += 2;
	else ans++;
 
	done2[ini[c]] = done2[fim[c]] = 1;
 
	for (auto u: all[c])
	{
		if (done2[u]) continue;
 
		if (f[u] != u && !done2[f[u]])
		{
			ans++;
			done2[u] = done2[f[u]] = 1;
		}
	}
 
	return ans;
}
 
int solve_nociclo(int c)
{
	for (auto u: all[c])
		done2[u] = done[u];
	
	int ans = 0;
 
	for (auto u: all[c])
	{
		if (done2[u]) continue;
 
		if (f[u] != u && !done2[f[u]])
		{
			ans++;
			done2[u] = done2[f[u]] = 1;
		}
	}
 
	return ans;
}
 
int main(void)
{
	int n;
	cin >> n;
 
	map<string, int> mp;
 
	int ind = 0;
 
	for (int i = 1; i <= n; i++)
	{
		string s1, s2;
		cin >> s1 >> s2;
 
		if (mp.find(s1) == mp.end()) mp[s1] = ++ind;
		if (mp.find(s2) == mp.end()) mp[s2] = ++ind;
 
		f[mp[s1]] = mp[s2];
	}
 
	if (n&1)
	{
		cout << "-1\n";
		return 0;
	}
 
	for (int i = 1; i <= n; i++)
		if (!mark[i])
			dfs(i);
 
	for (int i = 1; i <= cc; i++)
	{
		for (int u = ini[i]; ; u = f[u])
		{
			incycle[u] = 1;
			if (u == fim[i]) break;
		}
	}
 
	int ans = n;
 
	vector<int> v;
	for (int i = 1; i <= n; i++)
	{
		if (!incycle[i] && !incycle[f[i]])
			v.push_back(i);
		else
			all[comp[i]].push_back(i);
	}
 
	sort(v.begin(), v.end(), [&](int a, int b) {return nivel[a] > nivel[b];});
 
	for (auto u: v)
	{
		if (done[u]) continue;
 
		if (f[u] != u && !done[f[u]])
		{
			ans--;
			done[u] = done[f[u]] = 1;
		}
	}
 
	for (int c = 1; c <= cc; c++)
	{
		sort(all[c].begin(), all[c].end(), [&](int a, int b) {return nivel[a] > nivel[b];});
		ans -= max(solve_ciclo(c), solve_nociclo(c));
	}
 
	cout << ans << "\n";
}
