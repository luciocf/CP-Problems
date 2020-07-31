// Codeforces 1105E - Helping Hiasat
// Lúcio Cardoso

#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

typedef pair<int, int> pii;

const int maxn = 1e5+10;

int n, m;

pii qry[maxn];

bool bad[70][70];

bool ok[2][1<<21];
int dp[1<<21];

void get0(void)
{
	ok[0][0] = 1;

	for (int mask = 1; mask < (1<<min(20, m)); mask++)
	{
		int b;
		for (int i = 0; i < min(20, m); i++)
			if (mask&(1<<i))
				b = i;

		ok[0][mask] = ok[0][mask^(1<<b)];

		for (int i = b-1; i >= 0; i--)
			if (mask&(1<<i))
				ok[0][mask] &= (!bad[b][i]);
	}
}

void get1(void)
{
	ok[1][0] = 1;

	for (int mask = 1; mask < (1<<(m-20)); mask++)
	{
		int b;
		for (int i = 0; i < 20; i++)
			if (mask&(1<<i))
				b = i;

		ok[1][mask] = ok[1][mask^(1<<b)];

		for (int i = b-1; i >= 0; i--)
			if (mask&(1<<i))
				ok[1][mask] &= (!bad[b+20][i+20]);
	}

	for (int mask = 1; mask < (1<<(m-20)); mask++)
	{
		if (ok[1][mask]) dp[mask] = __builtin_popcount(mask);

		for (int i = 0; i < 20; i++)
			if (mask&(1<<i))
				dp[mask] = max(dp[mask], dp[mask^(1<<i)]);
	}
}

int main(void)
{
	ios_base::sync_with_stdio(false); cin.tie(0);

	cin >> n >> m;

	map<string, int> mp;
	int aux = -1;

	for (int i = 1; i <= n; i++)
	{
		int op;
		cin >> op;

		if (op == 2)
		{
			string s;
			cin >> s;

			if (mp.find(s) == mp.end())
				mp[s] = ++aux;

			qry[i] = {2, mp[s]};
		}
		else qry[i] = {1, 0};
	}

	for (int i = 1; i <= n; i++)
	{
		int j;
		for (j = i; j <= n && qry[j].ff == 1; j++)
			;

		if (j > n) break;

		vector<int> V;
		for (; j <= n && qry[j].ff == 2; j++)
			V.push_back(qry[j].ss);

		sort(V.begin(), V.end());
		V.erase(unique(V.begin(), V.end() ), V.end() );

		for (int a = 0; a < V.size(); a++)
			for (int b = a+1; b < V.size(); b++)
				bad[V[a]][V[b]] = bad[V[b]][V[a]] = 1;

		i = j;
	}

	get0();
	if (m > 20) get1();
 
	int ans = 0;

	for (int mask = 0; mask < (1<<min(m, 20)); mask++)
	{
		if (!ok[0][mask]) continue;

		int mask2 = 0;

		for (int i = 20; i < m; i++)
		{
			bool certo = 1;

			for (int j = 0; j < 20; j++)
				if (mask&(1<<j) && bad[i][j])
					certo = 0;

			if (certo) mask2 += (1<<(i-20));
		}

		ans = max(ans, __builtin_popcount(mask) + dp[mask2]);
	}

	cout << ans << "\n";
}
