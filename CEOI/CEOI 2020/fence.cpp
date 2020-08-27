// CEOI 2020 - Fancy Fence
// Lúcio Cardoso

#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

const int maxn = 1e5+10;
const int mod = 1e9+7;

typedef pair<int, int> pii;

struct Rect
{
	int h, w, ind;
} rect[maxn];

struct DSU
{
	int pai[maxn], peso[maxn];
	int soma[maxn];

	void init(int n)
	{
		for (int i = 1; i <= n; i++)
			pai[i] = i, peso[i] = 1, soma[i] = rect[i].w;
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

		pai[y] = x, peso[x] += peso[y], soma[x] = (soma[x]+soma[y])%mod;
 	}
} dsu;

int back[maxn];
bool mark[maxn];

int choose2(int a)
{
	return (1ll*a*(a-1)/2ll)%mod;
}

int pot(int a, int b)
{
	if (!b) return 1;

	int t = pot(a, b/2);

	if (b&1) return (1ll*a*((1ll*t*t)%mod))%mod;
	return (1ll*t*t)%mod;
}

int qtd(int h, int w)
{
	int x = (1ll*h*choose2(w))%mod;
	x = (1ll*x + 1ll*w*choose2(h))%mod;

	int ans = choose2((1ll*h*w)%mod);
	ans = (ans - x + mod)%mod;

	ans = (1ll*ans*pot(2, mod-2))%mod;
	ans = (ans + x)%mod;
	ans = (1ll*ans + 1ll*h*w)%mod;

	return ans;
}

int main(void)
{
	int n;
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &rect[i].h);
		rect[i].ind = i;
	}

	int ans = 0;

	for (int i = 1; i <= n; i++)
		scanf("%d", &rect[i].w);

	sort(rect+1, rect+n+1, [&] (Rect a, Rect b) {return a.h > b.h;});

	for (int i = 1; i <= n; i++)
		back[rect[i].ind] = i;

	dsu.init(n);

	for (int i = 1; i <= n; i++)
	{
		int j = rect[i].ind;

		int fora = 0;

		if (j > 1 && mark[j-1])
		{
			fora = (fora + qtd(rect[i].h, dsu.soma[dsu.Find(back[j-1])]))%mod;
			dsu.Join(i, back[j-1]);
		}

		if (j < n && mark[j+1])
		{
			fora = (fora + qtd(rect[i].h, dsu.soma[dsu.Find(back[j+1])]))%mod;
			dsu.Join(i, back[j+1]);
		}

		ans = (ans + qtd(rect[i].h, dsu.soma[dsu.Find(i)]))%mod;
		ans = (ans - fora + mod)%mod;

		mark[j] = 1;
	}

	printf("%d\n", ans);
}
