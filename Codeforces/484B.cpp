// Codeforces 484B - Maximum Value
// Lúcio Cardoso

// Solution is the same as the one in editorial

#include <bits/stdc++.h>

using namespace std;

const int maxn = 2e5+10;
const int maxv = 2e6+10;

vector<int> a;

int main(void)
{
	int n;
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
	{
		int x;
		scanf("%d", &x);

		a.push_back(x);
	}

	sort(a.begin(), a.end());
	a.erase(unique(a.begin(), a.end()), a.end());

	int ans = 0;

	for (auto k: a)
	{
		for (int v = 2*k; v < maxv; v += k)
		{
			auto it = lower_bound(a.begin(), a.end(), v);
			if (it == a.begin()) continue;

			--it;

			int x = *it;

			if (x >= v-k)
				ans = max(ans, x%k);
		}
	}

	printf("%d\n", ans);
}
