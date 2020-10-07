// JOISC 2016 - Matryoshka
// Lúcio Cardoso

/* Solution:

Consider all dolls included in query (A, B). Let G be a DAG such that doll u has an edge to doll v
iff r_u > r_v and h_u > h_v. Notice that what the problem asks is the minimal chain decomposition in this
graph.

By Dilworth's Theorem, the size of the minimal chain decomposition of a DAG is equal to the size
of the largest antichain (an anthichain is a set of vertices such that no two of them have a path).

If we sort the dolls by their r-value, it's easy to see that the query is a suffix in the array
and that the largest antichain for such query is the longest decreasing sequence considering all
elements in the suffix with h-value <= B.

If we process queries offline, it's possible to find the LDS of the suffix in O(log n) per query using
a segment tree.

For a solution in O(log n) per query without a segment tree, see this: https://github.com/thecodingwizard/competitive-programming/blob/master/JOI/JOISC%2016-Matryoshka.cpp

Complexity: O(n log n).

*/

#include <bits/stdc++.h>
 
#define ff first
#define ss second
 
using namespace std;
 
typedef pair<int, int> pii;
 
const int maxn = 2e5+10;
 
struct SegmentTree
{
	int tree[3*maxn];
 
	void upd(int node, int l, int r, int pos, int v)
	{
		if (l == r)
		{
			tree[node] = v;
			return;
		}
 
		int mid = (l+r)>>1;
 
		if (pos <= mid) upd(2*node, l, mid, pos, v);
		else upd(2*node+1, mid+1, r, pos, v);
 
		tree[node] = max(tree[2*node], tree[2*node+1]);
	}
 
	int query(int node, int l, int r, int a, int b)
	{
		if (l > r || l > b || r < a) return 0;
		if (l >= a && r <= b) return tree[node];
 
		int mid = (l+r)>>1;
 
		return max(query(2*node, l, mid, a, b), query(2*node+1, mid+1, r, a, b)); 
	}
} seg;
 
struct Query
{
	int r, h, ind;
} qry[maxn];
 
int n, q;
pii a[maxn];
 
int ans[maxn];
 
map<int, vector<int>> pos;
 
bool comp(pii x, pii y)
{
	if (x.ff == y.ff) return x.ss > y.ss;
	return x.ff < y.ff;
}
 
int main(void)
{
	scanf("%d %d", &n, &q);
 
	for (int i = 1; i <= n; i++)
		scanf("%d %d", &a[i].ff, &a[i].ss);
 
	for (int i = 1; i <= q; i++)
	{
		scanf("%d %d", &qry[i].r, &qry[i].h);
		qry[i].ind = i;
	}
 
	sort(a+1, a+n+1, comp);
	sort(qry+1, qry+q+1, [&] (Query a, Query b) {return a.h < b.h;});
 
	for (int i = n; i >= 1; i--)
		pos[a[i].ss].push_back(i);
 
	int ptr = 1;
 
	for (int i = 1; i <= q; i++)
	{
		while (ptr <= qry[i].h)
		{
			for (auto j: pos[ptr])
			{
				int mx = seg.query(1, 1, n, j+1, n)+1;
				seg.upd(1, 1, n, j, mx);
			}
 
			ptr++;
		}
 
		int pos = (int)(lower_bound(a+1, a+n+1, make_pair(qry[i].r, 0))-a);
 
		ans[qry[i].ind] = seg.query(1, 1, n, pos, n);
	}
 
	for (int i = 1; i <= q; i++)
		printf("%d\n", ans[i]);
}
