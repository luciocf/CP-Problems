// Infoarena - Perioada
// Lúcio Cardoso

// Solution:

// Notice that, if the string s can be a period of a larger string S, then |s| | |S|. Thus, we only
// need to try O(sqrt(n)) string for each query.

// Now, the problem becomes checking if a string s is a period of a larger string S. Let's use hashing.
// Let hash(s) = X. If s is a period of S, then S = x + 31^|s|*x + 31^(2*|s|)*x + ... + 31^(|S|/|s| - 1)*x
// (31 is the prime used for hashing). Thus, if we precalculate the value of geometric series 31^0 + 31^k + 31^(2*k) + ...
// for every k, we can this subproblem in O(1). It's easy to calculate these geometric series in O(n log n).

// Final complexity is O(m*sqrt(n))

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5+10;
const int mod = 1e9+7;

int pot[maxn];
int inv[maxn];
vector<int> soma[maxn];

int h[maxn];

int Pot(int a, int b)
{
	if (!b) return 1;

	int t = Pot(a, b/2);

	if (b&1) return (1ll*a*((1ll*t*t)%mod))%mod;
	return (1ll*t*t)%mod;
}

int ok(int l, int r, int d)
{
	int n = (r-l+1);

	int hsh = (1ll*((h[r]-h[l-1]+mod)%mod)*inv[l-1])%mod; 

	int x = (1ll*((h[l+d-1]-h[l-1]+mod)%mod)*inv[l-1])%mod;

	int S = (1ll*x*soma[d][n/d-1])%mod;

	return (S == hsh);
}

int main(void)
{
	freopen("perioada.in", "r", stdin); freopen("perioada.out", "w", stdout);

	ios::sync_with_stdio(false); cin.tie(0);

	int n;
	string s;
	cin >> n >> s;

	pot[0] = 1;
	inv[0] = 1;

	for (int i = 1; i <= n; i++)
	{
		pot[i] = (31ll*pot[i-1])%mod;

		inv[i] = Pot(pot[i], mod-2);

		int c = (int)(s[i-1]-'a'+1);

		h[i] = (1ll*h[i-1] + 1ll*pot[i-1]*c)%mod;
	}

	for (int l = 1; l <= n; l++)
	{
		soma[l].push_back(1);

		for (int i = l; i <= n; i += l)
			soma[l].push_back((soma[l].back() + pot[i])%mod);
	}

	int q;
	cin >> q;

	while (q--)
	{
		int l, r;
		cin >> l >> r;

		int k = (r-l+1);
		int ans = 0;

		for (int d = 1; d*d <= k; d++)
		{
			if (k%d) continue;

			if (d != k) ans += ok(l, r, d);
			if (d != k/d && k/d != k) ans += ok(l, r, k/d);
		}

		printf("%d\n", ans);
	}
}
