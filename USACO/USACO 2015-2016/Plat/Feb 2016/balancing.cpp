// USACO 2015/2016 - Load Balancing
// Lúcio Cardoso

#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

typedef pair<int, int> pii;

const int maxn = 1e5+10;
const int maxv = 1e6+10;

int n;
pii p[maxn];

int bit[2][maxv];

void upd(int x, int k, int v)
{
	for (; x < maxv; x += (x&-x))
		bit[k][x] += v; 
}

int soma(int x, int k)
{
	int ans = 0;

	for (; x > 0; x -= (x&-x))
		ans += bit[k][x];

	return ans;
}

int busca1(int L, int R)
{
	int ini = 0, fim = 500001, ans = n;

	while (ini <= fim)
	{
		int mid = (ini+fim)>>1;

		int q1 = soma(2*mid, 0), q2 = L-q1;
		int q3 = soma(2*mid, 1), q4 = R-q3;

		if (max(q1, q3) < max(q2, q4)) ini = mid+1;
		else ans = max(q1, q3), fim = mid-1;
	}

	return ans;
}

int busca2(int L, int R)
{
	int ini = 0, fim = 500001, ans = n;

	while (ini <= fim)
	{
		int mid = (ini+fim)>>1;

		int q1 = soma(2*mid, 0), q2 = L-q1;
		int q3 = soma(2*mid, 1), q4 = R-q3;

		if (max(q2, q4) < max(q1, q3)) fim = mid-1;
		else ans = max(q2, q4), ini = mid+1;
	}

	return ans;
}

int main(void)
{
	freopen("balancing.in", "r", stdin);
	freopen("balancing.out", "w", stdout);

	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
		scanf("%d %d", &p[i].ff, &p[i].ss);

	sort(p+1, p+n+1);

	for (int i = 1; i <= n; i++)
		upd(p[i].ss, 1, 1);

	int L = 0, R = n;
	int ans = n;

	for (int i = 1; i <= n; i++)
	{
		int j = i;
		for (; p[j].ff == p[i].ff; j++)
		{
			upd(p[j].ss, 0, 1);
			upd(p[j].ss, 1, -1);

			L++;
			R--;
		}

		ans = min({ans, busca1(L, R), busca2(L, R)});
		i = j-1;
	}

	printf("%d\n", ans);
}
