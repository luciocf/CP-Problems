// IOI 2009 - Hiring
// Lúcio Cardoso

// Solution is similar to: https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/Olympiad/IOI/official/2009/hiring.cpp

#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

const int maxn = 5e5+10;

int n;
ll w;

struct S
{
	int s, q, ind;
} a[maxn];

bool comp(S a, S b)
{
	return a.s*b.q < b.s*a.q;
}

int main(void)
{
	scanf("%d %lld", &n, &w);

	for (int i = 1; i <= n; i++)
	{
		scanf("%d %d", &a[i].s, &a[i].q);
		a[i].ind = i;
	}

	sort(a+1, a+n+1, comp);

	int ans = 0, ans_ind = 0;

	priority_queue<pii> fila;

	ll soma = 0;
	double ans_soma = 0;

	for (int i = 1; i <= n; i++)
	{
		if (1ll*a[i].s > w) continue;

		fila.push({a[i].q, i});
		soma += 1ll*a[i].q;

		while (1ll*a[i].s*soma > 1ll*w*a[i].q)
		{
			soma -= 1ll*fila.top().ff;
			fila.pop();
		}

		if (fila.size() > ans || (fila.size() == ans && (1.00*a[i].s/a[i].q*soma) < ans_soma))
			ans = fila.size(), ans_soma = (1.00*a[i].s/a[i].q*soma), ans_ind = i;
	}

	printf("%d\n", ans);

	while (fila.size()) fila.pop();

	soma = 0;

	for (int i = 1; i <= n; i++)
	{
		if (1ll*a[i].s > w) continue;

		fila.push({a[i].q, i});
		soma += 1ll*a[i].q;

		while (1ll*a[i].s*soma > 1ll*w*a[i].q)
		{
			soma -= 1ll*fila.top().ff;
			fila.pop();
		}

		if (i == ans_ind)
		{
			while (fila.size())
			{
				printf("%d\n", a[fila.top().ss].ind);
				fila.pop();
			}

			return 0;
		}
	}
}
