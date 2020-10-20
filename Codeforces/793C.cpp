// Codeforces 793C - Mice problem
// Lúcio Cardoso

// Solution is the same as the one in editorial

#include <bits/stdc++.h>
 
#define ff first
#define ss second
 
using namespace std;
 
typedef pair<double, double> pdd;
typedef pair<int, int> pii;
 
const int maxn = 1e5+10;
const double eps = 1e-12;
 
int n;
pii p1, p2;
 
pii pt[maxn], v[maxn];
 
bool intersect(pdd &at, pdd pp)
{ 
	pp.ff += eps;
	pp.ss -= eps;

	if (pp.ff > pp.ss || at.ff > pp.ss || at.ss < pp.ff) return 0;
 
	at.ff = max(at.ff, pp.ff);
	at.ss = min(at.ss, pp.ss);
 
	return 1;
}
 
int main(void)
{
	scanf("%d %d %d %d %d", &n, &p1.ff, &p1.ss, &p2.ff, &p2.ss);
 
	for (int i = 1; i <= n; i++)
		scanf("%d %d %d %d", &pt[i].ff, &pt[i].ss, &v[i].ff, &v[i].ss);
 
	pdd at = {0, 1e18};
 
	for (int i = 1; i <= n; i++)
	{
		if (v[i].ff == 0)
		{
			if (pt[i].ff >= p2.ff || pt[i].ff <= p1.ff)
			{
				printf("-1\n");
				return 0;
			}
		}
		else
		{
			pdd pp = {1.00*(p1.ff-pt[i].ff)/(1.00*v[i].ff), 1.00*(p2.ff-pt[i].ff)/(1.00*v[i].ff)};

			if (v[i].ff < 0) swap(pp.ff, pp.ss);
	 
			if (!intersect(at, pp))
			{
				printf("-1\n");
				return 0;
			}
		}
 	
 		if (v[i].ss == 0)
 		{
 			if (pt[i].ss >= p2.ss || pt[i].ss <= p1.ss)
			{
				printf("-1\n");
				return 0;
			}
 		}	
		else
		{
			pdd pp = {1.00*(p1.ss-pt[i].ss)/(1.00*v[i].ss), 1.00*(p2.ss-pt[i].ss)/(1.00*v[i].ss)};

			if (v[i].ss < 0) swap(pp.ff, pp.ss);
	 
			if (!intersect(at, pp))
			{
				printf("-1\n");
				return 0;
			}
		}
	}
 
	printf("%.7lf\n", at.ff);
}
