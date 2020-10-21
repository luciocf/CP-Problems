// CSES 1640 - Sum of Two Values
// Lúcio Cardoso

#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

typedef pair<int, int> pii;

const int maxn = 2e5+10;

pii a[maxn];

int main(void)
{
	int n, x;
	scanf("%d %d", &n, &x);

	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i].ff);
		a[i].ss = i;
	}

	sort(a+1, a+n+1);

	int ptr = n;

	for (int i = 1; i <= n; i++)
	{
		while (ptr-1 > i && a[i].ff + a[ptr].ff > x)
			ptr--;

		if (ptr != i && a[i].ff + a[ptr].ff == x)
		{
			printf("%d %d\n", a[i].ss, a[ptr].ss);
			return 0;
		}
	}

	printf("IMPOSSIBLE\n");
}
