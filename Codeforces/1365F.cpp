// Codeforces 1365F - Swaps Again
// Lúcio Cardoso

// Solution is the same as in editorial.

#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

const int maxn = 510;

int a[maxn], b[maxn];

int main(void)
{
	int tc;
	scanf("%d", &tc);

	while (tc--)
	{
		int n;
		scanf("%d", &n);

		for (int i = 1; i <= n; i++)
			scanf("%d", &a[i]);

		for (int i = 1; i <= n; i++)
			scanf("%d", &b[i]);

		vector<pii> st1, st2;

		for (int i = 1; i <= n; i++)
		{
			st1.push_back({a[i], a[n-i+1]});
			st2.push_back({b[i], b[n-i+1]});
		}

		sort(st1.begin(), st1.end()); sort(st2.begin(), st2.end());

		bool ok = 1;

		for (int i = 0; i < st1.size(); i++)
			if (st1[i] != st2[i])
				ok = 0;

		if (!ok) cout << "No\n";
		else cout << "yes\n";
	}
}
