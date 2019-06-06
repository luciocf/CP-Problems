// BOI 2012 - Mobile
// Lúcio Cardoso

// Binary Search Solution
// Same as here: http://www.boi2012.lv/data/day1/spoilers/mobile.pdf

#include <bits/stdc++.h>
 
#define ff first
#define ss second
 
using namespace std;
 
const int maxn = 1e6+10;
const double inf = 1e9+10;
 
typedef pair<int, int> pii;
 
int n, L;
 
pii p[maxn];
 
bool ok(double K)
{
	vector<pair<double, double>> V(n);

	int m = -1;
 
	for (int i = 1; i <= n; i++)
	{
		int x = p[i].ff, y = p[i].ss;
 
		if (K*K < 1.0*y*y)
			continue;
 
		double delta = sqrt(K*K - 1.0*y*y);
 
		double x1 = 1.0*x-delta, x2 = 1.0*x+delta;

		V[++m] = {x1, x2};
	}
 
	double r = 0.00;

	for (int i = 0; i <= m; i++)
		if (V[i].ff < r)
			r = max(r, V[i].ss);

	return (r <= 1.0*L);
}
 
double busca(void)
{
	double ini = 0.00, fim = inf, ans = 0.00;
 
	for (int i = 1; i <= 60; i++)
	{
		double mid = (ini+fim)/2.00;
 
		if (ok(mid)) ans = mid, ini = mid;
		else fim = mid;
	}
 
	return ans;
}
 
int main(void)
{
	scanf("%d %d\n", &n, &L);
 
	for (int i = 1; i <= n; i++)
		scanf("%d %d", &p[i].ff, &p[i].ss);
 
	printf("%.9lf\n", busca());
}
