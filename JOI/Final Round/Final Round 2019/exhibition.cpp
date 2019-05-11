// JOI Final Round 2019 - Exhibition
// Lúcio Cardoso

#include <bits/stdc++.h>
 
using namespace std;
 
const int maxn = 1e5+10;
 
struct P
{
	int s, v;
} p[maxn];
 
int suf[maxn];
 
int c[maxn];
 
int n, m;
 
bool comp(P a, P b)
{
	if (a.v == b.v) return a.s < b.s;
	return a.v < b.v;
}
 
int main(void)
{
	scanf("%d %d", &n, &m);
 
	for (int i = 1; i <= n; i++)
		scanf("%d %d", &p[i].s, &p[i].v);
 
	for (int i = 1; i <= m; i++)
		scanf("%d", &c[i]);
 
	sort(p+1, p+n+1, comp);
	sort(c+1, c+m+1);
 
	int ans = 0, ptr = n;
	for (int i = m; i >= 1; i--)
	{
		for (; ptr >= 1 && p[ptr].s > c[i]; ptr--);
 
		if (ptr >= 1)
		{
			ans++;
			ptr--;
		}
	}
 
	printf("%d\n", ans);
}
