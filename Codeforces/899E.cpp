// Codeforces 899E - Segments Removal
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

const int maxn = 2e5+10;

int n;
int a[maxn];

int pai[maxn], peso[maxn], mn[maxn], mx[maxn];

void init(void)
{
	for (int i = 1; i <= n; i++)
		pai[i] = i, peso[i] = 1, mn[i] = mx[i] = i;
}

int Find(int x)
{
	if (pai[x] == x) return x;
	return pai[x] = Find(pai[x]);
}

void Join(int x, int y)
{
	x = Find(x), y = Find(y);
	if (x == y) return;

	if (peso[x] < peso[y]) swap(x, y);

	pai[y] = x, peso[x] += peso[y];
	mn[x] = min(mn[x], mn[y]), mx[x] = max(mx[x], mx[y]);
}

int main(void)
{
	scanf("%d", &n);

	init();

	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);

		if (i > 1 && a[i] == a[i-1]) Join(i, i-1);
	}

	set<pii> st;
	set<int> on;

	for (int i = 1; i <= n; i++)
	{
		on.insert(i);

		int f = Find(i);

		st.insert({-peso[f], mn[f]});
	}

	int ans = 0;
	while (st.size())
	{
		++ans;

		int u = Find(st.begin()->second);
		st.erase(st.begin());

		for (auto it = on.find(mn[u]); it != on.end() && *it <= mx[u]; )
			it = on.erase(it);

		if (mn[u] == 1 || mx[u] == n) continue;

		auto it = on.upper_bound(mn[u]);
		if (it == on.begin()) continue;

		--it;
		int x = *it;

		it = on.upper_bound(mx[u]);
		if (it == on.end()) continue;

		int y = *it;

		if (a[x] != a[y]) continue;

		int fa = Find(x), fb = Find(y);

		st.erase({-peso[fa], mn[fa]});
		st.erase({-peso[fb], mn[fb]});

		Join(fa, fb);

		st.insert({-peso[Find(fa)], mn[Find(fa)]});
	}


	printf("%d\n", ans);
}
