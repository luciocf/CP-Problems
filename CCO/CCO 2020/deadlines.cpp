// CCO 2020 - Exercise Deadlines
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 2e5+10;

struct FenwickTree
{
	int bit[maxn];

	void upd(int x, int v)
	{
		for (; x < maxn; x += (x&-x))
			bit[x] += v;
	}

	int soma(int x)
	{
		int ans = 0;
		for (; x > 0; x -= (x&-x))
			ans += bit[x];
		return ans;
	}

	int get(int l, int r)
	{
		return soma(r)-soma(l-1);
	}
} BIT;

int a[maxn];

vector<int> lista[maxn];

int main(void)
{
	int n;
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
	{
		int x;
		scanf("%d", &x);

		lista[x].push_back(i);
	}

	set<int> st;

	for (int i = n; i >= 1; i--)
	{
		for (auto p: lista[i])
			st.insert(p);

		if (st.size() == 0)
		{
			printf("-1\n");
			return 0;
		}

		a[i] = *st.rbegin();
		st.erase(a[i]);
	}

	long long ans = 0;
	for (int i = 1; i <= n; i++)
	{
		ans += 1ll*(BIT.get(a[i], n));
		BIT.upd(a[i], 1);
	}

	printf("%lld\n", ans);
}
