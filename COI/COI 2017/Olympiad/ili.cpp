// COI 2017 - Ili
// Lúcio Cardoso

// Solution is the same as in: https://github.com/thecodingwizard/competitive-programming/blob/master/COI/COI%2017-ili.cpp

#include <bits/stdc++.h>
 
using namespace std;
 
const int maxn = 2e4+10;
 
int n, m;
int a[maxn], b[maxn];
int l[maxn], r[maxn];
 
bool mark[maxn];

vector<int> grafo[maxn];
 
void dfs(int u)
{
	mark[u] = 1;
	a[u] = 0;
 
	if (!mark[l[u]]) dfs(l[u]);
	if (!mark[r[u]]) dfs(r[u]);
}
 
void do_1(void)
{
	while (true)
	{
		for (int i = n+1; i <= n+m; i++)
			if (a[i] == 0 && !mark[i])
				dfs(i);

		bool novo = 0;

		for (int i = n+1; i <= n+m; i++)
		{
			if (a[i] == -1 && a[l[i]] == 0 && a[r[i]] == 0)
				a[i] = 0;
			
			if (a[i] == 0 && !mark[i])
			{
				novo = 1;
				break;
			}
		}

		if (!novo) break; 
	}
}
 
bool dfs2(int u)
{
	if (b[u] == 1) return false;
	mark[u] = 1, b[u] = 0;

	if (!mark[l[u]] && !dfs2(l[u])) return false;
	if (!mark[r[u]] && !dfs2(r[u])) return false;

	for (auto v: grafo[u])
	{
		if (b[v] == 1)
		{
			if (l[v] == u && b[r[v]] == 0) return false;
			else if (r[v] == u && b[l[v]] == 0) return false;
		}
		else if (b[v] == -1)
		{
			if ((l[v] == u && b[r[v]] == 0) || (r[v] == u && b[l[v]] == 0))
			{
				b[v] = 0;
				if (!mark[v] && !dfs2(v)) return false;
			}
		}
	}

	return true;
}
 
bool can(int u)
{
	memset(mark, 0, sizeof mark);
	for (int i = 1; i <= n+m; i++)
		b[i] = a[i];
	b[u] = 0;

	return dfs2(u);
}
 
int main(void)
{
	scanf("%d %d", &n, &m);
 
	memset(a, -1, sizeof a);
 
	for (int i = 1; i <= m; i++)
	{
		char c;
		scanf(" %c", &c);
 
		if (c == '1') a[n+i] = 1;
		else if (c == '0') a[n+i] = 0;
	}
 
	for (int i = 1; i <= m; i++)
	{
		char c1;
		int c2;
 
		scanf(" %c %d", &c1, &c2);
 
		if (c1 == 'x')
		{
			l[n+i] = c2;
			grafo[c2].push_back(n+i);
		}
		else
		{
			l[n+i] = n+c2;
			grafo[n+c2].push_back(n+i);
		}
 
		scanf(" %c %d", &c1, &c2);
 
		if (c1 == 'x')
		{
			r[n+i] = c2;
			grafo[c2].push_back(n+i);
		}
		else
		{
			r[n+i] = n+c2;
			grafo[n+c2].push_back(n+i);
		}
	}
 
	do_1();
 
	for (int i = 1; i <= n+m; i++)
	{
		if (a[i] != -1) continue;
 
		if (!can(i))
			a[i] = 1;
	}
 
	for (int i = n+1; i <= n+m; i++)
	{
		if (a[i] == -1) printf("?");
		else if (a[i] == 0) printf("0");
		else printf("1");
	}
	printf("\n");
}
