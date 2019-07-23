// COI 2019 - Ljetopica
// Lúcio Cardoso

// Solution: https://codeforces.com/blog/entry/66506?#comment-505659

#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

const int maxn = 1e3+10;
const int mod = 1e9+7;

typedef long long ll;
typedef pair<ll, ll> pii;

int n, k;
int pot[maxn];

char pos[maxn], A[maxn];

bool mark[maxn][maxn][2][2];

pii dp[maxn][maxn][2][2];

void change(void)
{
	int last = 0;
	for (int i = n-1; i >= 0; i--)
	{
		if (A[i] == '1')
		{
			last = i;
			break;
		}
	}

	A[last] = '0';
	for (int i = last+1; i < n; i++)
		A[i] = '1';
}

pii solve(int depth, int r, int q, int flag)
{
	if (mark[depth][r][q][flag]) return dp[depth][r][q][flag];
	if (depth == n && r != 0) return {0, 0};
	if (depth == n) return {0, 1};

	mark[depth][r][q][flag] = true;

	if (!r) 
	{
		char c = pos[depth];

		if (!q && c == 'L') c = 'R';
		else if (!q && c == 'R') c = 'L';

		if (c == 'L')
			return dp[depth][r][q][flag] = solve(depth+1, 0, q, (flag || (A[depth]=='1')));

		if (A[depth] == '1' || flag)
		{
			pii ans = solve(depth+1, 0, q, flag);

			return dp[depth][r][q][flag] = {(ans.ff + (1ll*pot[n-depth-1]*ans.ss)%mod)%mod, ans.ss};
		}

		return dp[depth][r][q][flag] = {0, 0};
	}

	char c = pos[depth];
	if (!q && c == 'L') c = 'R';
	else if (!q && c == 'R') c = 'L';

	if (c == 'L')
	{
		pii ans1 = solve(depth+1, r, q, (flag || (A[depth]=='1')));
		pii ans2 = solve(depth+1, r-1, !q, (flag || (A[depth]=='1')));

		return dp[depth][r][q][flag] = {(ans1.ff+ans2.ff)%mod, (ans1.ss+ans2.ss)%mod};
	}
	else
	{
		pii ans = {0, 0};

		if (A[depth] == '1' || flag)
		{
			pii sub1 = solve(depth+1, r, q, flag);
			pii sub2 = solve(depth+1, r-1, !q, flag);

			ans = {(sub1.ff+sub2.ff)%mod, (sub1.ss+sub2.ss)%mod};

			ans.ff = (ans.ff + ((1ll*pot[n-depth-1]*ans.ss)%mod))%mod;
		}

		return dp[depth][r][q][flag] = ans;
	}
}

int main(void)
{
	scanf("%d %d", &n, &k);

	pot[0] = 1;
	for (int i = 1; i <= n; i++)
		pot[i] = (2*pot[i-1])%mod;

	for (int i = 1; i < n; i++)
		scanf(" %c", &pos[i]);

	for (int i = 0; i < n; i++)
		scanf(" %c", &A[i]);

	change();

	int ans1 = 0;

	if (A[0] != '0')
	{
		pii sub1 = solve(1, k, 1, 0);
		memset(mark, 0, sizeof mark);
		pii sub2 = solve(1, k, 0, 0);

		ans1 = ((sub1.ff + sub2.ff)%mod + (1ll*pot[n-1]*sub1.ss + 1ll*pot[n-1]*sub2.ss)%mod)%mod;
	}

	memset(mark, 0, sizeof mark);

	for (int i = 0; i < n; i++)
		scanf(" %c", &A[i]);

	pii sub1 = solve(1, k, 1, 0);
	memset(mark, 0, sizeof mark);
	pii sub2 = solve(1, k, 0, 0);

	int ans2 = ((sub1.ff + sub2.ff)%mod + (1ll*pot[n-1]*sub1.ss + 1ll*pot[n-1]*sub2.ss)%mod)%mod;

	printf("%d\n", (ans2+mod-ans1)%mod);
}
