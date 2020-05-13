// MCO 2017 - Large City
// Lúcio Cardoso

// Solution: https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/Olympiad/MCO/official/2017/editorial.pdf

#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

typedef pair<int, int> pii;

const int maxn = 3e5+10;

vector<pii> mark;
vector<pii> ok;

int main(void)
{
	int n, m;
	scanf("%d %d", &n, &m);

	for (int i = 1; i <= m; i++)
	{
		int x, y;
		scanf("%d %d", &x, &y);

		swap(x, y);

		mark.push_back({x, y});
	}

	sort(mark.begin(), mark.end());

	ok.push_back({1, 1});

	long long ans = 0;
	int prev = 0;

	for (int i = 0; i < m; i++)
	{
		int a = mark[i].ff;

		if (prev < a-1)
		{
			if (ok.size() != 0)
			{
				ans += 1ll*(a-prev-1)*(n-ok[0].ss+1);

				ok.clear();
				ok.push_back({n, ok[0].ss});
			}
		}
		prev = a;

		vector<pii> aux;

		int j;
		for (j = i; j < m && mark[j].ff == mark[i].ff; j++)
		{
			int b = mark[j].ss;
			if (b == 1 || (j > i && mark[j-1].ss == b-1)) continue;

			int ini = (j == i ? 1 : mark[j-1].ss+1);
			auto it = lower_bound(ok.begin(), ok.end(), make_pair(ini, 0));

			if (it == ok.end()) continue;

			int pos = it->second;
			pos = max(pos, ini);

			if (pos < b)
			{
				ans += 1ll*(b-pos);
				aux.push_back({b-1, pos});
			}
		}
		j--;

		int ini = mark[j].ss+1;
		auto it = lower_bound(ok.begin(), ok.end(), make_pair(ini, 0));

		if (it != ok.end())
		{
			int pos = it->second;

			pos = max(pos, ini);

			ans += 1ll*(n-pos+1);
			aux.push_back({n, pos});
		}

		swap(aux, ok);
		aux.clear();

		i = j;
	}

	if (prev < n && ok.size() != 0)
		ans += 1ll*(n-prev)*(n-ok[0].ss+1);

	printf("%lld\n", ans);
}
