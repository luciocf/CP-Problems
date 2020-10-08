// Codeforces 915E - Physical Education Lessons
// Lúcio Cardoso

// Solution is the same as in editorial

#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

typedef pair<int, int> pii;

const int maxn = 3e5+10;

int n, q;
int ans;

set<pii> st[2];

void upd(int l, int r, int q, int t)
{
	int mult = (q == 0 ? -1 : 1);
	if (q == t) mult = 0;

	auto it = st[q].lower_bound({l, 0});

	if (it != st[q].begin())
	{
		--it;

		if (it->ss >= l && it->ss <= r)
		{
			ans += mult*(it->ss-l+1);

			st[q].insert({it->ff, l-1});
			st[q].erase(it);
		}
		else if (it->ss >= l)
		{
			ans += mult*(r-l+1);

			st[q].insert({it->ff, l-1}); st[q].insert({r+1, it->ss});
			st[q].erase(it);
		}
	}

	for (auto it = st[q].lower_bound({l, 0}); it != st[q].end() && it->ff <= r; )
	{
		if (it->ss > r)
		{
			ans += mult*(r-it->ff+1);

			st[q].insert({r+1, it->ss});
			st[q].erase(it);
			break;
		}

		ans += mult*(it->ss-it->ff+1);

		it = st[q].erase(it);
	}
}

int main(void)
{
	scanf("%d %d", &n, &q);

	ans = n;
	st[0].insert({1, n});

	while (q--)
	{
		int l, r, t;
		scanf("%d %d %d", &l, &r, &t);

		upd(l, r, 0, t%2); upd(l, r, 1, t%2);
		st[t%2].insert({l, r});

		printf("%d\n", ans);
	}

}
