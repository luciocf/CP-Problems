// Codeforces 1354D - Multiset
// Lucio Figueiredo

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <deque>
#include <cstring>
#include <set>
#include <map>
#include <cmath>

using namespace std;

#define ff first
#define ss second
#define mkp make_pair
#define pb push_back
#define sz(x) (int)(x).size()
#define lb lower_bound
#define ub upper_bound
#define all(x) x.begin(), x.end()
#define ins insert

typedef pair<int, int> pii;
typedef long long ll;

const int maxn = 1e6+2;

int n, q;
int a[maxn];
int query[maxn];

bool ok(int x)
{
	int qtd = 0;
	for (int i = 1; i <= n; i++)
		if (a[i] <= x)
			qtd++;

	for (int i = 1; i <= q; i++)
	{
		if (query[i] > 0)
		{
			if (query[i] <= x) qtd++;
		}
		else if (abs(query[i]) <= qtd) qtd--;
	}

	return qtd > 0;
}

int main(void)
{
	scanf("%d %d", &n, &q);

	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);

	for (int i = 1; i <= q; i++)
		scanf("%d", &query[i]);

	int ini = 1, fim = n, ans = 0;
	while (ini <= fim)
	{
		int mid = (ini+fim)>>1;

		if (ok(mid)) ans = mid, fim = mid-1;
		else ini = mid+1;
	}

	printf("%d\n", ans);
}
