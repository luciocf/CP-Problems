// IOI 2004 - Empodia
// Lúcio Cardoso

#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

typedef pair<int, int> pii;

const int maxn = 2000010;

int n;
int a[maxn], dif[maxn];

int bit[maxn];

vector<pii> ans;

set<pii> mx;
set<int> st[maxn];

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

int main(void)
{
	scanf("%d", &n);

	vector<pii> aux;
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);

		aux.push_back({a[i]-i, i});
	}

	sort(aux.begin(), aux.end());

	int cnt = 1;
	for (int i = 0; i < aux.size(); i++)
	{
		if (i != 0 && aux[i].first != aux[i-1].first) ++cnt;

		dif[aux[i].second] = cnt;
	}

	stack<pii> stk;
	for (int i = n; i >= 1; i--)
	{
		for (auto it = mx.begin(); it != mx.end();)
		{
			if ((*it).ff > a[i]) break;

			st[dif[(*it).ss]].erase((*it).ss);

			it = mx.erase(it);
		}

		int last = n;

		while (stk.size() && stk.top().ff > a[i]) stk.pop();

		if (stk.size()) last = stk.top().ss-1;

		stk.push({a[i], i});

		if (st[dif[i]].size())
		{
			int p = *(st[dif[i]].begin());

			if (p <= last && soma(p) == 0)
			{
				ans.push_back({i, p});
				upd(p, 1);
			}
		}

		st[dif[i]].insert(i);
		mx.insert({a[i], i});
	}

	sort(ans.begin(), ans.end());

	printf("%d\n", (int)ans.size());
	for (auto pp: ans)
		printf("%d %d\n", pp.first, pp.second);
}
