// COCI 2010/2011 - Diferencija
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

const int maxn = 3e5+10;

int n;
int a[maxn];

int l1[maxn], r1[maxn];
int l2[maxn], r2[maxn];

void calc_1(void)
{
	stack<pii> stk;

	for (int i = 1; i <= n; i++)
	{
		while (stk.size() && stk.top().first <= a[i])
			stk.pop();

		if (stk.size()) l1[i] = stk.top().second+1;
		else l1[i] = 1;

		stk.push({a[i], i});
	}

	while (stk.size()) stk.pop();

	for (int i = n; i >= 1; i--)
	{
		while (stk.size() && stk.top().first < a[i])
			stk.pop();

		if (stk.size()) r1[i] = stk.top().second-1;
		else r1[i] = n;

		stk.push({a[i], i});
	}
}

void calc_2(void)
{
	stack<pii> stk;

	for (int i = 1; i <= n; i++)
	{
		while (stk.size() && stk.top().first >= a[i])
			stk.pop();

		if (stk.size()) l2[i] = stk.top().second+1;
		else l2[i] = 1;

		stk.push({a[i], i});
	}

	while (stk.size()) stk.pop();

	for (int i = n; i >= 1; i--)
	{
		while (stk.size() && stk.top().first > a[i])
			stk.pop();

		if (stk.size()) r2[i] = stk.top().second-1;
		else r2[i] = n;

		stk.push({a[i], i});
	}
}

int main(void)
{
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);

	calc_1(); calc_2();

	long long ans = 0;

	for (int i = 1; i <= n; i++)
	{
		ans += 1ll*a[i]*(r1[i]-i+1)*(i-l1[i]+1);
		ans -= 1ll*a[i]*(r2[i]-i+1)*(i-l2[i]+1);
	}

	printf("%lld\n", ans);
}
