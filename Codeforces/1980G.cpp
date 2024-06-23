// Codeforces 1980G - Yasya and the Mysterious Tree
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

using namespace std;

#define ff first
#define ss second
#define mkp make_pair
#define pb push_back
#define sz(x) (int)(x).size()
#define lb lower_bound
#define ub upper_bound
#define all(x) x.begin(), x.end()
#define ins insert

typedef pair<int, int> pii;
typedef long long ll;

const int maxn = 2e5+10;

struct Node
{
	Node *t[2];
	int qtd;

	Node()
	{
		t[0] = t[1] = NULL;
		qtd = 0;
	}
};

struct Trie
{
	Node *root;

	void add(int x)
	{
		Node *at = root;
		for (int b = 30; b >= 0; b--)
		{
			int k;
			if (x&(1<<b)) k = 1;
			else k = 0;

			if (!at->t[k]) at->t[k] = new Node;

			at->qtd++;
			at = at->t[k];
		}
		at->qtd++;
	}

	void del(int x)
	{
		Node *at = root;
		for (int b = 30; b >= 0; b--)
		{
			int k;
			if (x&(1<<b)) k = 1;
			else k = 0;

			at->qtd--;
			at = at->t[k];
		}
		at->qtd--;
	}

	int mx(int x)
	{
		int ans = 0;
		Node *at = root;

		for (int b = 30; b >= 0; b--)
		{
			if (at->qtd == 0) return -1;

			int k;
			if (x&(1<<b)) k = 0;
			else k = 1;

			if (!at->t[k] or at->t[k]->qtd == 0) at = at->t[!k];
			else
			{
				ans += (1<<b);
				at = at->t[k];
			}
		}

		return ans;
	}
};

int nivel[maxn], path[maxn];
vector<pii> grafo[maxn];

void dfs(int u, int p)
{
	for (auto [v, w]: grafo[u])
	{
		if (v == p) continue;

		nivel[v] = nivel[u]+1, path[v] = path[u] ^ w;
		dfs(v, u);
	}
}

void solve()
{
	int n, m;
	cin >> n >> m;

	Trie T[2];
	T[0].root = new Node();
	T[1].root = new Node();

	for (int i = 1; i <= n; i++)
	{
		nivel[i] = path[i] = 0;
		grafo[i].clear();
	}

	for (int i = 1; i < n; i++)
	{
		int u, v, w;
		cin >> u >> v >> w;

		grafo[u].pb({v, w});
		grafo[v].pb({u, w});
	}

	dfs(1, 0);

	for (int i = 1; i <= n; i++)
		T[nivel[i]%2].add(path[i]);

	int add = 0;
	while (m--)
	{
		char op;
		cin >> op;

		if (op == '?')
		{
			int u, x;
			cin >> u >> x;

			int k = nivel[u]%2;

			T[k].del(path[u]);

			cout << max(T[k].mx(path[u]^x), T[!k].mx(path[u]^x^add)) << " ";

			T[k].add(path[u]);
		}
		else
		{
			int x;
			cin >> x;
			add ^= x;
		}
	}
}

int main(void)
{
	int tc = 1;
	cin >> tc;
	while (tc--)
	{
		solve();
	}
}
