// Codeforces 1251E2 - Voting (Hard Version)
// Lúcio Cardoso

// Solution is the same as in editorial

#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

typedef pair<int, int> pii;
typedef long long ll;

const int maxn = 2e5+10;

pii a[maxn];

int main(void)
{
	int tc;
	scanf("%d", &tc);

	while (tc--)
	{
		int n;
		scanf("%d", &n);

		for (int i = 1; i <= n; i++)
			scanf("%d %d", &a[i].ff, &a[i].ss);

		sort(a+1, a+n+1);

		ll ans = 0;
		int qtd = 0;
		multiset<int> st;

		for (int i = n; i >= 1; i--)
		{
			st.insert(a[i].ss);

			while (i+qtd-1 < a[i].ff)
			{
				ans += 1ll*(*st.begin());
				++qtd;

				st.erase(st.begin());
			}
		}

		printf("%lld\n", ans);
	}
}
