// Codeforces 713C - Sonya and Problem Wihtout a Legend
// Lúcio Figueiredo

#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

typedef long long ll;
typedef pair<ll, int> pii;

const int maxn = 3e3+10;
const ll inf = 1e18+10;

int n;
int a[maxn], b[maxn];

ll cost[maxn][maxn];
int med[maxn][maxn];

pii dp[maxn];

ll soma1, soma2;
multiset<int> st1, st2;

void add(int x)
{
	int tot = st1.size() + st2.size();

	if (tot%2)
	{
		if (x >= *st2.begin())
		{
			soma1 += 1ll*(*st2.begin()); st1.insert(*st2.begin());
			soma2 -= 1ll*(*st2.begin()); st2.erase(st2.begin());
			soma2 += 1ll*x; st2.insert(x);
		}
		else
		{
			soma1 += 1ll*x; st1.insert(x);
		}
	}
	else
	{
		if (st2.size() == 0 || x >= *st1.rbegin())
		{
			soma2 += 1ll*x; st2.insert(x);
		}
		else
		{
			soma2 += 1ll*(*st1.rbegin()); st2.insert(*st1.rbegin());
			soma1 -= 1ll*(*st1.rbegin()); st1.erase(st1.find(*st1.rbegin()));
			soma1 += 1ll*x; st1.insert(x);
		}
	}
}

ll get(void)
{
	int m = *st2.begin();

	return (soma2 - soma1 - (st1.size() != st2.size() ? 1ll*m : 0));
}

void calc(int l)
{
	st1.clear(); st2.clear();
	soma1 = soma2 = 0;

	for (int r = l; r <= n; r++)
	{
		add(b[r]);

		cost[l][r] = get();
		med[l][r] = *st2.begin();
	}
}

int main(void)
{
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
		b[i] = a[i]-i;
	}

	for (int i = 1; i <= n; i++)
		calc(i);

	for (int r = 1; r <= n; r++)
	{
		dp[r] = {inf, inf};

		for (int l = r-1; l >= 0; l--)
		{
			if (l > 0 && med[l+1][r] + (l+1) <= dp[l].ss) continue;

			if (make_pair(cost[l+1][r] + dp[l].ff, med[l+1][r] + r) < dp[r])
				dp[r] = {cost[l+1][r] + dp[l].ff, med[l+1][r] + r};
		}
	}

	printf("%lld\n", dp[n].ff);
}
