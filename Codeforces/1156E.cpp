// Codeforces 1156E - Special Segments of Permutation
// Lúcio Cardoso

// Solution is the same as in editorial

#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

typedef pair<int, int> pii;
typedef long long ll;

const int maxn = 2e5+10;

int n;
int a[maxn];
int pos[maxn];

int l[maxn], r[maxn];

void calc_l(void)
{
	stack<pii> stk;

	for (int i = 1; i <= n; i++)
	{
		while (stk.size() && stk.top().ff < a[i])
			stk.pop();

		if (stk.size()) l[i] = stk.top().ss+1;
		else l[i] = 1;

		stk.push({a[i], i});
	}
}

void calc_r(void)
{
	stack<pii> stk;

	for (int i = n; i >= 1; i--)
	{
		while (stk.size() && stk.top().ff < a[i])
			stk.pop();

		if (stk.size()) r[i] = stk.top().ss-1;
		else r[i] = n;

		stk.push({a[i], i});
	}
}

int main(void)
{
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);

		pos[a[i]] = i;
	}

	calc_l(); calc_r();

	ll ans = 0;

	for (int i = 1; i <= n; i++)
	{
		if (i-l[i] <= r[i]-i)
		{
			for (int j = l[i]; j < i; j++)
				if (pos[a[i] - a[j]] > i && pos[a[i] - a[j]] <= r[i])
					ans++;
		}
		else
		{
			for (int j = i+1; j <= r[i]; j++)
				if (pos[a[i] - a[j]] < i && pos[a[i] - a[j]] >= l[i])
					ans++;
		}
	}

	printf("%lld\n", ans);
}
