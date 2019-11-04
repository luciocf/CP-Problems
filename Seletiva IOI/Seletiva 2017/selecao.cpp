// Seletiva IOI 2017 - Seleção
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int maxn = 1e6+10;

int n;
ll k;
int Ax, Bx, Cx, Mx;
int Ay, By, Cy, My;
int a[maxn], b[maxn];

ll qtd(int v)
{
	int ptr = n;
	ll tot = 0;

	for (int i = 1; i <= n; i++)
	{
		while (ptr > 1 && a[i]+b[ptr] >= v) ptr--;

		if (a[i]+b[ptr] < v) tot += 1ll*ptr;
	}

	return tot;
}

int busca(void)
{
	int ini = 0, fim = 1e9+10, ans = 0;

	while (ini <= fim)
	{
		int mid = (ini+fim)>>1;

		if (qtd(mid) <= k-1) ans = mid, ini = mid+1;
		else fim = mid-1;
	}

	return ans;
}

int main(void)
{
	scanf("%d %lld %d %d %d %d %d %d %d %d", &n, &k, &Ax, &Bx, &Cx, &Mx, &Ay, &By, &Cy, &My);

	a[1] = Ax;
	for (int i = 2; i <= n; i++)
		a[i] = (Bx + Cx*a[i-1])%Mx;

	b[1] = Ay;
	for (int i = 2; i <= n; i++)
		b[i] = (By + Cy*b[i-1])%My;

	sort(a+1, a+n+1); sort(b+1, b+n+1);

	printf("%d\n", busca());
}
