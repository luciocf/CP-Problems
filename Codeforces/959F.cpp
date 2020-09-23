// Codeforces 959F - Mahmoud and Ehab and yet another xor task
// Lúcio Cardoso

// Solution is the last one described in editorial.

#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

typedef pair<int, int> pii;

const int maxn = 2e6+10;
const int mod = 1e9+7;

int a[maxn];
int mn[maxn];
int qtd[maxn];

int val[25];

vector<pii> basis;

void add(int mask, int pos)
{
	for (int i = 0; i <= 20; i++)
	{
		if (!(mask&(1<<i))) continue;

		if (!val[i])
		{
			val[i] = mask;
			basis.push_back({mask, pos});
			break;
		}

		mask ^= val[i];
	}
}

int main(void)
{
	int n, q;
	scanf("%d %d", &n, &q);

	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
		add(a[i], i);
	}

	int sz = basis.size();

	memset(mn, -1, sizeof mn);

	for (int mask = 0; mask < (1<<sz); mask++)
	{
		int mx = 0, v = 0;

		for (int i = 0; i < sz; i++)
			if (mask&(1<<i))
				v ^= basis[i].ff, mx = max(mx, basis[i].ss);

		mn[v] = mx;
	}

	for (int i = 1; i <= n; i++)
	{
		if (a[i] == 0)
		{
			qtd[i] = (2*qtd[i-1]+1)%mod;
			continue;
		}

		if (mn[a[i]] < i) qtd[i] = (2*qtd[i-1]+1)%mod;
		else qtd[i] = qtd[i-1];
	}

	while (q--)
	{
		int l, x;
		scanf("%d %d", &l, &x);

		if (mn[x] > l || mn[x] == -1) printf("0\n");
		else printf("%d\n", (qtd[l] + 1)%mod);
	}
}
