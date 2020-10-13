// Codeforces 1027F - Session in BSU
// Lúcio Cardoso

/* Solution:

The main goal in this problem is checking the condition from Hall's Theorem in the graph {students, classes}.

To check this (and, consequently, get the earliest point when Hall's condition is met), iterate through
each classes in increasing order. Let G(C) = (set of students V with either A[V] or B[V] equal to C).

Now, suppose we're only considering classes with index <= the index we're currently iterating.

Lemma: It's possible to prove that if S = {c_1, c_2, ..., c_k} is the neighbourhood of a set of students that breaks
Hall's condition, then (G(c_1) U G(c_2) ... U G(c_k)) certainly breaks the condition.

Using the lemma above, we know that for a class C, the student set with C as part of its neighbouring set that is
"most prone" to break Hall's condition includes G(C). There is a problem, though: The neighbouring set of G(C)
can include other classes besides C, so we need to know how many.

To know that, we can use a DSU in the classes, keeping a vector that stores which students the current
neighbouring set of classes must have (according to the lemma above). The vectors can be merged using small
to large.

Now, all we need to keep is how many DSU sets so far have the value (amount_of_classes_in_set - size_of_its_vector_of_students)
negative. If the amount is 0, then it's possible to arrange classes/students using as largest class the current one. This can
be easily maintaned using only a variable.

Complexity: O(n log n) (barely passes though, runs in 3977 ms)

Note: I had to make some constant optimizations to AC, so the code might have some unexplained things.
The gist of the idea is the above, though.

*/

#include <bits/stdc++.h>

using namespace std;

const int maxn = 2e6+10;

int n, m;
int l[maxn], r[maxn];

bool mark[maxn];

vector<int> grafo[maxn];

int qtd_neg;

struct DSU
{
	int pai[maxn], peso[maxn];
	vector<int> st[maxn];

	void init(void)
	{
		for (int i = 1; i <= m; i++)
		{
			pai[i] = i, peso[i] = 1;

			for (auto v: grafo[i])
				if (l[v] == i)
					st[i].push_back(v);
		}
	}

	int Find(int x)
	{
		if (pai[x] == x) return x;
		return pai[x] = Find(pai[x]);
	}

	void Merge(int x, int y)
	{
		if (st[x].size() < st[y].size())
		{
			for (auto v: st[x])
				st[y].push_back(v);

			swap(st[x], st[y]);
		}
		else
		{
			for (auto v: st[y])
				st[x].push_back(v);
		}
	}

	void Join(int x, int y)
	{
		x = Find(x), y = Find(y);
		if (x == y) return;

		if (peso[y] - (int)st[y].size() < 0) qtd_neg--;
		if (peso[x] - (int)st[x].size() < 0) qtd_neg--;

		if (peso[x] < peso[y]) swap(x, y);

		pai[y] = x, peso[x] += peso[y];
		Merge(x, y);

		if (peso[x] - (int)st[x].size() < 0) qtd_neg++;
	}
} dsu;

int back[maxn];

void compress(void)
{
	map<int, int> mp;

	for (int i = 1; i <= n; i++)
		mp[l[i]] = 0, mp[r[i]] = 0;

	for (auto &x: mp)
	{
		x.second = ++m;
		back[x.second] = x.first;
	}

	for (int i = 1; i <= n; i++)
	{
		l[i] = mp[l[i]];
		r[i] = mp[r[i]];
	}
}

int main(void)
{
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
		scanf("%d %d", &l[i], &r[i]);

	compress();

	for (int i = 1; i <= n; i++)
	{
		grafo[l[i]].push_back(i);
		grafo[r[i]].push_back(i);
	}

	int tot = 0;
	dsu.init();

	for (int i = 1; i <= m; i++)
	{
		if (1 - (int)dsu.st[i].size() < 0) qtd_neg++;

		for (auto v: grafo[i])
		{
			if (!mark[v])
			{
				mark[v] = 1;
				++tot;
			}

			if (l[v] < i)
				dsu.Join(i, l[v]);
		}

		if (tot == n && qtd_neg == 0)
		{
			printf("%d\n", back[i]);
			return 0;
		}
	}

	printf("-1\n");
}
