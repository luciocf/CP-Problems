// infoarena - Unique
// Lúcio Cardoso

// Solution:

// Suppose we want to calculate the largest interval that ends at i. For every index r
// in [1..i], calculate the rightmost index l < r with a[l] > a[j] (this can be done with a
// monotonic stack). Now, for each such pair (l, r), we want to check if the amount of distinct
// values in [l+1, i] is equal to a[r]. If so, this interval is a valid one, since every number in
// [l+1, i] is smaller than or equal to a[r].

// To check that, while iterating through the array from the left to right, we'll maintain an array
// last[k] that indicates the rightmost position j in [1..i] such that a[j] = k. If the amount of indices
// j in [l+1, i] such that last[k] = j for some k is equal to a[r], this is a valid interval, i.e, all numbers
// from 1 to a[r] are present.

// To calculate the amount of "active last[] indices" in an interval, we can join every interval with DSU
// and maintain a variable for every DSU set that indicates how many "last[] indices" it contains.

// Complexity: O(n alpha(n)) 


#include <bits/stdc++.h>
 
#define ff first
#define ss second
 
using namespace std;
 
typedef pair<int, int> pii;
 
const int maxn = 1e5+10;
 
int n;
int a[maxn];
 
int last[maxn];
 
int pai[maxn], peso[maxn], qtd[maxn];
 
void init(void)
{
	for (int i = 1; i <= n; i++)
		pai[i] = i, peso[i] = 1, qtd[i] = 0;
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

	pai[y] = x, peso[x] += peso[y], qtd[x] += qtd[y];
} 

int main(void)
{
	freopen("unique.in", "r", stdin); freopen("unique.out", "w", stdout);

	int t;
	scanf("%d", &t);
 
	while (t--)
	{
		memset(last, 0, sizeof last);
 
		scanf("%d", &n);
 		init();

		for (int i = 1; i <= n; i++)
			scanf("%d", &a[i]);
 
		int ans = 0;
		stack<pii> stk;
 
		for (int i = 1; i <= n; i++)
		{
			while (stk.size() && a[i] >= stk.top().ff)
			{
				int val = stk.top().ff, pos = stk.top().ss, r = i-1;
				stk.pop();
 
				int l = (!stk.size() ? 1 : stk.top().ss+1);

				Join(pos, pos+1);
 
				if (qtd[Find(pos)] == val) ans = max(ans, r-l+1);
			}
		
			stk.push({a[i], i});
 		
			if (last[a[i]]) qtd[Find(last[a[i]])]--;
			qtd[Find(i)]++, last[a[i]] = i;
		}
 
		while (stk.size())
		{
			int val = stk.top().ff, pos = stk.top().ss, r = n;
			stk.pop();
 
			int l = (!stk.size() ? 1 : stk.top().ss+1);

			if (pos != n) Join(pos, pos+1);
 
			if (qtd[Find(pos)] == val) ans = max(ans, r-l+1);
		}
 
		printf("%d\n", ans);
	}
}
