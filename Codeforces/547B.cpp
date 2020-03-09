// Codeforces 547B - Mike and Feet
// Lúcio Cardoso

#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

typedef pair<int, int> pii;

const int maxn = 2e5+10;

int n;
int a[maxn];

int l[maxn], r[maxn];

int suf[maxn];

int main(void)
{
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);

	stack<pii> stk;

	for (int i = 1; i <= n; i++)
	{
		while (stk.size() && stk.top().ff >= a[i])
			stk.pop();

		if (stk.size()) l[i] = stk.top().ss+1;
		else l[i] = 1;

		stk.push({a[i], i});
	}

	while (stk.size()) stk.pop();

	for (int i = n; i >= 1; i--)
	{
		while (stk.size() && stk.top().ff >= a[i])
			stk.pop();

		if (stk.size()) r[i] = stk.top().ss-1;
		else r[i] = n;

		stk.push({a[i], i});
	}

	for (int i = 1; i <= n; i++)
		suf[r[i]-l[i]+1] = max(suf[r[i]-l[i]+1], a[i]);

	for (int i = n; i >= 1; i--)
		suf[i] = max(suf[i], suf[i+1]);

	for (int i = 1; i <= n; i++)
		printf("%d ", suf[i]);
	printf("\n");
}
