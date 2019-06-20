// USACO Gold Dec 2016 - Cow Checklist
// Lúcio Cardoso

#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

const int maxn = 1e3+10;
const long long inf = 2e18+10;

typedef long long ll;
typedef pair<int, int> pii;

int h, g;

ll dp[maxn][maxn][2];

pii H[maxn], G[maxn];

ll dist(pii A, pii B)
{
	return 1ll*(A.ff-B.ff)*(A.ff-B.ff) + 1ll*(A.ss-B.ss)*(A.ss-B.ss);
}

ll solve(int i, int j, bool q)
{
	if (i == h && j < g) return inf;
	if (i == h) return 0;
	if (dp[i][j][q] != -1) return dp[i][j][q];

	ll ans1 = inf, ans2 = inf;

	if (q == 0)
	{
		if (i < h) ans1 = dist(H[i], H[i+1]) + solve(i+1, j, 0);
		if (i <= h && j <= g) ans2 = dist(H[i], G[j+1]) + solve(i, j+1, 1);
	}
	else
	{
		if (j < g) ans1 = dist(G[j], G[j+1]) + solve(i, j+1, 1);
		if (i <= h && j <= g) ans2 = dist(G[j], H[i+1]) + solve(i+1, j, 0);
	}

	return dp[i][j][q] = min(ans1, ans2);
}

int main(void)
{
	FILE *fin = fopen("checklist.in", "r");
	FILE *fout = fopen("checklist.out", "w");

	fscanf(fin, "%d %d", &h, &g);

	for (int i = 1; i <= h; i++)
		fscanf(fin, "%d %d", &H[i].ff, &H[i].ss);

	for (int i = 1; i <= g; i++)
		fscanf(fin, "%d %d", &G[i].ff, &G[i].ss);

	memset(dp, -1, sizeof dp);

	fprintf(fout, "%lld\n", solve(1, 0, 0));
}
