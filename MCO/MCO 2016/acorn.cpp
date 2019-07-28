// MCO 2016 - Acorn
// Lúcio Cardoso

// Solution:

// 1. Suppose the set of pairs (a, b) that are maximum at some time X is
// S = {i_1, i_2, ..., i_k}, such that b_{i_1} < b_{i_2} < ... < b_{i_k} (notice
// that all values b_i in the set are distinct). Then, we can observe that
// a_{i_1} < a_{i_2} < ... < a_{i_k}. Since 0 <= a_i <= 1000, |S| <= 1000.
// We can find the set S by sorting all N pairs by b_i and using a monotonic queue in O(N).

// 2. If in time T the "optimum" pair (the one with maximum value) is (a_i, b_i),
// in time (T+delta), the value b of the optimum pair is >= b_i. Thus, we can use binary search
// to find for a certain index i from S if it is ever optimum: if for a time T the b value of the optimum pair
// is larger than b_i, the time i is optimal is < T. Otherwise, it's >= T.

// 3. As a detail for the binary search, notice that after time T > 10^6, the pair with largest b value will
// always be the best. Hence, the complexity of the binary search is O(|S| log 10^6).

// Overall complexity: O(|S|^2 * log 10^6 + N log N).

#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

typedef pair<int, int> pii;

const int maxn = 8e4+10;

int n, m, mini=1e9;

pii v[maxn];

pii opt[maxn];

void get_opt(void)
{
	stack<pii> stk;

	for (int i = 1; i <= n; i++)
	{
		if (i > 1 && v[i].ff == v[i-1].ff) continue;

		while (stk.size() && stk.top().ss >= v[i].ss)
			stk.pop();

		stk.push(v[i]);
	}

	m = stk.size();

	for (int i = m; i >= 1; i--)
	{
		opt[i] = stk.top();
		stk.pop();
	}
}

bool ok(int k, int T)
{
	int mx = 0, ind = 1;

	for (int i = 1; i <= m; i++)
	{
		int x = max(0, opt[i].ff*(T-opt[i].ss));

		if (x > mx || (x == mx && opt[i].ff > opt[ind].ff))
			mx = x, ind = i;
	}

	return opt[ind].ff <= opt[k].ff;
}

bool busca(int k)
{
	int ini = mini, fim = 1e6+10, ans = -1;

	while (ini <= fim)
	{
		int mid = (ini+fim)>>1;

		if (ok(k, mid)) ans = mid, ini = mid+1;
		else fim = mid-1;
	}

	if (ans == -1) return 0;

	int mx = 0, ind = 1;

	for (int i = 1; i <= m; i++)
	{
		int x = max(0, opt[i].ff*(ans-opt[i].ss));

		if (x > mx || (x == mx && opt[i].ff > opt[ind].ff))
			mx = x, ind = i;
	}

	return (ind == k);
}

int main(void)
{
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
		scanf("%d %d", &v[i].ss, &v[i].ff);

	sort(v+1, v+n+1);

	get_opt();

	int ans = n-m;

	for (int i = 1; i <= m; i++)
		mini = min(mini, opt[i].ss+1);

	for (int i = 1; i <= m; i++)
		if (!busca(i))
			ans++;

	printf("%d\n", ans);
}
