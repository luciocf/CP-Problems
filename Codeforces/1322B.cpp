// Codeforces 1322B - Present
// Lúcio Cardoso

#include <bits/stdc++.h>
 
using namespace std;
 
const int maxn = 4e5+10;
 
int a[maxn];
int v[maxn];
 
int busca1(int l, int r, int pos, int x)
{
	int ini = l, fim = r, ans = -1;
 
	while (ini <= fim)
	{
		int mid = (ini+fim)>>1;
 
		if (a[mid] + a[pos] <= x) ans = mid, ini = mid+1;
		else fim = mid-1;
	}
 
	return ans;
}
 
int busca2(int l, int r, int pos, int x)
{
	int ini = l, fim = r, ans = -1;
 
	while (ini <= fim)
	{
		int mid = (ini+fim)>>1;
 
		if (a[mid] + a[pos] >= x) ans = mid, fim = mid-1;
		else ini = mid+1;
	}
 
	return ans;
}
 
int main(void)
{
	int n;
	scanf("%d", &n);
 
	for (int i = 1; i <= n; i++)
		scanf("%d", &v[i]);
 
	int ans = 0;
 
	for (int b = 0; b <= 24; b++)
	{
		int qtd = 0;
 
		for (int i = 1; i <= n; i++)
			a[i] = v[i]%(1<<(b+1));
 
		sort(a+1, a+n+1);
 
		for (int i = 1; i <= n; i++)
		{
			int l = busca2(1, i-1, i, (1<<b));
			int r = busca1(1, i-1, i, (1<<(b+1))-1);
 
			if (l != -1 && r != -1) qtd += (r-l+1);
 
			l = busca2(1, i-1, i, (1<<b) + (1<<(b+1)));
			r = busca1(1, i-1, i, (1<<(b+2))-2);
 
			if (l != -1 && r != -1) qtd += (r-l+1);
		}
 
		if (qtd%2) ans += (1<<b);
	}
 
	printf("%d\n", ans);
}
