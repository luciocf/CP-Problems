// Codeforces 1167E - Range Deleting
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int maxn = 1e6+10;

int n, x;
int a[maxn];

int mn[maxn], mx[maxn];

bool ok1(int r)
{
	vector<int> v;

	for (int i = 1; i <= n; i++)
		if (a[i] > r)
			v.push_back(a[i]);

	for (int i = 1; i < (int)v.size(); i++)
		if (v[i-1] > v[i])
			return false;

	return true;
}

int busca1(void)
{
	int ini = 1, fim = x, ans = x;

	while (ini <= fim)
	{
		int mid = (ini+fim)>>1;

		if (ok1(mid)) ans = mid, fim = mid-1;
		else ini = mid+1;
	}

	return ans;
}

bool ok2(int l)
{
	vector<int> v;

	for (int i = 1; i <= n; i++)
		if (a[i] < l)
			v.push_back(a[i]);

	for (int i = 1; i < (int)v.size(); i++)
		if (v[i-1] > v[i])
			return false;

	return true;
}

int busca2(void)
{
	int ini = 1, fim = x, ans = 1;

	while (ini <= fim)
	{
		int mid = (ini+fim)>>1;

		if (ok2(mid)) ans = mid, ini = mid+1;
		else fim = mid-1;
	}

	return ans;
}

int main(void)
{
	scanf("%d %d", &n, &x);

	for (int i = 1; i <= x; i++)
		mn[i] = n+1, mx[i] = 0;

	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);

		mn[a[i]] = min(mn[a[i]], i);
		mx[a[i]] = max(mx[a[i]], i);
	}

	int ini_r = busca1();
	int fim_l = busca2();

	ll ans = 0;

	set<int> st_l, st_r;

	int r = ini_r;

	for (int i = ini_r+1; i <= x; i++)
		st_r.insert(mn[i]);

	for (int l = 1; l <= fim_l; l++)
	{
		while (r < l)
			st_r.erase(mn[++r]);

		while (r < x && st_l.size() && st_r.size() && *st_r.begin() < -*st_l.begin())
			st_r.erase(mn[++r]);

		ans += 1ll*(x-r+1);
		
		st_l.insert(-mx[l]);
	}

	printf("%lld\n", ans);
}
