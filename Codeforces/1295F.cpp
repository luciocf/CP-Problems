// Codeforces 1295F - Good Contest
// Lúcio Cardoso

#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

typedef pair<int, int> pii;

const int maxn = 110;
const int mod = 998244353;

int fat[maxn];

int n;
int dp[maxn][maxn];

pii range[maxn];
vector<pii> segment;

int pot(int a, int b)
{
	if (!b) return 1;

	int t = pot(a, b/2);

	if (b&1) return (1ll*a*((1ll*t*t)%mod))%mod;
	return (1ll*t*t)%mod;
}

int choose(int a, int b)
{
	int k = 1;

	for (int i = a; i > a-b; i--)
		k = (1ll*k*i)%mod;

	return (1ll*k*pot(fat[b], mod-2))%mod;
}

bool inside(pii a, pii b)
{
	return (a.ff >= b.ff && a.ss <= b.ss);
}

int solve(int i, int j)
{
	if (i == n+1) return 1;
	if (j == segment.size()) return 0;
	if (dp[i][j] != -1) return dp[i][j];

	int ans = solve(i, j+1);

	for (int l = i; l <= n; l++)
	{
		if (!inside(segment[j], range[l])) break;

		int sz = segment[j].ss-segment[j].ff+1;
		int k = l-i+1;

		int ways = choose(sz+k-1, k);

		ans = (ans + (1ll*ways*solve(l+1, j+1))%mod)%mod;
	}

	return dp[i][j] = ans;
}

int main(void)
{
	scanf("%d", &n);

	fat[0] = 1;
	for (int i = 1; i <= n; i++)
		fat[i] = (1ll*i*fat[i-1])%mod;

	vector<int> V;

	for (int i = 1; i <= n; i++)
	{
		scanf("%d %d", &range[i].ff, &range[i].ss);
		V.push_back(range[i].ff); V.push_back(range[i].ss+1);
	}

	sort(V.begin(), V.end());
	V.erase(unique(V.begin(), V.end()), V.end());

	for (int i = 0; i < V.size()-1; i++)
		segment.push_back({V[i], V[i+1]-1});

	reverse(segment.begin(), segment.end());

	memset(dp, -1, sizeof dp);

	int prod = 1;
	for (int i = 1; i <= n; i++)
		prod = (1ll*prod*(range[i].ss-range[i].ff+1))%mod;

	printf("%d\n", (1ll*solve(1, 0)*pot(prod, mod-2))%mod);
}
