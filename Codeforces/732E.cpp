// Codeforces 732E - Sockets
// Lúcio Cardoso

// Solution is the same as in editorial

#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

typedef pair<int, int> pii;

const int maxn = 2e5+10;

pii a[maxn], b[maxn];

int ans1[maxn], ans2[maxn];

bool mark1[maxn], mark2[maxn];

int main(void)
{
	int n, m;
	scanf("%d %d", &n, &m);

	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i].ff);
		a[i].ss = i;
	}

	for (int i = 1; i <= m; i++)
	{
		scanf("%d", &b[i].ff);
		b[i].ss = i;
	}

	sort(a+1, a+n+1, greater<pii>()); sort(b+1, b+m+1, greater<pii>());

	int ans = 0, cost = 0;

	for (int vez = 0; vez <= 40; vez++)
	{
		int ptr1 = 1, ptr2 = 1;

		while (ptr1 <= n && ptr2 <= m)
		{
			while (ptr1 <= n && mark1[ptr1]) ptr1++;

			if (ptr1 == n+1) break;

			while (ptr2 < m && b[ptr2].ff > a[ptr1].ff && b[ptr2+1].ff >= a[ptr1].ff) ptr2++;

			while (ptr2 <= m && mark2[ptr2]) ptr2++;

			if (ptr2 == m+1) break;

			if (b[ptr2].ff == a[ptr1].ff)
			{
				mark1[ptr1] = mark2[ptr2] = 1;

				ans++;
				cost += vez;

				ans1[a[ptr1].ss] = b[ptr2].ss, ans2[b[ptr2].ss] = vez;
			}

			ptr1++;
		}

		for (int i = 1; i <= m; i++)
			b[i].ff = (b[i].ff+1)/2;
	}

	printf("%d %d\n", ans, cost);

	for (int i = 1; i <= m; i++)
		printf("%d ", ans2[i]);
	printf("\n");
	for (int i = 1; i <= n; i++)
		printf("%d ", ans1[i]);
	printf("\n");
}
