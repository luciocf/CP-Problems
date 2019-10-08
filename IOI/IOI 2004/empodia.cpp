// IOI 2004 - Empodia
// Lúcio Cardoso

// The condition for an interval [l, r] to be framed is the following:
//	- A[l] is smallest number in [l, r]
//	- A[r] is the largest number in [l, r]
//	- A[r]-A[l] = r-l  -> A[r]-r = A[l]-l

// Iterate through every array index L in reverse order. We will assume L is the left endpoint
// of an empodio. Use a set called mx maintaining all indices k such that A[k] is the maximum in [L, k].
// When we consider the index L, we need to remove every element from mx that is smaller than A[L]
// (we can do it in O(n) in total).

// Now, maintain an array of sets st[] such that st[i] contains every element in mx with index k such
// that A[k]-k = i. Update these sets when removing the elements from mx.

// Notice only the smallest index in the st[A[L]-L] (say, R) can be a valid endpoint for an empodio starting at L
// (otherwise the empodio [L, R] would be inside another empodio). Thus, all we now need to do is to check
// if there is another framed interval [X, Y] inside [L, R]. To check that, use a BIT that marks
// the right endpoint of each framed interval with the value 1. If sum(R) >= 1, there is a framed interval
// inside [L, R].

// Complexity: O(N log N) 

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
