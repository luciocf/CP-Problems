// Codeforces 1388D - Captain Flint and Treasure
// Lúcio Cardoso

// Solution is the same as in editorial

#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

typedef pair<int, int> pii;

const int maxn = 2e5+10;

long long a[maxn];

int f[maxn];
int grau[maxn];

int main(void)
{
	int n;
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
		scanf("%lld", &a[i]);

	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &f[i]);

		if (f[i] != -1)
			grau[f[i]]++;
	}

	set<pii> st;

	for (int i = 1; i <= n; i++)
		st.insert({grau[i], i});

	vector<int> pos, neg;
	long long ans = 0;

	while (st.size())
	{
		int u = st.begin()->ss;
		st.erase(st.begin());

		if (f[u] != -1)
		{
			st.erase({grau[f[u]], f[u]});
			grau[f[u]]--;
			st.insert({grau[f[u]], f[u]});
		}

		ans += 1ll*a[u];

		if (a[u] >= 0)
		{
			if (f[u] != -1) a[f[u]] += a[u];
			pos.push_back(u);
		}
		else neg.push_back(u);
	}

	printf("%lld\n", ans);

	for (auto i: pos)
		printf("%d ", i);
	for (int i = neg.size()-1; i >= 0; i--)
		printf("%d ", neg[i]);
	printf("\n");
}
