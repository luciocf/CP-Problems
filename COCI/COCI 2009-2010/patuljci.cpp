// COCI 2009/2010 - Patuljci
// Lúcio Cardoso

// Solution:

// 1. Use Mo's algorithm to calculate the frequency of each number in the current range.

// 2. We can precalculate, in a segment tree, the most frequent value in one of its nodes
// in O(n log n).

// 3. Notice that, if a value shows up more than K/2 times in a range, it has to be one of
// the most frequent values in at least one of the nodes of the segment tree that represents
// such range. Thus, we have at most log n candidates for the answer.

#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

const int maxn = 3e5+10;

struct Q
{
	int l, r, bloco, id;
} query[maxn];

int a[maxn], freq[maxn];

int tree[4*maxn];

int ans[maxn];

vector<int> env;

void build(int node, int l, int r)
{
	if (l == r)
	{
		tree[node] = a[l];
		return;
	}

	int mid = (l+r)>>1;

	build(2*node, l, mid); build(2*node+1, mid+1, r);

	int freq1 = 0, freq2 = 0;
	int a1 = tree[2*node], a2 = tree[2*node+1];

	for (int i = l; i <= r; i++)
	{
		if (a[i] == a1) freq1++;
		if (a[i] == a2) freq2++;
	}

	tree[node] = -1;

	if (freq1 > (r-l+1)/2) tree[node] = a1;
	if (freq2 > (r-l+1)/2) tree[node] = a2;
}

void get(int node, int l, int r, int a, int b)
{
	if (l > b || r < a) return;
	if (l >= a && r <= b)
	{
		if (tree[node] != -1)
			env.push_back(tree[node]);
		return;
	}

	int mid = (l+r)>>1;

	get(2*node, l, mid, a, b); get(2*node+1, mid+1, r, a, b);
}

void add(int l)
{
	freq[a[l]]++;
}

void rem(int l)
{
	freq[a[l]]--;
}

bool comp(Q a, Q b)
{
	if (a.bloco == b.bloco) return a.r < b.r;
	return a.bloco < b.bloco;
}

int main(void)
{
	int n, c;
	scanf("%d %d", &n, &c);

	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);

	int bucket = sqrt(n);

	int m;
	scanf("%d", &m);

	for (int i = 1; i <= m; i++)
	{
		scanf("%d %d", &query[i].l, &query[i].r);

		query[i].bloco = query[i].l/bucket;
		query[i].id = i;
	}


	build(1, 1, n);

	sort(query+1, query+m+1, comp);

	int l = 1, r = 1;
	add(1);

	for (int i = 1; i <= m; i++)
	{
		env.clear();

		while (r > query[i].r) rem(r--);
		while (r < query[i].r) add(++r);

		while (l > query[i].l) add(--l);
		while (l < query[i].l) rem(l++);

		int cor = 0;

		get(1, 1, n, l, r);

		for (auto x: env)
			if (freq[x] > (r-l+1)/2)
				cor = x;

		ans[query[i].id] = cor;
	}

	for (int i = 1; i <= m; i++)
	{
		if (ans[i]) printf("yes %d\n", ans[i]);
		else printf("no\n");
	}
}
