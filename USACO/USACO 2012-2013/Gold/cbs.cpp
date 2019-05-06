// USACO Gold 2012-2013 - Concurrently Balanced Strings
// Lúcio Cardoso

// Solution is the same as this one: http://usaco.org/current/data/sol_cbs.html

#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

const int maxn = 5e4+10;
const int maxk = 12;
const int add = 5e4;

typedef long long ll;
typedef pair<int, int> pii;

int a[maxk][maxn];
int pref[maxk][maxn];

stack<pii> stk[maxk];

int main(void)
{
	FILE *fin = fopen("cbs.in", "r");
	FILE *fout = fopen("cbs.out", "w");

	int k, n;
	fscanf(fin, "%d %d", &k, &n);

	for (int i = 1; i <= k; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			char c;
			fscanf(fin, " %c", &c);

			if (c == '(') pref[i][j] = pref[i][j-1]+1;
			else pref[i][j] = pref[i][j-1]-1;
		}
	}

	ll ans = 0;
	map<vector<int>, pii> mp;

	for (int j = 1; j <= n; j++)
	{
		int left = 1;

		for (int i = 1; i <= k; i++)
		{
			while (stk[i].size() > 0 && stk[i].top().ff >= pref[i][j])
				stk[i].pop();

			if (stk[i].size() > 0)
				left = max(left, stk[i].top().second+1);

			stk[i].push({pref[i][j], j});
		}

		vector<int> aux;
		for (int i = 1; i <= k; i++)
			aux.push_back(pref[i][j]);

		if (mp[aux].ff >= left)
		{	
			ans += (1ll*mp[aux].ss);
			mp[aux].ss++;
		}
		else mp[aux] = {left, 1};
	}

	fprintf(fout, "%lld\n", ans);
}
