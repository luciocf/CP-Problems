// Codeforces 650D - Zip-line
// Lúcio Cardoso

// Solution is the same as editorial, using the second approach (not the hashing one)

#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

typedef pair<int, int> pii;

const int maxn = 8e5+10;

int n, m;
int a[maxn];

int bit[maxn];

int pref[maxn], suf[maxn], freq[maxn];
int ans[maxn];

map<int, int> q_pref[maxn], q_suf[maxn];

vector<pii> query[maxn];

void upd(int x, int v)
{
	for (; x < maxn; x += (x&-x))
		bit[x] = max(bit[x], v);
}

int get(int x)
{
	int ans = 0;
	for (; x > 0; x -= (x&-x))
		ans = max(ans, bit[x]);
	return ans;
}

int main(void)
{
	scanf("%d %d", &n, &m);

	map<int, int> mp;
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);

		mp[a[i]] = 0;
	}

	for (int i = 1; i <= m; i++)
	{
		int pos, v;
		scanf("%d %d", &pos, &v);

		query[pos].push_back({v, i});

		mp[v] = 0;
	}

	int aux = 0;
	for (auto &x: mp)
		x.second = ++aux;

	for (int i = 1; i <= n; i++)
		a[i] = mp[a[i]];

	for (int i = 1; i <= n; i++)
		for (int j = 0; j < query[i].size(); j++)
			query[i][j].ff = mp[query[i][j].ff];

	int lis = 0;

	for (int i = 1; i <= n; i++)
	{
		for (auto v: query[i])
			q_pref[i][v.ff] = get(v.ff-1);

		pref[i] = get(a[i]-1)+1;
		upd(a[i], pref[i]);

		lis = max(lis, pref[i]);
	}

	memset(bit, 0, sizeof bit);

	for (int i = n; i >= 1; i--)
	{
		for (auto v: query[i])
			q_suf[i][v.ff] = get(maxn-v.ff-1);

		suf[i] = get(maxn-a[i]-1)+1;
		upd(maxn-a[i], suf[i]);
	}

	for (int i = 1; i <= n; i++)
		if (pref[i]+suf[i]-1 == lis)
			freq[pref[i]]++;

	for (int i = 1; i <= n; i++)
	{
		for (auto pp: query[i])
		{
			int v = pp.ff, ind = pp.ss;

			if (q_pref[i][v]+q_suf[i][v]+1 >= lis)
				ans[ind] = q_pref[i][v]+q_suf[i][v]+1;
			else
			{
				if (pref[i]+suf[i]-1 != lis) ans[ind] = lis;
				else if (pref[i]+suf[i]-1 == lis && freq[pref[i]] > 1) ans[ind] = lis;
				else ans[ind] = lis-1;
			}
		}
	}

	for (int i = 1; i <= m; i++)
		printf("%d\n", ans[i]);
}
