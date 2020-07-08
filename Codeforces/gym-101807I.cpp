// Codeforces Gym 101807I - Infection
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5+10;

int a[maxn];
int b[maxn];

bool mark[maxn];

vector<int> grafo[maxn];

int main(void)
{
	int n, m;
	scanf("%d %d", &n, &m);

	for (int i = 1; i <= m; i++)
	{
		int u, v;
		scanf("%d %d", &u, &v);

		grafo[u].push_back(v);
		grafo[v].push_back(u);
	}

	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);

	set<int> st;
	int last = 0;

	for (int i = 1; i <= n; i++)
	{
		int u = a[i];

		mark[u] = 1;

		if (st.find(-u) != st.end())
			st.erase(-u);

		for (auto v: grafo[u])
			if (!mark[v])
				st.insert(-v);

		if (i != n && -*st.begin() > a[i+1])
			last = i;
	}

	memset(mark, 0, sizeof mark);
	st.clear();

	if (last == 0)
	{
		if (a[1] == n)
		{
			printf("-1\n");
			return 0;
		}

		b[1] = a[1]+1;

		for (int i = 2; i <= n; i++)
		{
			int u = b[i-1];

			mark[u] = 1;

			if (st.find(u) != st.end())
				st.erase(u);

			for (auto v: grafo[u])
				if (!mark[v])
					st.insert(v);

			b[i] = *st.begin();
		}

		for (int i = 1; i <= n; i++)
			printf("%d ", b[i]);
		printf("\n");
	}
	else
	{
		for (int i = 1; i <= last; i++)
		{
			int u = a[i];
			mark[u] = 1;

			if (st.find(u) != st.end())
				st.erase(u);

			b[i] = a[i];

			if (st.find(u) != st.end())
				st.erase(u);

			for (auto v: grafo[u])
				if (!mark[v])
					st.insert(v);
		}

		b[last+1] = *st.upper_bound(a[last+1]);

		for (int i = last+2; i <= n; i++)
		{
			int u = b[i-1];
			mark[u] = 1;

			if (st.find(u) != st.end())
				st.erase(u);

			for (auto v: grafo[u])
				if (!mark[v])
					st.insert(v);

			b[i] = *st.begin();
		}

		for (int i = 1; i <= n; i++)
			printf("%d ", b[i]);
		printf("\n");
	}
}
