// Seletiva IOI 2017 - Seleção
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 3e6+10;

typedef long long ll;

int n;
ll a[maxn], b[maxn], soma[maxn], k;

bool ok(int x)
{
	ll aux = 0LL;
	for (int i = 1; i <= n; i++)                   
		if (a[i] <= x) aux += soma[x-a[i]];

	return (aux >= k);
}

ll busca(void)
{
	int ini = 1, fim = 2e6+10;
	ll ans;

	while (ini <= fim)
	{
		int mid = (ini+fim)/2;

		if (ok(mid)) ans = mid, fim = mid-1;
		else ini = mid+1;
	}

	return ans;
}

int main(void)
{
	ios::sync_with_stdio(false); cin.tie(0);

	ll ax, bx, cx, mx;

	cin >> n >> k;
	cin >> ax >> bx >> cx >> mx;

	a[1] = ax;
	for (int i = 2; i <= n; i++)
		a[i] = (bx + (cx*a[i-1])%mx)%mx;

	ll ay, by, cy, my;
	cin >> ay >> by >> cy >> my;

	b[1] = ay, soma[ay]++;
	for (int i = 2; i <= n; i++)
	{
		b[i] = (by + (cy*b[i-1])%my)%my;
		soma[b[i]]++;
	}

	for (int i = 1; i < maxn; i++)
		soma[i] += soma[i-1];

	cout << busca() << "\n";
}