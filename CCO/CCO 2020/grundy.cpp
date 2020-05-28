// CCO 2020 - A Game with Grundy
// Lúcio Cardoso

#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

typedef pair<int, int> pii;

const int maxn = 1e5+10;

int ans[maxn];

int main(void)
{
	int n, l, r, y;
	scanf("%d %d %d %d", &n, &l, &r, &y);

	multiset<pii> st;

	for (int i = 1; i <= n; i++)
	{
		long long x, v, h;
		scanf("%lld %lld %lld", &x, &v, &h);

		double a, b;

		if ((y*h)%v == 0)
		{
			b = (y*h)/v + x;
			a = (y*h)/(-v) + x + 1;
		}
		else
		{
			b = ceil((1.00*y*h)/(1.00*v) + 1.00*x);
			a = ceil((1.00*y*h)/(-1.00*v) + 1.00*x);
		}

		if (b <= l) continue;
		if (a > r) continue;

		if (a < l) a = l;
		if (b > r) b = r+1;

		if (a < b)
		{
			st.insert({(int)a, 0});
			st.insert({(int)b, 1});
		}
	}

	if (st.size() == 0)
	{
		for (int i = 0; i <= n; i++)
			printf("%d\n", r-l+1);
		return 0;
	}

	int ant = l, open = 0;

	for (auto it = st.begin(); it != st.end(); )
	{
		int x = it->ff, tipo = it->ss;

		ans[open] += (x-ant);

		if (tipo == 0) ++open;
		else --open;

		ant = x;

		while (next(it) != st.end() && next(it)->ff == x)
		{
			if (next(it)->ss == 0) ++open;
			else --open;

			it++;
		}

		it++;
	}

	ans[0] += max(0, (r-ant+1));

	printf("%d\n", ans[0]);
	for (int i = 1; i <= n; i++)
	{
		ans[i] += ans[i-1];
		printf("%d\n", ans[i]);
	}
}
