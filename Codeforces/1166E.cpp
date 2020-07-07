// Codeforces 1166E - The LCMs Must be Large
// Lúcio Cardoso

// Solution is the same as in editorial

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e4+10;

bitset<maxn> bs[51];

int main(void)
{
	int n, m;
	scanf("%d %d", &n, &m);

	for (int i = 1; i <= n; i++)
	{
		int s;
		scanf("%d", &s);

		for (int j = 1; j <= s; j++)
		{
			int x;
			scanf("%d", &x);

			bs[i][x] = 1;
		}
	}

	bool ok = true;

	for (int i = 1; i <= n; i++)
		for (int j = i+1; j <= n; j++)
			if ((bs[i]&bs[j]).count() == 0)
				ok = false;

	if (ok) printf("possible\n");
	else printf("impossible\n");
}
