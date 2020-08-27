// Codeforces 1400G - Mercenaries
// Lúcio Cardoso

// Solution is the same as in editorial.

#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

typedef pair<int, int> pii;

const int maxn = 3e5+10;
const int mod = 998244353;

int n, m;
pii range[maxn], edge[maxn];

int inside[maxn];

int pref[41][maxn];

int fat[maxn];
int inv[maxn];

int pot(int a, int b)
{
	if (!b) return 1;
 
	int t = pot(a, b/2);
 
	if (b&1) return (1ll*a*((1ll*t*t)%mod))%mod;
	return (1ll*t*t)%mod;
}
 
int choose(int a, int b)
{
	if (a < b) return 0;
	return ((1ll*fat[a]*inv[a-b])%mod * 1ll*inv[b])%mod;
}

void get_inside(void)
{
	vector<int> aux;

	for (int i = 1; i <= n; i++)
		aux.push_back(range[i].ss);

	sort(aux.begin(), aux.end());

	for (int i = 1; i <= n; i++)
		inside[i] += (int)(lower_bound(aux.begin(), aux.end(), i)-aux.begin());

	aux.clear();

	for (int i = 1; i <= n; i++)
		aux.push_back(range[i].ff);

	sort(aux.begin(), aux.end());

	for (int i = 1; i <= n; i++)
		inside[i] += (int)(aux.end() - upper_bound(aux.begin(), aux.end(), i));

	for (int i = 1; i <= n; i++)
		inside[i] = n-inside[i];
}

void precalc(int k)
{
	for (int i = 1; i <= n; i++)
	{
		pref[k][i] = pref[k][i-1];

		if (inside[i] >= k && i >= k)
			pref[k][i] = (pref[k][i] + choose(inside[i]-k, i-k))%mod;
	}
}

int soma(int l, int r, int k)
{
	return (pref[k][r]-pref[k][l-1]+mod)%mod;
}

int main(void)
{
	scanf("%d %d", &n, &m);

	fat[0] = 1;
	for (int i = 1; i <= n; i++)
		fat[i] = (1ll*fat[i-1]*i)%mod;

	for (int i = 0; i <= n; i++)
		inv[i] = pot(fat[i], mod-2);

	for (int i = 1; i <= n; i++)
		scanf("%d %d", &range[i].ff, &range[i].ss);

	for (int i = 1; i <= m; i++)
		scanf("%d %d", &edge[i].ff, &edge[i].ss);

	get_inside();

	for (int i = 1; i <= 40; i++)
		precalc(i);

	int ans = 0;

	for (int i = 1; i <= n; i++)
		if (inside[i] >= i)
			ans = (ans + choose(inside[i], i))%mod;

	for (int mask = 1; mask < (1<<m); mask++)
	{
		int l = 0, r = n+1;

		set<int> st;

		for (int i = 0; i < m; i++)
		{
			if (mask&(1<<i))
			{
				int u = edge[i+1].ff, v = edge[i+1].ss;

				st.insert(u); st.insert(v);

				l = max({l, range[u].ff, range[v].ff});
				r = min({r, range[u].ss, range[v].ss});
			}
		}

		if (l > r) continue;

		int k = st.size(), sz = __builtin_popcount(mask);
		int v = soma(l, r, k);

		if (sz%2) ans = (ans - v + mod)%mod;
		else ans = (ans + v)%mod;
	}

	printf("%d\n", ans);
}
