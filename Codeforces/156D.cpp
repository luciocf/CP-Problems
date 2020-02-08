#include <bits/stdc++.h>
 
using namespace std;
 
const int maxn = 1e5+10;
 
int pai[maxn], peso[maxn];
 
void init(int n)
{
	for (int i = 1; i <= n; i++)
		pai[i] = i, peso[i] = 1;
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
 
	pai[y] = x, peso[x] += peso[y];
}
 
int main(void)
{
	int n, m, k;
	scanf("%d %d %d", &n, &m, &k);
 
	init(n);
 
	for (int i = 1; i <= m; i++)
	{
		int u, v;
		scanf("%d %d", &u, &v);
 
		Join(u, v);
	}
 
	int prod = 1, cc = 0;
 
	for (int i = 1; i <= n; i++)
		if (Find(i) == i)
			prod = (1ll*prod*peso[i])%k, ++cc;
 
	for (int i = 1; i <= cc-2; i++)
		prod = (1ll*prod*n)%k;
 
	if (k == 1) printf("0\n");
	else if (cc == 1) printf("1\n");
	else printf("%d\n", prod);
}
