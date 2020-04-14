// Codeforces 1257E - The Contest
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 6e5+10;

vector<int> a, c;

int A(int l, int r)
{
	if (l > r) return 0;
	if (a[0] > r) return 0;
	if (a.back() < l) return 0;

	auto it = upper_bound(a.begin(), a.end(), r);
	auto it2 = lower_bound(a.begin(), a.end(), l);

	return (int)(it-it2);
}

int C(int l, int r)
{
	if (l > r) return 0;
	if (c[0] > r) return 0;
	if (c.back() < l) return 0;

	auto it = upper_bound(c.begin(), c.end(), r);
	auto it2 = lower_bound(c.begin(), c.end(), l);

	return (int)(it-it2);
}

int main(void)
{
	int k1, k2, k3;
	scanf("%d %d %d", &k1, &k2, &k3);

	int n = k1+k2+k3;

	for (int i = 1; i <= k1; i++)
	{
		int x;
		scanf("%d", &x);

		a.push_back(x);
	}

	for (int i = 1; i <= k2; i++)
	{
		int x;
		scanf("%d", &x);
	}

	for (int i = 1; i <= k3; i++)
	{
		int x;
		scanf("%d", &x);

		c.push_back(x);
	}

	sort(a.begin(), a.end()); sort(c.begin(), c.end());

	int ans = n+1;

	multiset<int> st;

	for (int r = 1; r <= n+1; r++)
		st.insert(C(1, r-1) - C(r, n) - A(r, n) - r);

	for (int l = 0; l <= n; l++)
	{
		ans = min(ans, n + l + 1 - A(1, l) + A(l+1, n) + *st.begin() - C(1, l));

		st.erase(st.find(C(1, l) - C(l+1, n) - A(l+1, n) - (l+1)));
	}
	printf("%d\n", ans);
}
