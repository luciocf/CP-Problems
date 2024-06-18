// Codeforces 1981D - Turtle and Multiplication
// Lucio Figueiredo

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <deque>
#include <cstring>
#include <set>
#include <map>
#include <cmath>

#define ff first
#define ss second
#define mkp make_pair
#define pb push_back

using namespace std;

typedef pair<int, int> pii;
typedef long long ll;

const int maxn = 2e6+10;

vector<int> primes;
bool comp[maxn];

void sieve(void)
{
	for (int i = 2; i < maxn; i++)
	{
		if (!comp[i])
		{
			primes.push_back(i);
			for (int j = 2*i; j < maxn; j += i)
				comp[j] = 1;
		}
	}
}

int qtd(int x)
{
	if (x%2) return x*(x+1)/2;
	return x*x/2+1;
}

vector<pii> grafo[maxn];
vector<int> path;
int ind[maxn];
bool mark[maxn];
bool seen[maxn];

void makeGraph(int m)
{
	int e = 0;

	if (m%2)
	{
		for (int i = 1; i <= m; i++)
		{
			for (int j = i+1; j <= m; j++)
			{
				grafo[i].push_back({j, ++e});
				grafo[j].push_back({i, e});
				mark[e] = 0;
			}
		}
	}
	else
	{
		for (int i = 1; i <= m; i++)
		{
			for (int j = i+1; j <= m; j++)
			{
				if ((i%2) and j == i+1 and j != m) continue;

				grafo[i].push_back({j, ++e});
				grafo[j].push_back({i, e});
				mark[e] = 0;
			}
		}
	}
}

void dfs(int u)
{
	while (ind[u] < grafo[u].size())
	{
		int v = grafo[u][ind[u]].ff, e = grafo[u][ind[u]].ss;
		++ind[u];

		if (!mark[e])
		{
			mark[e] = 1;
			dfs(v);
 		}
	}

	path.push_back(u-1);
	if (!seen[u])
	{
		seen[u] = 1;
		path.pb(u-1);
	}
}

int main(void)
{
	int tc;
	cin >> tc;

	sieve();

	while (tc--)
	{
		int n;
		cin >> n;
		n--;

		int m = 1;
		while (qtd(m) < n)
			++m;

		path.clear();
		for (int i = 1; i <= m; i++)
		{
			seen[i] = 0;
			ind[i] = 0;
			grafo[i].clear();
		}

		makeGraph(m);
		int u = 1;
		for (int i = 1; i <= m; i++)
			if (grafo[i].size()%2)
				u = i;
		dfs(u);

		vector<int> ans;
		ans.push_back(primes[path[0]]);
		for (int i = 1; i < path.size() and n > 0; i++, n--)
			ans.push_back(primes[path[i]]);

		for (auto x: ans)
			cout << x << " ";
		cout << "\n";
	}
}
